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
