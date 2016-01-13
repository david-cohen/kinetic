/*
 * Copyright (c) [2014 - 2016] Western Digital Technologies, Inc. All rights reserved.
 */

/*
 * Include Files
 */
#include <mutex>
#include "SslStream.hpp"
#include "SystemConfig.hpp"
#include "ClearTextStream.hpp"
#include "ConnectionListener.hpp"
#include "CommunicationsManager.hpp"

/**
 * Communications Manager Constructor
*/
CommunicationsManager::CommunicationsManager() {

    ListenerInterfacePtr sslListener(new ConnectionListener<SslStream>(systemConfig.sslPort()));
    ListenerInterfacePtr clearTextListener(new ConnectionListener<ClearTextStream>(systemConfig.tcpPort()));
    m_listenerList.push_back(sslListener);
    m_listenerList.push_back(clearTextListener);
}

/**
 * Start
 */
void CommunicationsManager::start() {

    m_heartbeatProvider.start();

    for (auto listener : m_listenerList)
        listener->start();
}

/**
 * Stop
 */
void CommunicationsManager::stop() {

    m_heartbeatProvider.stop();

    for (auto listener : m_listenerList)
        listener->stop();
}

/**
 * Add Connection
 *
 * @param   connection  the connection being added
 *
 * @throw   runtime_error if the maximum number of connections are already open
 */
void CommunicationsManager::addConnection(Connection* connection) {

    std::unique_lock<std::mutex> scopedLock(m_mutex);
    if (m_connectionList.size() >= systemConfig.maxConnections())
        throw std::runtime_error("No connections available");

    m_connectionList.push_back(connection);
}

/**
 * Remove Connection
 *
 * @param   connection  the connection being removed
 */
void CommunicationsManager::removeConnection(Connection* connection) {

    std::unique_lock<std::mutex> scopedLock(m_mutex);
    m_connectionList.remove(connection);
    delete connection;
}

/**
 * Batch Count
 *
 * @return  the number of active batch commands
 */
uint32_t CommunicationsManager::batchCount() {

    std::unique_lock<std::mutex> scopedLock(m_mutex);
    uint32_t batchCount = 0;
    for (auto connection : m_connectionList)
        batchCount += connection->batchCount();

    return batchCount;
}

