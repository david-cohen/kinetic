/*
 * Copyright (c) [2014 - 2016] Western Digital Technologies, Inc. All rights reserved.
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
