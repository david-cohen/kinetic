/*
 * Copyright (c) [2014 - 2016] Western Digital Technologies, Inc.
 *
 * This code is CONFIDENTIAL and a TRADE SECRET of Western Digital Technologies, Inc. and its
 * affiliates ("WD").  This code is protected under copyright laws as an unpublished work of WD.
 * Notice is for informational purposes only and does not imply publication.
 *
 * The receipt or possession of this code does not convey any rights to reproduce or disclose its
 * contents, or to manufacture, use, or sell anything that it may describe, in whole or in part,
 * without the specific written consent of WD.  Any reproduction or distribution of this code
 * without the express written consent of WD is strictly prohibited, is a violation of the copyright
 * laws, and may subject you to criminal prosecution.
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
    void tearDownConnection(SSL* ssl);
    bool operational() {return m_operational;}

private:
    /*
     * Private Data Members
     */
    bool        m_operational;  //!< True if the required libraries, certificate and private key were loaded successfully
    SSL_CTX*    m_context;      //!< Object needed to establish TLS/SSL enabled connection
};

extern SslControl sslControl;

#endif
