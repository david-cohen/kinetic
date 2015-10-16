/*
    Copyright (c) [2014 - 2015] Western Digital Technologies, Inc. All rights reserved.
*/

#pragma once
#ifndef TRANSPORT_INTERFACE_HPP
#define TRANSPORT_INTERFACE_HPP

/*
    Include Files
*/

#include <list>
#include <mutex>
#include "ConnectionHandler.hpp"

/*
    Transport Security
*/

enum class Security {
    NONE = 0,
    SSL  = 1,
};

/**
    Transport Interface

    The abstract base class that defines the required interface for concrete transport classes (such
    as TCP).
*/

class TransportInterface {

public:

    /*
        Public Member Function
    */

    explicit TransportInterface(Security security) : m_security(security) {}
    virtual ~TransportInterface() {}
    virtual bool start() = 0;
    virtual void stop() = 0;
    virtual void wait() = 0;
    Security security() {return m_security;}

    virtual void addConnection(ConnectionHandler* connectionHandler) {
        std::unique_lock<std::mutex> scopedLock(m_mutex);
        m_connectionHandlerList.push_back(connectionHandler);
    }

    virtual void removeConnection(ConnectionHandler* connectionHandler) {
        std::unique_lock<std::mutex> scopedLock(m_mutex);
        m_connectionHandlerList.remove(connectionHandler);
        delete connectionHandler;
    }

    uint32_t connectionCount() {
        std::unique_lock<std::mutex> scopedLock(m_mutex);
        return m_connectionHandlerList.size();
    }


protected:

    /*
        Protected Data Members
    */

    const Security                  m_security;                 //!< Security method to be used
    std::mutex                      m_mutex;                    //!< Mutex to make class thread safe
    std::list<ConnectionHandler*>   m_connectionHandlerList;    //!< List of active connections
};

#endif
