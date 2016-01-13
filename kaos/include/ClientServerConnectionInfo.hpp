/*
 * Copyright (c) [2015 - 2016] Western Digital Technologies, Inc. All rights reserved.
 */
#pragma once
#ifndef CLIENT_SERVER_CONNECTION_INFO_HPP
#define CLIENT_SERVER_CONNECTION_INFO_HPP

/*
 * Include Files
 */
#include <stdint.h>
#include <string>

class ClientServerConnectionInfo {
public:
    ClientServerConnectionInfo(int32_t socketDescriptor, uint32_t serverPort, std::string serverIpAddress,
                               uint32_t clientPort, std::string clientIpAddress)
        : m_socketDescriptor(socketDescriptor), m_serverPort(serverPort), m_serverIpAddress(serverIpAddress),
          m_clientPort(clientPort), m_clientIpAddress(clientIpAddress) {
    }

    inline int32_t         socketDescriptor() {return m_socketDescriptor;}
    inline uint32_t        serverPort() {return m_serverPort;}
    inline std::string     serverIpAddress() {return m_serverIpAddress;}
    inline uint32_t        clientPort() {return m_clientPort;}
    inline std::string     clientIpAddress() {return m_clientIpAddress;}

private:

    int32_t         m_socketDescriptor;
    uint32_t        m_serverPort;
    std::string     m_serverIpAddress;
    uint32_t        m_clientPort;
    std::string     m_clientIpAddress;
};

#endif
