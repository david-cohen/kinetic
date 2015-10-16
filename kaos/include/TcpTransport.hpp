/*
    Copyright (c) [2014 - 2015] Western Digital Technologies, Inc. All rights reserved.
*/

#pragma once
#ifndef TCP_TRANSPORT_HPP
#define TCP_TRANSPORT_HPP

/*
    Include Files
*/

#include <thread>
#include "openssl/ssl.h"
#include "Common.hpp"
#include "TransportInterface.hpp"

/**
    TCP Transport

    The TCP transport class has a thread that listens for new TCP connections.  When an incoming
    connection is received, it creates a new connection thread to manage the connection.
*/

class TcpTransport : public TransportInterface {

public:

    /*
        Constructor
    */

    TcpTransport(uint32_t port, Security security);

    /*
        Public Member Function
    */

    bool start();
    void stop();
    void wait();
    void close(int socketFd);

private:

    /*
        Private Member Functions
    */

    virtual void run();

    /*
        Private Data Member
    */

    uint32_t        m_port;     //!< Listening port
    std::thread*    m_thread;   //!< Listening thread

    DISALLOW_COPY_AND_ASSIGN(TcpTransport);
};

#endif
