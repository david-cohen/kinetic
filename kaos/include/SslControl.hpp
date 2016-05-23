/*
 * Copyright (c) 2014-2016 Western Digital Technologies, Inc. <copyrightagent@wdc.com>
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
#pragma once
#ifndef SSL_CONTROL_HPP
#define SSL_CONTROL_HPP

/*
 * Include Files
 */
#include <stdint.h>
#include <openssl/ssl.h>

/**
 * Provides SSL connection creation capabilities.
 */
class SslControl {
public:
    /*
     * Constructor/Destructor
     */
    SslControl();
    ~SslControl();

    /*
     * Public Member Functions
     */
    SSL* createConnection(int32_t socketFd);
    void tearDownConnection(SSL* const ssl);

private:
    /*
     * Private Data Members
     */
    bool        m_operational;  //!< True if the required libraries, certificate and private key were loaded successfully
    SSL_CTX*    m_context;      //!< Object needed to establish TLS/SSL enabled connection
};

#endif
