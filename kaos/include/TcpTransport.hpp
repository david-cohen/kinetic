/*
 * Copyright (c) 2014-2016 Western Digital Technologies, Inc. <copyrightagent@wdc.com>
 * @author Gary Ballance <gary.ballance@wdc.com>
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
#ifndef TCP_TRANSPORT_HPP
#define TCP_TRANSPORT_HPP

/*
 * Include Files
 */
#include <stdint.h>
#include <string>
#include "ClientServerConnectionInfo.hpp"

/**
 * Provides functions to establish new TCP connections with a server or client.
 */
class TcpTransport {
public:
    /*
     * Public Class Function
     */
    static int32_t clientConnect(const std::string& ipAddress, uint32_t port);
    static int32_t serverSetup(uint32_t port);
    static ClientServerConnectionInfo serverConnect(uint32_t serverPort, int32_t listeningSocketDescriptor);
    static void serverShutdown(int32_t socketDescriptor);
};

#endif
