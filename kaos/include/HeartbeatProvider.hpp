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
 * Responsible for sending Kinetic heartbeat messages to the Kinetic UDP multicast address.
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
