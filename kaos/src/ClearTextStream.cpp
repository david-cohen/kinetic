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
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <memory>
#include <stdexcept>
#include "Common.hpp"
#include "Logger.hpp"
#include "GlobalConfig.hpp"
#include "ClearTextStream.hpp"

/*
 * Constants
 */
const uint32_t  STATUS_END_OF_STREAM(0);

/**
 * Initializes the Clear Text Stream object.
 *
 * @param   streamFd    Stream's file descriptor
 */
ClearTextStream::ClearTextStream(int32_t streamFd)
    : m_streamFd(streamFd) {
}

/**
 * Reads the specified number of bytes into the specified buffer.
 *
 * @param   buffer      Pointer to the buffer the data is to be read into
 * @param   byteCount   The number of bytes to be read
 *
 * @throws  A runtime error if a fatal error was encountered
*/
void ClearTextStream::read(char* buffer, size_t byteCount) {

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
            throw std::runtime_error("Socket closed");
        }

        if (byteCountStatus == STATUS_FAILURE) {
            LOG(ERROR) << "Clear text stream read failure: error code=" << errno << ", description=" << strerror(errno);
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
void ClearTextStream::blackHoleRead(size_t byteCount) {

    /*
     * Loop reading from the socket until the requested amount of data has been received (without
     * keeping any of the received data).
     */
    std::unique_ptr<char> valueBuffer(new char[globalConfig.maxValueSize()]);

    do {
        int32_t byteCountStatus = ::read(m_streamFd, valueBuffer.get(), byteCount > globalConfig.maxValueSize() ? globalConfig.maxValueSize() : byteCount);

        /*
         * If the read failed because it was interrupted (non-fatal error), then retry the operation.
         */
        if ((byteCountStatus == STATUS_FAILURE) && (errno == EINTR))
            continue;

        if (byteCountStatus == STATUS_END_OF_STREAM) {
            close();
            throw std::runtime_error("Socket closed");
        }

        if (byteCountStatus == STATUS_FAILURE) {
            LOG(ERROR) << "Clear text stream read failure: error code=" << errno << ", description=" << strerror(errno);
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
void ClearTextStream::write(const char* const buffer, size_t byteCount) {

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
            throw std::runtime_error("Socket closed");
        }

        if (byteCountStatus == STATUS_FAILURE) {
            LOG(ERROR) << "Clear text stream write failure: error code=" << errno << ", description=" << strerror(errno);
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
void ClearTextStream::close() {

    if (::close(m_streamFd) == STATUS_FAILURE) {
        LOG(ERROR) << "Clear text stream close failure: error code=" << errno << ", description=" << strerror(errno);
    }
}
