/*
 * Copyright (c) 2016 Western Digital Technologies, Inc.
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
    std::string name() {return m_name;}
    std::string macAddress() {return m_macAddress;}
    std::string ipv4() {return m_ipv4;}
    std::string ipv6() {return m_ipv6;}
private:
    /*
     * Private Data Members
     */
    std::string m_name;         //!< Assigned name of network interface
    std::string m_macAddress;   //!< MAC address
    std::string m_ipv4;         //!< IP address version 4
    std::string m_ipv6;         //!< IP address version 6
};

/*
 * Network Interface Shared Pointer and Unordered Map
 */

typedef std::shared_ptr<NetworkInterface> NetworkInterfacePtr;
typedef std::unordered_map<std::string, NetworkInterfacePtr> NetworkInterfaceMap;

#endif
