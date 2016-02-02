/*
 * Copyright (c) [2014 - 2016] Western Digital Technologies, Inc. All rights reserved.
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
#include "Common.hpp"
#include "Logger.hpp"
#include "TcpTransport.hpp"
#include "SystemConfig.hpp"

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
        throw std::runtime_error("Failed to create socket: Error Code=" + toString(errno) + ", Description=" + toString(strerror(errno)));

    const int OPTION_SET(1);
    if (setsockopt(listeningSocketDescriptor, SOL_SOCKET, SO_REUSEADDR, &OPTION_SET, sizeof(OPTION_SET)) == STATUS_FAILURE)
        throw std::runtime_error("Failed to set socket options SO_REUSEADDR: Error Code=" + toString(errno) + ", Description=" + toString(strerror(errno)));

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
        throw std::runtime_error("Failed to bind socket: Error Code=" + toString(errno) + ", Description=" + toString(strerror(errno)));

    if (listen(listeningSocketDescriptor, systemConfig.maxPendingAdminConnections()) == STATUS_FAILURE)
        throw std::runtime_error("Failed to listen on socket: Error Code=" + toString(errno) + ", Description=" + toString(strerror(errno)));

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
        throw std::runtime_error("Failed to accept connection: Error Code=" + toString(errno) + ", Description=" + toString(strerror(errno)));

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
int32_t TcpTransport::clientConnect(std::string ipAddress, uint32_t port) {

    const int USE_DEFAULT_PROTOCOL(0);
    int32_t socketDescriptor = socket(AF_INET, SOCK_STREAM, USE_DEFAULT_PROTOCOL);

    if (socketDescriptor == STATUS_FAILURE)
        throw std::runtime_error("Failed to create socket: Error Code=" + toString(errno) + ", Description=" + toString(strerror(errno)));

    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(ipAddress.c_str());
    server.sin_port = htons(port);

    if (connect(socketDescriptor, (struct sockaddr*) &server, sizeof(server)) == STATUS_FAILURE)
        throw std::runtime_error("Failed to connect: Error Code=" + toString(errno) + ", Description=" + toString(strerror(errno)));

    return socketDescriptor;
}
