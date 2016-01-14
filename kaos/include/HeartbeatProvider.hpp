/*
 * Copyright (c) [2014 - 2016] Western Digital Technologies, Inc. All rights reserved.
 */
#pragma once
#ifndef HEARTBEAT_PROVIDER_HPP
#define HEARTBEAT_PROVIDER_HPP

/*
 * Include Files
 */
#include <netinet/in.h>
#include <atomic>
#include <thread>
#include <string>
#include "Common.hpp"

/**
 * Heartbeat Provider
 *
 * Sends a Kinetic heartbeat message to a UDP multicast address at regular intervals (around five
 * seconds).
 */
class HeartbeatProvider {
public:

    /*
     * Constructor
     */
    HeartbeatProvider();

    /*
     * Public Member Function
     */
    bool start();
    void stop();
    void wait();

private:

    /*
     * Private Member Functions
     */
    void run();
    void openSocket();
    void sendHeartbeatMessage();

    /*
     * Private Data Member
     */
    std::atomic_bool    m_active;       //!< Indicates if provider is active
    std::thread*        m_thread;       //!< Thread that repeatedly sends heartbeat message
    int32_t             m_socketFd;     //!< Socket used to send heartbeat message
    struct sockaddr_in  m_address;      //!< Address information when sending message

    DISALLOW_COPY_AND_ASSIGN(HeartbeatProvider);
};

#endif
