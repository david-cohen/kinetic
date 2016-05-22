/*
 * Copyright (c) 2014-2016 Western Digital Technologies, Inc. <copyrightagent@wdc.com>
 *
 * SPDX-License-Identifier: GPL-2.0+
 * This file is part of Kinetic Advanced Object Store (KAOS).
 *
 * This program is free software: you may copy, redistribute and/or modify it under the terms of the
 * GNU General Public License as published by the Free Software Foundation, either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
 * even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program; if
 * not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA. <http://www.gnu.org/licenses/>
 */
#pragma once
#ifndef SSL_STREAM_HPP
#define SSL_STREAM_HPP

/*
 * Include Files
 */
#include <stdint.h>
#include "openssl/ssl.h"
#include "StreamInterface.hpp"

/**
 * A stream object that transfers data encrypted using SSL/TLS.
 */
class SslStream : public StreamInterface {
public:
    /*
     * Constructor/Destructor
     */
    explicit SslStream(int32_t socketDescriptor);
    ~SslStream();

    /*
     * Public Member Functions
     */
    void read(char* buffer, size_t byteCount);
    void blackHoleRead(size_t byteCount);
    void write(const char* const buffer, size_t byteCount);
    void close();
    Security security() {return Security::SSL;}

private:

    /*
     * Private Data Members
     */
    int32_t     m_streamFd;     //!< File descriptor for the stream's socket
    SSL*        m_ssl;          //!< Object that manages the SSL connection
};

#endif
