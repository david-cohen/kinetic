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
#ifndef COMMUNICATIONS_MANAGER_HPP
#define COMMUNICATIONS_MANAGER_HPP

/*
 * Include Files
 */
#include <stdint.h>
#include <list>
#include <mutex>
#include "Common.hpp"
#include "ListenerInterface.hpp"
#include "HeartbeatProvider.hpp"

/*
 * Incomplete Class Definitions
 */
class Server;
class Connection;

/**
 * Manages the server's communications with clients.
 */
class CommunicationsManager {

public:

    /*
     * Constructor
     */
    explicit CommunicationsManager(Server* server);
    Server* server() {return m_server;}

    /*
     * Public Member Functions
     */
    void start();
    void stop();
    void addConnection(Connection* connection);
    void removeConnection(Connection* connection);
    uint32_t batchCount();

private:

    /*
     * Private Data Members
     */
    Server*                         m_server;               //!< Server that the manager belong to
    std::list<Connection*>          m_connectionList;       //!< List of active connections
    std::list<ListenerInterfacePtr> m_listenerList;         //!< List of active listeners
    HeartbeatProvider               m_heartbeatProvider;    //!< Provider of heartbeat messages
    std::mutex                      m_mutex;                //!< Mutex to make class thread safe

    DISALLOW_COPY_AND_ASSIGN(CommunicationsManager);
};

#endif
