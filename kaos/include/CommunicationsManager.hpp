/*
 * Copyright (c) [2014 - 2016] Western Digital Technologies, Inc. All rights reserved.
 */
#pragma once
#ifndef COMMUNICATIONS_MANAGER_HPP
#define COMMUNICATIONS_MANAGER_HPP

/*
 * Include Files
 */
#include <stdint.h>
#include <list>
#include "Common.hpp"
#include "Connection.hpp"
#include "ListenerInterface.hpp"
#include "HeartbeatProvider.hpp"

/**
 * Manages the daemon's communications with clients.
 */
class CommunicationsManager {

public:

    /*
     * Constructor
     */
    CommunicationsManager();

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
    std::mutex                      m_mutex;                //!< Mutex to make class thread safe
    std::list<Connection*>          m_connectionList;       //!< List of active connections
    std::list<ListenerInterfacePtr> m_listenerList;         //!< List of active listeners
    HeartbeatProvider               m_heartbeatProvider;    //!< Provider of heartbeat messages

    DISALLOW_COPY_AND_ASSIGN(CommunicationsManager);
};

extern CommunicationsManager communicationsManager;

#endif
