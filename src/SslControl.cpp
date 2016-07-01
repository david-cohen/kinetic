/*
 * Copyright (c) 2014-2016 Western Digital Corporation or its affiliates <copyrightagent@wdc.com>
 * @author Gary Ballance <gary.ballance@wdc.com>
 *
 * SPDX-License-Identifier: GPL-2.0+
 * This file is part of Kinetic Advanced Object Store (KAOS).
 *
 * This program is free software: you may copy, redistribute and/or modify it under the terms of the
 * GNU General Public License as published by the Free Software Foundation, either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
 * even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program; if
 * not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA. <http://www.gnu.org/licenses/>
 */

/*
 * Include Files
 */
#include <openssl/err.h>
#include <string>
#include <stdexcept>
#include "Logger.hpp"
#include "SslControl.hpp"
#include "GlobalConfig.hpp"

/*
 * Constants
 */
const int32_t SSL_SUCCESS(1);

/**
 * Initializes the SSL Control object.
 */
SslControl::SslControl()
    : m_operational(false), m_context(nullptr) {

    /*
     * Load the SSL library, the digest algorithms and ciphers, as well as the error messages.
     */
    SSL_library_init();
    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();

    /*
     * Create a context that supports SSL version 2 and 3 as well as TLS version 1 to 1.2.
     */
    m_context = SSL_CTX_new(SSLv23_server_method());

    if (m_context == nullptr) {
        LOG(ERROR) << "Failed to create SSL context";
        return;
    }

    /*
     * Load the certificate and the private key and then make sure they are consistent.
     */
    if (SSL_CTX_use_certificate_file(m_context, globalConfig.sslCertificateFile().c_str(), SSL_FILETYPE_PEM) != SSL_SUCCESS) {
        LOG(ERROR) << "Failed to load certificate";
        return;
    }
    if (SSL_CTX_use_PrivateKey_file(m_context, globalConfig.sslPrivateKeyFile().c_str(), SSL_FILETYPE_PEM) != SSL_SUCCESS) {
        LOG(ERROR) << "Failed to load private key";
        return;
    }
    if (SSL_CTX_check_private_key(m_context) != SSL_SUCCESS) {
        LOG(ERROR) << "Key does not match certificate";
        return;
    }
    m_operational = true;
}

/**
 * Frees the allocated resources from the control object.
 */
SslControl::~SslControl() {
    if (m_operational) {
        if (m_context != nullptr)
            SSL_CTX_free(m_context);

        EVP_cleanup();
        ERR_free_strings();
        m_operational = false;
    }
}

/**
 * Attempts to create a SSL/TLS connection.
 *
 * @param   socketFd    File descriptor of the socket
 *
 * @return  The SSL connection object
 *
 * @throws  A runtime error if a connection could not be created
 */
SSL* SslControl::createConnection(int socketFd) {
    if (!m_operational) {
        LOG(ERROR) << "Failed to create SSL connection due to non-operational SSL control";
        throw std::runtime_error("Failed to create SSL connection due to non-operational SSL control");
    }

    SSL* ssl = SSL_new(m_context);

    if (ssl == nullptr) {
        LOG(ERROR) << "Failed to create new SSL object";
        throw std::runtime_error("Failed SSL object creation");
    }

    /*
     * We want to automatically retry reads and writes when a renegotiation takes place. This way
     * the only errors we have to handle are real, permanent ones.
     */
    SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);

    if (SSL_set_fd(ssl, socketFd) != SSL_SUCCESS) {
        LOG(ERROR) << "Failed to associate SSL object with file descriptor";
        SSL_free(ssl);
        throw std::runtime_error("Failed SSL set mode creation");
    }

    int32_t status = SSL_accept(ssl);
    if (status != SSL_SUCCESS) {
        SSL_free(ssl);
        LOG(ERROR) << "SSL accept failure: return code=" << status << ", SSL error=" << SSL_get_error(ssl, status);
        throw std::runtime_error("Failed SSL accept");
    }

    return ssl;
}

/**
 * Frees the resources used for this SSL connection.
 *
 * @param   ssl     The SSL connection object to be freed
 */
void SslControl::tearDownConnection(SSL* const ssl) {
    SSL_free(ssl);
}

