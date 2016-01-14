/*
 * Copyright (c) [2014 - 2016] Western Digital Technologies, Inc. All rights reserved.
 */

/*
 * Include Files
 */
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <memory>
#include <stdexcept>
#include "Common.hpp"
#include "Logger.hpp"
#include "SystemConfig.hpp"
#include "ClearTextStream.hpp"

/*
 * Constants
 */
const uint32_t  STATUS_END_OF_STREAM(0);

/**
 * Clear Text Stream Constructor
 *
 * @param  streamFd    Stream's file descriptor
 */
ClearTextStream::ClearTextStream(int32_t streamFd)
    : m_streamFd(streamFd) {
}

/**
 * Read
 *
 * @param  buffer      Pointer to the buffer the data is to be read into
 * @param  byteCount   the number of bytes to be read
 *
 * Reads the specified number of bytes into the specified buffer.
*/
void
ClearTextStream::read(char* buffer, size_t byteCount) {

    /*
     * Loop reading from the socket until the requested amount of data has been received.
     */
    int32_t bufferIndex = 0;
    do {
        int32_t byteCountStatus = ::read(m_streamFd, &buffer[bufferIndex], byteCount);

        /*
         * If the read failed because it was interrupted (non-fatal error), then retry the operation.
         */
        if ((byteCountStatus == STATUS_FAILURE) && (errno == EINTR))
            continue;

        if (byteCountStatus == STATUS_END_OF_STREAM) {
            close();
            throw std::runtime_error("socket closed");
        }

        if (byteCountStatus == STATUS_FAILURE) {
            LOG(ERROR) << "TCP Read Failure: Error Code=" << errno << ", Error Description=" << strerror(errno);
            close();
            throw std::runtime_error("failed read");
        }

        byteCount -= byteCountStatus;
        bufferIndex += byteCountStatus;
    }
    while (byteCount > 0);
}

/**
 * Black Hole Read
 *
 * @param  byteCount   the number of bytes to be read
 *
 * Read and discard the specified number of bytes.
 */
void
ClearTextStream::blackHoleRead(size_t byteCount) {

    /*
     * Loop reading from the socket until the requested amount of data has been received (without
     * keeping any of the received data).
     */
    std::unique_ptr<char> valueBuffer(new char[systemConfig.maxValueSize()]);

    do {
        int32_t byteCountStatus = ::read(m_streamFd, valueBuffer.get(), byteCount > systemConfig.maxValueSize() ? systemConfig.maxValueSize() : byteCount);

        /*
         * If the read failed because it was interrupted (non-fatal error), then retry the operation.
         */
        if ((byteCountStatus == STATUS_FAILURE) && (errno == EINTR))
            continue;

        if (byteCountStatus == STATUS_END_OF_STREAM) {
            close();
            throw std::runtime_error("socket closed");
        }

        if (byteCountStatus == STATUS_FAILURE) {
            LOG(ERROR) << "TCP Read Failure: Error Code=" << errno << ", Error Description=" << strerror(errno);
            close();
            throw std::runtime_error("failed read");
        }

        byteCount -= byteCountStatus;
    }
    while (byteCount > 0);
}

/**
 * Write
 *
 * @param  buffer      Pointer to the buffer the data is to be written to
 * @param  byteCount   the number of bytes to be written
 *
 * Write the number of bytes specified from the buffer specified.
 */
void
ClearTextStream::write(const char* const buffer, size_t byteCount) {

    /*
     * Loop writing to the socket until the requested amount of data has been sent.
     */
    int32_t bufferIndex = 0;
    do {
        int32_t byteCountStatus = ::write(m_streamFd, &buffer[bufferIndex], byteCount);

        /*
         * If the write failed because it was interrupted (non-fatal error), then retry the
         * operation.
         */
        if ((byteCountStatus == STATUS_FAILURE) && (errno == EINTR))
            continue;

        if (byteCountStatus == STATUS_END_OF_STREAM) {
            close();
            throw std::runtime_error("socket closed");
        }

        if (byteCountStatus == STATUS_FAILURE) {
            LOG(ERROR) << "TCP Write Failure: Error Code=" << errno << ", Error Description=" << strerror(errno);
            close();
            throw std::runtime_error("failed write");
        }

        byteCount -= byteCountStatus;
        bufferIndex += byteCountStatus;
    }
    while (byteCount > 0);
}

/**
 * Close
 *
 * Close the stream.
 */
void
ClearTextStream::close() {

    if (::close(m_streamFd) == STATUS_FAILURE) {
        LOG(ERROR) << "TCP close failure: error_code=" << errno << ", error_description=" << strerror(errno);
    }
}
