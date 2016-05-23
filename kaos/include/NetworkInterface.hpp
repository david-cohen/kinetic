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
#ifndef NETWORK_INTERFACE_HPP
#define NETWORK_INTERFACE_HPP

/*
 * Include Files
 */
#include <stdint.h>
#include <memory>
#include <string>
#include <unordered_map>

/**
 * Describes the attributes of a network interface.
 */
class NetworkInterface {
public:
    /*
     * Constructor
     */
    NetworkInterface(std::string m_name, std::string m_macAddress, std::string m_ipv4, std::string m_ipv6)
        : m_name(m_name), m_macAddress(m_macAddress), m_ipv4(m_ipv4), m_ipv6(m_ipv6) {}

    /*
     * Public Accessors
     */
    std::string name() const {return m_name;}
    std::string macAddress() const {return m_macAddress;}
    std::string ipv4() const {return m_ipv4;}
    std::string ipv6() const {return m_ipv6;}
private:
    /*
     * Private Data Members
     */
    const std::string   m_name;         //!< Assigned name of network interface
    const std::string   m_macAddress;   //!< MAC address
    const std::string   m_ipv4;         //!< IP address version 4
    const std::string   m_ipv6;         //!< IP address version 6
};

/*
 * Network Interface Shared Pointer and Unordered Map
 */

typedef std::shared_ptr<NetworkInterface> NetworkInterfacePtr;
typedef std::unordered_map<std::string, NetworkInterfacePtr> NetworkInterfaceMap;

#endif
