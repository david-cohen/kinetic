/*
    Copyright (c) [2014 - 2015] Western Digital Technologies, Inc. All rights reserved.
*/

#pragma once
#ifndef STREAM_INTERFACE_HPP
#define STREAM_INTERFACE_HPP

#include <cstddef>

class StreamInterface {
public:
    virtual ~StreamInterface() {}
    virtual void read(char* buffer, size_t byteCount) = 0;
    virtual void blackHoleRead(size_t byteCount) = 0;
    virtual void write(const char* const buffer, size_t byteCount) = 0;
    virtual void close() = 0;
};

#endif
