/*
    Copyright (c) [2014 - 2015] Western Digital Technologies, Inc. All rights reserved.
*/

#pragma once
#ifndef SSL_CONTROL_HPP
#define SSL_CONTROL_HPP

/*
    Include Files
*/

#include <stdint.h>
#include <openssl/ssl.h>

class SslControl {
public:
    SslControl();
    ~SslControl();
    SSL* createConnection(int32_t socketFd);
    bool operational() {
        return m_operational;
    }
    static SslControl& instance();

private:
    bool                m_operational;
    SSL_CTX*            m_context;

    static SslControl*  m_instance;
};

#endif
