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

/*
 * Include Files
 */
#include <errno.h>
#include <unistd.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string>
#include <stdexcept>
#include "Logger.hpp"
#include "TcpTransport.hpp"
#include "GlobalConfig.hpp"

/**
 * Sets up the server by creating the listening socket for it to use to detect new connections.
 *
 * @param   port  The port number the server is to listen on for new connections
 *
 * @return  The listening port socket's file descriptor
 *
 * @throws  A runtime error if the setup fails
 */
int32_t TcpTransport::serverSetup(uint32_t port) {
    /*
     * Create a connection-oriented communication path and allow the same source address and port to
     * be reused.
     */
    int32_t listeningSocketDescriptor = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (listeningSocketDescriptor == STATUS_FAILURE)
        throw std::runtime_error("Failed to create socket: error code=" + std::to_string(errno) + ", description=" + std::string(strerror(errno)));

    const int OPTION_SET(1);
    if (setsockopt(listeningSocketDescriptor, SOL_SOCKET, SO_REUSEADDR, &OPTION_SET, sizeof(OPTION_SET)) == STATUS_FAILURE)
        throw std::runtime_error("Failed to set socket option SO_REUSEADDR: error code=" + std::to_string(errno)
                                 + ", description=" + std::string(strerror(errno)));

    /*
     * Bind the server address and port to the socket and then begin listening for client connection
     * requests.
     */
    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);

    if (bind(listeningSocketDescriptor, (struct sockaddr*) &server, sizeof(struct sockaddr)) == STATUS_FAILURE)
        throw std::runtime_error("Failed to bind socket on port " + std::to_string(port) + ": error code="
                                 + std::to_string(errno) + ", description=" + std::string(strerror(errno)));

    if (listen(listeningSocketDescriptor, globalConfig.maxPendingConnections()) == STATUS_FAILURE)
        throw std::runtime_error("Failed to listen to socket on port " + std::to_string(port) + ": error code="
                                 + std::to_string(errno) + ", description=" + std::string(strerror(errno)));

    return listeningSocketDescriptor;
}

/**
 * Attempts to connect to a client by listening on a specific port.  If successful, it will return
 * server and client connection information.
 *
 * @param   serverPort                  The server's TCP port number
 * @param   listeningSocketDescriptor   The file descriptor of the socket to listen on
 *
 * @return  The IP address and port number of both the client and the server for the connection
 *
 * @throws  A runtime error if a connection fails
 */
ClientServerConnectionInfo TcpTransport::serverConnect(uint32_t serverPort, int32_t listeningSocketDescriptor) {
    /*
     * Wait for an incoming connection.  When one is received, create a connection handle to process
     * all requests through that connection.
     */
    struct sockaddr_in client;
    socklen_t sin_size = sizeof(struct sockaddr_in);

    int32_t newConnectionSocket = accept(listeningSocketDescriptor, (struct sockaddr*) &client, &sin_size);
    if (newConnectionSocket == STATUS_FAILURE)
        throw std::runtime_error("Failed to accept connection on port " + std::to_string(serverPort) + ": error code="
                                 + std::to_string(errno) + ", description=" + std::string(strerror(errno)));

    std::string serverIpAddress("unknown");
    std::string clientIpAddress("unknown");

    struct sockaddr_in socketInfo;
    socklen_t byteCount(sizeof(socketInfo));
    char serverIpAddressBuffer[INET_ADDRSTRLEN];
    if ((getsockname(newConnectionSocket, (struct sockaddr*) &socketInfo, &byteCount) == STATUS_SUCCESS)
            && (inet_ntop(AF_INET, &socketInfo.sin_addr, serverIpAddressBuffer, INET_ADDRSTRLEN) != nullptr)) {
        serverIpAddress.assign(serverIpAddressBuffer);
    }

    char clientIpAddressBuffer[INET_ADDRSTRLEN];
    if (inet_ntop(AF_INET, &client.sin_addr, clientIpAddressBuffer, INET_ADDRSTRLEN) != nullptr)
        clientIpAddress.assign(clientIpAddressBuffer);

    ClientServerConnectionInfo clientServerConnectionInfo(newConnectionSocket, serverPort, serverIpAddress, ntohs(client.sin_port), clientIpAddress);
    return clientServerConnectionInfo;
}

/**
 * Shuts down the server socket, closing it.
 *
 * @param   socketDescriptor  File descriptor of socket to shutdown
 */
void TcpTransport::serverShutdown(int32_t socketDescriptor) {
    shutdown(socketDescriptor, SHUT_RDWR);
}

/**
 * Attempts to connect to a server with the specified IP address and port.  If successful, it will
 * return the socket descriptor for the new connection.
 *
 * @param   ipAddress   The IP address of the server that the client wants to connect to
 * @param   port        The port number of the server that the client wants to connect to
 *
 * @return  The socket descriptor for the client connection
 *
 * @throws  A runtime error if socket or connection creation fails
 */
int32_t TcpTransport::clientConnect(const std::string& ipAddress, uint32_t port) {
    const int USE_DEFAULT_PROTOCOL(0);
    int32_t socketDescriptor = socket(AF_INET, SOCK_STREAM, USE_DEFAULT_PROTOCOL);

    if (socketDescriptor == STATUS_FAILURE)
        throw std::runtime_error("Failed to create socket on port " + std::to_string(port) + ": error code="
                                 + std::to_string(errno) + ", description=" + std::string(strerror(errno)));

    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(ipAddress.c_str());
    server.sin_port = htons(port);

    if (connect(socketDescriptor, (struct sockaddr*) &server, sizeof(server)) == STATUS_FAILURE)
        throw std::runtime_error("Failed to connect on port " + std::to_string(port) + ": error code="
                                 + std::to_string(errno) + ", description=" + std::string(strerror(errno)));

    return socketDescriptor;
}
