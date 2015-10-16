/*
    Copyright (c) [2014 - 2015] Western Digital Technologies, Inc. All rights reserved.
*/

#pragma once
#ifndef CONNECTION_FACTORY_HPP
#define CONNECTION_FACTORY_HPP

/*
    Include Files
*/

#include <mutex>
#include <string>
#include <stdexcept>
#include "SslStream.hpp"
#include "SslControl.hpp"
#include "TcpTransport.hpp"
#include "SystemConfig.hpp"
#include "ClearTextStream.hpp"
#include "StreamInterface.hpp"
#include "TransportManager.hpp"
#include "ConnectionHandler.hpp"
#include "TransportInterface.hpp"

/**
    Connection Factory

    Used to create a connection.  Currently, there are only two types of connections that can be
    created (secure and unsecure).  The secure connection uses an encrypted SSL stream where the
    unsecure connection uses a clear text stream.  Both connection types utilized the TCP protocol.
    There is a maximum number of connections that the system supports, which is enforced at the
    point of connection creation.  Checking the number of connections and adding a connection (if
    possible) both need to be done at the same time with the same mutex protection to prevent race
    conditions.
*/

class ConnectionFactory {

public:

    /**
        Create Connection

        @param  transport        The transport that will be used by the connection
        @param  socketFd         The socket associated with connection
        @param  serverPort       The port number used by the server for the connection
        @param  serverIpAddress  The IP address used by the server for the connection
        @param  clientPort       The port number used by the client for the connection
        @param  clientIpAddress  The IP address used by the client for the connection

        @throw  runtime_error if there are no available connections in the system
    */

    void createConnection(TransportInterface* transport, int32_t socketFd, uint32_t serverPort,
                          std::string serverIpAddress, uint32_t clientPort, std::string clientIpAddress) {

        std::unique_lock<std::mutex> m_scopedLock(m_mutex);

        if (!transportManager.connectionCount() >= systemConfig.maxConnections())
            throw std::runtime_error("No connections available");

        StreamInterface* stream = (transport->security() == Security::SSL)
                                  ? static_cast<StreamInterface*>(new SslStream(socketFd, SslControl::instance().createConnection(socketFd)))
                                  : static_cast<StreamInterface*>(new ClearTextStream(socketFd));

        transport->addConnection(new ConnectionHandler(transport, stream, serverPort, serverIpAddress, clientPort, clientIpAddress));
    }

private:

    /*
        Private Data Members
    */

    std::mutex  m_mutex;    //!< Mutex used to serialize connection creation
};

extern ConnectionFactory connectionFactory;

#endif
