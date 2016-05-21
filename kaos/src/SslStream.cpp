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

/*
 * Include Files
 */
#include <stdint.h>
#include <unistd.h>
#include <memory>
#include <stdexcept>
#include "Common.hpp"
#include "Logger.hpp"
#include "SslStream.hpp"
#include "SslControl.hpp"
#include "GlobalConfig.hpp"

/*
 * Private Data Objects
 */
static SslControl sslControl;

/**
 * Initialize the SSL stream object.
 *
 * @param   socketDescriptor    Stream socket's file descriptor
 */
SslStream::SslStream(int32_t socketDescriptor)
    : m_streamFd(socketDescriptor), m_ssl(sslControl.createConnection(socketDescriptor)) {
}

/**
 * Tear down the SSL connection object.
 */
SslStream::~SslStream() {

    sslControl.tearDownConnection(m_ssl);
}

/**
 * Reads the specified number of bytes into the specified buffer.
 *
 * @param   buffer      Pointer to the buffer the data is to be read into
 * @param   byteCount   The number of bytes to be read
 *
 * @throws  A runtime error if a fatal error was encountered
 */
void SslStream::read(char* buffer, size_t byteCount) {

    /*
     * Loop reading from the socket until the requested amount of data has been received.
     */
    int32_t bufferIndex = 0;
    do {
        int32_t byteCountStatus = SSL_read(m_ssl, &buffer[bufferIndex], byteCount);

        if (byteCountStatus == 0) {
            close();
            throw std::runtime_error("Socket closed");
        }

        if (byteCountStatus < 0) {
            LOG(ERROR) << "SSL stream read failure: return code=" << byteCountStatus << ", SSL error=" << SSL_get_error(m_ssl, byteCountStatus);
            close();
            throw std::runtime_error("Failed read");
        }

        byteCount -= byteCountStatus;
        bufferIndex += byteCountStatus;
    }
    while (byteCount > 0);
}

/**
 * Reads and discards the specified number of bytes.
 *
 * @param   byteCount   The number of bytes to be read
 *
 * @throws  A runtime error if a fatal error was encountered
 */
void SslStream::blackHoleRead(size_t byteCount) {

    /*
     * Loop reading from the socket until the requested amount of data has been received (without
     * keeping any of the received data).
     */
    std::unique_ptr<char> valueBuffer(new char[globalConfig.maxValueSize()]);

    do {
        int32_t byteCountStatus = SSL_read(m_ssl, valueBuffer.get(), byteCount > globalConfig.maxValueSize() ? globalConfig.maxValueSize() : byteCount);

        if (byteCountStatus == 0) {
            close();
            throw std::runtime_error("Socket closed");
        }

        if (byteCountStatus < 0) {
            LOG(ERROR) << "SSL stream read failure: return code=" << byteCountStatus << ", SSL error=" << SSL_get_error(m_ssl, byteCountStatus);
            close();
            throw std::runtime_error("Failed read");
        }

        byteCount -= byteCountStatus;
    }
    while (byteCount > 0);
}

/**
 * Writes the specified number of bytes from the specified buffer.
 *
 * @param   buffer      Pointer to the buffer the data is to be written to
 * @param   byteCount   The number of bytes to be written
 *
 * @throws  A runtime error if a fatal error was encountered
 */
void SslStream::write(const char* const buffer, size_t byteCount) {
    /*
     * Loop writing to the socket until the requested amount of data has been sent.
     */
    int32_t bufferIndex = 0;
    do {
        int32_t byteCountStatus = SSL_write(m_ssl, &buffer[bufferIndex], byteCount);

        if (byteCountStatus == 0) {
            close();
            throw std::runtime_error("Socket closed");
        }

        if (byteCountStatus < 0) {
            LOG(ERROR) << "SSL stream write failure: return code=" << byteCountStatus << ", SSL error=" << SSL_get_error(m_ssl, byteCountStatus);
            close();
            throw std::runtime_error("Failed write");
        }

        byteCount -= byteCountStatus;
        bufferIndex += byteCountStatus;
    }
    while (byteCount > 0);
}

/**
 * Closes the stream.
 */
void SslStream::close() {

    if (::close(m_streamFd) == STATUS_FAILURE) {
        LOG(ERROR) << "SSL stream close failure: error code=" << errno << ", description=" << strerror(errno);
    }
}
