/*
 * Copyright (c) [2014 - 2016] Western Digital Technologies, Inc. All rights reserved.
 */
#pragma once
#ifndef STREAM_INTERFACE_HPP
#define STREAM_INTERFACE_HPP

/*
 * Include Files
 */
#include <cstddef>

/*
 * Stream Security
 */
enum class Security {
    NONE = 0,
    SSL  = 1,
};

/**
 * Defines the interface for various the data streams (such as encrypted or non-encrypted) used in
 * Kinetic communications.
 */
class StreamInterface {
public:
    virtual ~StreamInterface() {}
    virtual void read(char* buffer, size_t byteCount) = 0;
    virtual void blackHoleRead(size_t byteCount) = 0;
    virtual void write(const char* const buffer, size_t byteCount) = 0;
    virtual void close() = 0;
    virtual Security security() = 0;
};

#endif
