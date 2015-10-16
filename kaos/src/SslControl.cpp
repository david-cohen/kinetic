/*
    Copyright (c) [2014 - 2015] Western Digital Technologies, Inc. All rights reserved.
*/

/*
    Include Files
*/

#include <openssl/err.h>
#include <string>
#include <exception>
#include <stdexcept>
#include "Logger.hpp"
#include "SslControl.hpp"
#include "SystemConfig.hpp"

/*
    Data Objects
*/

SslControl* SslControl::m_instance(nullptr);
const int32_t SSL_SUCCESS(1);

/**
    SSL Control Constructor
*/

SslControl::SslControl()
    : m_operational(false), m_context(nullptr) {

    /*
        Load the SSL library, the digest algorithms and ciphers, as well as the error messages.
    */
    SSL_library_init();
    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();

    /*
        Create a context that supports SSL version 2 and 3 as well as TLS version 1 to 1.2.
    */

    m_context = SSL_CTX_new(SSLv23_server_method());

    if (m_context == nullptr) {
        LOG(ERROR) << "Failed to create SSL context" << std::endl;
        return;
    }

    /*
        Load the certificate and the private key and then make sure they are consistent.
    */

    if (SSL_CTX_use_certificate_file(m_context, systemConfig.sslCertificateFile().c_str(), SSL_FILETYPE_PEM) != SSL_SUCCESS) {
        LOG(ERROR) << "Failed to Load Certificate" << std::endl;
        return;
    }
    if (SSL_CTX_use_PrivateKey_file(m_context, systemConfig.sslPrivateKeyFile().c_str(), SSL_FILETYPE_PEM) != SSL_SUCCESS) {
        LOG(ERROR) << "Failed to Load Private Key" << std::endl;
        return;
    }
    if (SSL_CTX_check_private_key(m_context) != SSL_SUCCESS) {
        LOG(ERROR) << "Key Does Not Match Certificate" << std::endl;
        return;
    }
    m_operational = true;
}

/**
    SSL Control Destructor
*/

SslControl::~SslControl() {

    if (m_context != nullptr)
        SSL_CTX_free(m_context);

    EVP_cleanup();
    ERR_free_strings();
}

/*
    Create Connection

    @param socketFd     file descriptor of the socket
*/

SSL* SslControl::createConnection(int socketFd) {

    SSL* ssl = SSL_new(m_context);

    // We want to automatically retry reads and writes when a renegotiation
    // takes place. This way the only errors we have to handle are real,
    // permanent ones.

    if (ssl == nullptr) {
        LOG(ERROR) << "Failed to create new SSL object";
        throw std::runtime_error("failed SSL oobject creation");
    }

    SSL_set_mode(ssl, SSL_MODE_AUTO_RETRY);

    if (SSL_set_fd(ssl, socketFd) != 1) {
        LOG(ERROR) << "Failed to associate SSL object with file descriptor";
        SSL_free(ssl);
        throw std::runtime_error("failed SSL set mode creation");
    }

    int32_t status = SSL_accept(ssl);

    if (status == 0) {
        SSL_free(ssl);
        throw std::runtime_error("socket closed");
    }

    if (status < 0) {
        SSL_free(ssl);
        LOG(ERROR) << "SSL accept failure: return_code=" << status << ", ssl_error=" << SSL_get_error(ssl, status);
        throw std::runtime_error("failed to perform SSL accpet");
    }

    return ssl;
}

/**
    Instance

    @return an instance of the (singleton) SSL control object
*/

SslControl& SslControl::instance() {
    if (m_instance == nullptr)
        m_instance = new SslControl();

    return *m_instance;
}

