/*
    Copyright (c) [2014 - 2015] Western Digital Technologies, Inc. All rights reserved.
*/

/*
    Include Files
*/

#include <stdint.h>
#include <unistd.h>
#include <memory>
#include <stdexcept>
#include "Common.hpp"
#include "Logger.hpp"
#include "SslStream.hpp"
#include "SystemConfig.hpp"

/*
    Clear Text Stream Constructor

    @param  streamFd    Stream's file descrptor
*/

SslStream::SslStream(int32_t streamFd, SSL* ssl) : m_streamFd(streamFd), m_ssl(ssl) {
}

/**
    Read

    @param  buffer      Pointer to the buffer the data is to be read into
    @param  byteCount   the number of bytes to be read
*/

void
SslStream::read(char* buffer, size_t byteCount) {

    /*
        Loop reading from the socket until the requested amount of data has been received.
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
    Black Hole Read

    @param  byteCount   the number of bytes to be read

    Read and discard the specified number of bytes.
*/

void
SslStream::blackHoleRead(size_t byteCount) {

    /*
        Loop reading from the socket until the requested amount of data has been received (without
        keeping any of the received data).
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
    Write

    @param  buffer      Pointer to the buffer the data is to be written to
    @param  byteCount   the number of bytes to be written

    Write the number of bytes specified from the buffer specified.
*/

void
SslStream::write(const char* const buffer, size_t byteCount) {
    /*
        Loop writing to the socket until the requested amount of data has been sent.
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
    Close
*/

void
SslStream::close() {

    if (::close(m_streamFd) == STATUS_FAILURE) {
        LOG(ERROR) << "TCP close failure: error_code=" << errno << ", error_description=" << strerror(errno);
    }
}
