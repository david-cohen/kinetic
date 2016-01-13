/*
 * Copyright (c) [2014 - 2016] Western Digital Technologies, Inc. All rights reserved.
 */
#pragma once
#ifndef TCP_TRANSPORT_HPP
#define TCP_TRANSPORT_HPP

/*
 * Include Files
 */
#include <stdint.h>
#include <string>
#include "Common.hpp"
#include "ClientServerConnectionInfo.hpp"

/**
 * TCP Transport
 *
 * Provides functions to establish new TCP connections for a server or client.
 */
class TcpTransport {
public:

    /*
     * Public Class Function
     */
    static int32_t                    clientConnect(std::string ipAddress, uint32_t port);
    static int32_t                    serverSetup(uint32_t port);
    static ClientServerConnectionInfo serverConnect(uint32_t serverPort, int32_t listeningSocketDescriptor);
    static void                       serverShutdown(int32_t socketDescriptor);

private:
    DISALLOW_COPY_AND_ASSIGN(TcpTransport);
};

#endif
