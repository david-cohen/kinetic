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
