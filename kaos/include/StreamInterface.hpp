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
