/*
 * Copyright (c) [2014 - 2016] Western Digital Technologies, Inc. All rights reserved.
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
#include "SystemConfig.hpp"

/**
 * SSL Stream Constructor
 *
 * @param   socketDescriptor    Stream socket's file descriptor
 */
SslStream::SslStream(int32_t socketDescriptor)
    : m_streamFd(socketDescriptor), m_ssl(sslControl.createConnection(socketDescriptor)) {
}

/**
 * Reads the specified number of bytes into the specified buffer.
 *
 * @param   buffer      Pointer to the buffer the data is to be read into
 * @param   byteCount   The number of bytes to be read
 */
void SslStream::read(char* buffer, size_t byteCount) {

    /*
     * Loop reading from the socket until the requested amount of data has been received.
     */
    int32_t bufferIndex = 0;
    do {
        int32_t byteCountStatus = SSL_read(m_ssl, &buffer[bufferIndex], byteCount);

        if (byteCountStatus == 0) {
            // need to free SSL struct
            close();
            throw std::runtime_error("socket closed");
        }

        if (byteCountStatus < 0) {
            LOG(ERROR) << "SSL read failure: return_code=" << byteCountStatus << ", ssl_error=" << SSL_get_error(m_ssl, byteCountStatus);
            // need to free SSL struct
            close();
            throw std::runtime_error("failed read");
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
 */
void SslStream::blackHoleRead(size_t byteCount) {

    /*
     * Loop reading from the socket until the requested amount of data has been received (without
     * keeping any of the received data).
     */
    std::unique_ptr<char> valueBuffer(new char[systemConfig.maxValueSize()]);

    do {
        int32_t byteCountStatus = SSL_read(m_ssl, valueBuffer.get(), byteCount > systemConfig.maxValueSize() ? systemConfig.maxValueSize() : byteCount);

        if (byteCountStatus == 0) {
            // need to free SSL struct
            close();
            throw std::runtime_error("socket closed");
        }

        if (byteCountStatus < 0) {
            LOG(ERROR) << "SSL read failure: return_code=" << byteCountStatus << ", ssl_error=" << SSL_get_error(m_ssl, byteCountStatus);
            // need to free SSL struct
            close();
            throw std::runtime_error("failed read");
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
 */
void SslStream::write(const char* const buffer, size_t byteCount) {
    /*
     * Loop writing to the socket until the requested amount of data has been sent.
     */
    int32_t bufferIndex = 0;
    do {
        int32_t byteCountStatus = SSL_write(m_ssl, &buffer[bufferIndex], byteCount);

        if (byteCountStatus == 0) {
            // need to free SSL struct
            close();
            throw std::runtime_error("socket closed");
        }

        if (byteCountStatus < 0) {
            LOG(ERROR) << "SSL write failure: return_code=" << byteCountStatus << ", ssl_error=" << SSL_get_error(m_ssl, byteCountStatus);
            // need to free SSL struct
            close();
            throw std::runtime_error("failed write");
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
        LOG(ERROR) << "TCP close failure: error_code=" << errno << ", error_description=" << strerror(errno);
    }
}
