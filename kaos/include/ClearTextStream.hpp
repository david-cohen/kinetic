/*
 * Copyright (c) [2014 - 2016] Western Digital Technologies, Inc. All rights reserved.
 */
#pragma once
#ifndef CLEAR_TEXT_STREAM_HPP
#define CLEAR_TEXT_STREAM_HPP

/*
 * Include Files
 */
#include <stdint.h>
#include "StreamInterface.hpp"

/**
 * A text stream object that transfers data "in the clear", not utilization any encryption or
 * authentication.
 */
class ClearTextStream : public StreamInterface {
public:

    /*
     * Constructor
     */
    explicit ClearTextStream(int32_t streamFd);

    /*
     * Public Member Functions
     */
    void read(char* buffer, size_t byteCount);
    void blackHoleRead(size_t byteCount);
    void write(const char* const buffer, size_t byteCount);
    void close();
    Security security() {return Security::NONE;}

private:

    /*
     * Private Data Members
     */
    int32_t m_streamFd;  //!< File descriptor for the stream's socket
};

#endif
