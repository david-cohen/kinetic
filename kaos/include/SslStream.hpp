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
#ifndef SSL_STREAM_HPP
#define SSL_STREAM_HPP

/*
 * Include Files
 */
#include <stdint.h>
#include "openssl/ssl.h"
#include "StreamInterface.hpp"

/**
 * A stream object that transfers data encrypted using SSL/TLS.
 */
class SslStream : public StreamInterface {
public:
    /*
     * Constructor/Destructor
     */
    explicit SslStream(int32_t socketDescriptor);
    ~SslStream();

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
