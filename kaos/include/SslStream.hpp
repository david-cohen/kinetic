/*
 * Copyright (c) [2014 - 2016] Western Digital Technologies, Inc. All rights reserved.
 */
#pragma once
#ifndef SSL_STREAM_HPP
#define SSL_STREAM_HPP

/*
 * Include Files
 */
#include <stdint.h>
#include "openssl/ssl.h"
#include "StreamInterface.hpp"

/**
 * SSL Stream
 *
 * A stream that transfers encryption data using SSL/TLS.
 */
class SslStream : public StreamInterface {
public:
    /*
     * Constructor/Destructor
     */
    explicit SslStream(int32_t socketDescriptor);

    /*
     * Public Member Functions
     */
    void read(char* buffer, size_t byteCount);
    void blackHoleRead(size_t byteCount);
    void write(const char* const buffer, size_t byteCount);
    void close();
    Security security() {return Security::SSL;}

private:

    /*
     * Private Data Members
     */
    int32_t     m_streamFd;     //!< File descriptor for the stream's socket
    SSL*        m_ssl;          //!< Object that manages the SSL connection
};

#endif
