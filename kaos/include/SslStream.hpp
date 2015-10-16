/*
    Copyright (c) [2014 - 2015] Western Digital Technologies, Inc. All rights reserved.
*/

#pragma once
#ifndef SSL_STREAM_HPP
#define SSL_STREAM_HPP

/*
    Include Files
*/

#include <stdint.h>
#include "openssl/ssl.h"
#include "StreamInterface.hpp"

class SslStream : public StreamInterface {
public:
    explicit SslStream(int32_t streamFd, SSL* ssl);
    void read(char* buffer, size_t byteCount);
    void blackHoleRead(size_t byteCount);
    void write(const char* const buffer, size_t byteCount);
    void close();

private:
    int32_t     m_streamFd;
    SSL*        m_ssl;
};

#endif
