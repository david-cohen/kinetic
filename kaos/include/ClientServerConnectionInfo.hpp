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
    inline int32_t         socketDescriptor() {return m_socketDescriptor;}
    inline uint32_t        serverPort() {return m_serverPort;}
    inline std::string     serverIpAddress() {return m_serverIpAddress;}
    inline uint32_t        clientPort() {return m_clientPort;}
    inline std::string     clientIpAddress() {return m_clientIpAddress;}

private:

    /*
     * Private Data Members
     */
    int32_t         m_socketDescriptor;     //!< File description of the connection's socket
    uint32_t        m_serverPort;           //!< Port number of the server
    std::string     m_serverIpAddress;      //!< IP address of the server
    uint32_t        m_clientPort;           //!< Port number of the client
    std::string     m_clientIpAddress;      //!< IP address of the client
};

#endif
