/*
    Copyright (c) [2014 - 2015] Western Digital Technologies, Inc. All rights reserved.
*/

/*
    Include Files
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
#include "Logger.hpp"
#include "TcpTransport.hpp"
#include "SystemConfig.hpp"
#include "ConnectionFactory.hpp"

/**
    TcpTransport Constructor

    @param  port        The port to listen on for new connections
    @param  security    Security method to be used
*/

TcpTransport::TcpTransport(uint32_t port, Security security)
    : TransportInterface(security), m_port(port), m_thread(nullptr) {
}

/**
    Start

    @return true if the thread was successfully created
*/

bool
TcpTransport::start() {

    try {
        m_thread = new std::thread(&TcpTransport::run, this);
        return true;
    }
    catch (std::exception& e) {
        LOG(ERROR) << "Failed to create TCP Transport thread: description=" << e.what();
        m_thread = nullptr;
        return false;
    }
}

/**
    Run

    This function is called by the thread that will manage the TCP transport.  It listens for
    client connections and creates a connection handler for each new connection.
*/

void
TcpTransport::run() {

    try {
        const int OPTION_SET(1);

        /*
            Create a connection-oriented communication path and allow the same source address and
            port to be reused.
        */

        int32_t listeningSocketfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

        if (listeningSocketfd == STATUS_FAILURE) {
            LOG(ERROR) << "Failed to create socket: error_code=" << errno << ", description=" << strerror(errno);
            return;
        }

        if (setsockopt(listeningSocketfd, SOL_SOCKET, SO_REUSEADDR, &OPTION_SET, sizeof(OPTION_SET)) == STATUS_FAILURE) {
            LOG(ERROR) << "Failed to set socket options SO_REUSEADDR: error_code=" << errno << ", description=" << strerror(errno);
            return;
        }

        /*
            Now bind the server address and port to the socket.
        */

        struct sockaddr_in server;
        memset(&server, 0, sizeof(server));
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = INADDR_ANY;
        server.sin_port = htons(m_port);

        if (bind(listeningSocketfd, (struct sockaddr*) &server, sizeof(struct sockaddr)) == STATUS_FAILURE) {
            LOG(ERROR) << "Failed to bind socket: error_code=" << errno << ", description=" << strerror(errno);
            return;
        }

        /*
            Begin listening for client connection attempts.
        */

        LOG(INFO) << "TCP listener started: port=" << m_port;
        listen(listeningSocketfd, systemConfig.maxPendingAdminConnections());

        for (;;) {

            struct sockaddr_in client;
            socklen_t sin_size = sizeof(struct sockaddr_in);

            /*
                Wait for an incoming connection.  When one is received, create a connection handler
                to process all requests through that connection.
            */

            int32_t socketFd = accept(listeningSocketfd, (struct sockaddr*) &client, &sin_size);
            if (socketFd == STATUS_FAILURE) {
                LOG(ERROR) << "Failed to accept connection: error_code=" << errno << ", description=" << strerror(errno);
            }
            else {
                std::string serverIpAddressString("unknown");
                std::string clientIpAddressString("unknown");

                struct sockaddr_in socketInfo;
                socklen_t byteCount(sizeof(socketInfo));
                char serverIpAddressBuffer[INET_ADDRSTRLEN];
                if ((getsockname(socketFd, (struct sockaddr*) &socketInfo, &byteCount) == STATUS_SUCCESS)
                        && (inet_ntop(AF_INET, &socketInfo.sin_addr, serverIpAddressBuffer, INET_ADDRSTRLEN) != nullptr)) {

                    serverIpAddressString = std::string(serverIpAddressBuffer);
                }

                char clientIpAddressBuffer[INET_ADDRSTRLEN];
                if (inet_ntop(AF_INET, &client.sin_addr, clientIpAddressBuffer, INET_ADDRSTRLEN) != nullptr)
                    clientIpAddressString = std::string(clientIpAddressBuffer);

                connectionFactory.createConnection(this, socketFd, ntohs(server.sin_port), serverIpAddressString, ntohs(client.sin_port), clientIpAddressString);
            }
        }
    }
    catch (std::exception& ex) {
        LOG(ERROR) << "TCP Transport exception: " << ex.what();
    }
    catch (...) {
        LOG(ERROR) << "TCP Transport unknown exception";
    }
}

/**
    Stop
*/

void
TcpTransport::stop() {

    // to be implemented
}

/**
    Wait

    Causes the caller to be blocked until the listener thread ends.
*/

void
TcpTransport::wait() {

    if (m_thread != nullptr)
        m_thread->join();
}

