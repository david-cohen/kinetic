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
#ifndef HEARTBEAT_PROVIDER_HPP
#define HEARTBEAT_PROVIDER_HPP

/*
 * Include Files
 */
#include <netinet/in.h>
#include <atomic>
#include <thread>
#include <string>
#include "Common.hpp"

/**
 * Responsible for sending Kinetic heartbeat messages to the Kinetic UDP multicast address.
 */
class HeartbeatProvider {
public:

    /*
     * Constructor
     */
    HeartbeatProvider();

    /*
     * Public Member Function
     */
    bool start();
    void stop();
    void wait();

private:

    /*
     * Private Member Functions
     */
    void run();
    void openSocket();
    void sendHeartbeatMessage();

    /*
     * Private Data Member
     */
    std::atomic_bool    m_active;       //!< Indicates if provider is active
    std::thread*        m_thread;       //!< Thread that repeatedly sends heartbeat message
    int32_t             m_socketFd;     //!< Socket used to send heartbeat message
    struct sockaddr_in  m_address;      //!< Address information when sending message

    DISALLOW_COPY_AND_ASSIGN(HeartbeatProvider);
};

#endif
