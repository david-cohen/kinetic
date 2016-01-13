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
#include <thread>
#include <exception>
#include <stdexcept>
#include "Common.hpp"
#include "Logger.hpp"
#include "TcpTransport.hpp"
#include "SystemConfig.hpp"

/*
 * Used Namespaces
 */
using std::string;

/**
 * Server Setup
 *
 * @param port The port number the server is to listen on for new connections
 *
 * @return the listening port socket's file descriptor
 */
int32_t TcpTransport::serverSetup(uint32_t port) {

    /*
     * Create a connection-oriented communication path and allow the same source address and port to
     * be reused.
     */
    int32_t listeningSocketDescriptor = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (listeningSocketDescriptor == STATUS_FAILURE)
        throw std::runtime_error("Failed to create socket: error_code=" + toString(errno) + ", description=" + string(strerror(errno)));

    const int OPTION_SET(1);
    if (setsockopt(listeningSocketDescriptor, SOL_SOCKET, SO_REUSEADDR, &OPTION_SET, sizeof(OPTION_SET)) == STATUS_FAILURE)
        throw std::runtime_error("Failed to set socket options SO_REUSEADDR: error_code=" + toString(errno) + ", description=" + string(strerror(errno)));

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
        throw std::runtime_error("Failed to bind socket: error_code=" + toString(errno) + ", description=" + string(strerror(errno)));

    if (listen(listeningSocketDescriptor, systemConfig.maxPendingAdminConnections()) == STATUS_FAILURE)
        throw std::runtime_error("Failed to listen on socket: error_code=" + toString(errno) + ", description=" + string(strerror(errno)));

    return listeningSocketDescriptor;
}

/**
 * Server Connect
 *
 * This function is called by the thread that will manage the TCP transport.  It listens for
 * client connections and creates a connection handler for each new connection.
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
        throw std::runtime_error("Failed to accept connection: error_code=" + toString(errno) + ", description=" + string(strerror(errno)));

    string serverIpAddress("unknown");
    string clientIpAddress("unknown");

    struct sockaddr_in socketInfo;
    socklen_t byteCount(sizeof(socketInfo));
    char serverIpAddressBuffer[INET_ADDRSTRLEN];
    if ((getsockname(newConnectionSocket, (struct sockaddr*) &socketInfo, &byteCount) == STATUS_SUCCESS)
            && (inet_ntop(AF_INET, &socketInfo.sin_addr, serverIpAddressBuffer, INET_ADDRSTRLEN) != nullptr)) {

        serverIpAddress = string(serverIpAddressBuffer);
    }

    char clientIpAddressBuffer[INET_ADDRSTRLEN];
    if (inet_ntop(AF_INET, &client.sin_addr, clientIpAddressBuffer, INET_ADDRSTRLEN) != nullptr)
        clientIpAddress = string(clientIpAddressBuffer);

    ClientServerConnectionInfo clientServerConnectionInfo(newConnectionSocket, serverPort, serverIpAddress, ntohs(client.sin_port), clientIpAddress);
    return clientServerConnectionInfo;
}

/**
 * Server Shutdown
 *
 * @param socketDescriptor  File descriptor of socket to shutdown
 */
void TcpTransport::serverShutdown(int32_t socketDescriptor) {
    shutdown(socketDescriptor, SHUT_RDWR);
}

/**
 * Client Connect
 *
 * @param ipAddress     The IP address of the server that the client wants to connect to
 * @param port          The port number of the server that the client wants to connect to
 *
 * @throw runtime_error for socket creation or connection failure
 */
int32_t TcpTransport::clientConnect(string ipAddress, uint32_t port) {

    const int USE_DEFAULT_PROTOCOL(0);
    int32_t socketDescriptor = socket(AF_INET, SOCK_STREAM, USE_DEFAULT_PROTOCOL);

    if (socketDescriptor == STATUS_FAILURE)
        throw std::runtime_error("Failed to create socket: error_code=" + toString(errno) + ", description=" + string(strerror(errno)));

    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(ipAddress.c_str());
    server.sin_port = htons(port);

    if (connect(socketDescriptor, (struct sockaddr*) &server, sizeof(server)) == STATUS_FAILURE)
        throw std::runtime_error("Failed to connect: error_code=" + toString(errno) + ", description=" + string(strerror(errno)));

    return socketDescriptor;
}

/*
    string serverIpAddressString("unknown");
    string clientIpAddressString("unknown");

    struct sockaddr_in socketInfo;
    socklen_t byteCount(sizeof(socketInfo));
    char serverIpAddressBuffer[INET_ADDRSTRLEN];
    if ((getsockname(newConnectionSocket, (struct sockaddr*) &socketInfo, &byteCount) == STATUS_SUCCESS)
            && (inet_ntop(AF_INET, &socketInfo.sin_addr, serverIpAddressBuffer, INET_ADDRSTRLEN) != nullptr)) {

        serverIpAddressString = string(serverIpAddressBuffer);
    }

    char clientIpAddressBuffer[INET_ADDRSTRLEN];
    if (inet_ntop(AF_INET, &client.sin_addr, clientIpAddressBuffer, INET_ADDRSTRLEN) != nullptr)
        clientIpAddressString = string(clientIpAddressBuffer);
*/
