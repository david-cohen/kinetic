/*
 * Copyright (c) 2014-2016 Western Digital Corporation or its affiliates <copyrightagent@wdc.com>
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
#ifndef CLIENT_SERVER_CONNECTION_INFO_HPP
#define CLIENT_SERVER_CONNECTION_INFO_HPP

/*
 * Include Files
 */
#include <stdint.h>
#include <string>

/**
 * Maintains the IP address and port information for both the client and the server in a connection.
 */
class ClientServerConnectionInfo {
public:
    /*
     * Constructor
     */
    ClientServerConnectionInfo(int32_t socketDescriptor, uint32_t serverPort, std::string serverIpAddress,
                               uint32_t clientPort, std::string clientIpAddress)
        : m_socketDescriptor(socketDescriptor), m_serverPort(serverPort), m_serverIpAddress(serverIpAddress),
          m_clientPort(clientPort), m_clientIpAddress(clientIpAddress) {
    }

    /*
     * Public Accessors
     */
    inline int32_t socketDescriptor() const {return m_socketDescriptor;}
    inline uint32_t serverPort() const {return m_serverPort;}
    inline std::string serverIpAddress() const {return m_serverIpAddress;}
    inline uint32_t clientPort() const {return m_clientPort;}
    inline std::string clientIpAddress() const {return m_clientIpAddress;}

private:
    /*
     * Private Data Members
     */
    const int32_t       m_socketDescriptor;     //!< File description of the connection's socket
    const uint32_t      m_serverPort;           //!< Port number of the server
    const std::string   m_serverIpAddress;      //!< IP address of the server
    const uint32_t      m_clientPort;           //!< Port number of the client
    const std::string   m_clientIpAddress;      //!< IP address of the client
};

#endif
