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
 * SSL Control
 *
 * Used to create SSL connections.
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
    bool        m_operational;
    SSL_CTX*    m_context;
};

extern SslControl sslControl;

#endif
