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
#include "Connection.hpp"

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

    virtual void addConnection(Connection* connection) {
        std::unique_lock<std::mutex> scopedLock(m_mutex);
        m_connectionList.push_back(connection);
    }

    virtual void removeConnection(Connection* connection) {
        std::unique_lock<std::mutex> scopedLock(m_mutex);
        m_connectionList.remove(connection);
        delete connection;
    }

    uint32_t connectionCount() {
        std::unique_lock<std::mutex> scopedLock(m_mutex);
        return m_connectionList.size();
    }

    uint32_t batchCount() {
        uint32_t batchCount = 0;
        std::unique_lock<std::mutex> scopedLock(m_mutex);
        for (auto connection : m_connectionList) {
            batchCount += connection->batchCount();
        }
        return batchCount;
    }

protected:

    /*
        Protected Data Members
    */

    const Security              m_security;         //!< Security method to be used
    std::mutex                  m_mutex;            //!< Mutex to make class thread safe
    std::list<Connection*>      m_connectionList;   //!< List of active connections
};

#endif
