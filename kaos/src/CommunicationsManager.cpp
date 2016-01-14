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
 *
 * Initializes the list of connection listeners.  Currently, there are only two - one for encrypted
 * communication (on the SSL port) and one for clear text communications (on the TCP port).
*/
CommunicationsManager::CommunicationsManager() {

    ListenerInterfacePtr sslListener(new ConnectionListener<SslStream>(systemConfig.sslPort()));
    ListenerInterfacePtr clearTextListener(new ConnectionListener<ClearTextStream>(systemConfig.tcpPort()));
    m_listenerList.push_back(sslListener);
    m_listenerList.push_back(clearTextListener);
}

/**
 * Start
 *
 * Start the heartbeat message provider, which allows discovery of this Kinetic device.  Also,
 * start the listener threads, which enables client communications.
 */
void CommunicationsManager::start() {

    m_heartbeatProvider.start();

    for (auto listener : m_listenerList)
        listener->start();
}

/**
 * Stop
 *
 * Stop the heartbeat message provider, which prevents discovery of this Kinetic device.  Also, stop
 * the listener threads, which disables client communications.
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
 *
 * If the maximum number of connections hasn't been reached, add the connection
 * to the manager's database and permit it to be used.  Otherwise, reject the
 * connection (by throwing an exception), causing it to be closed.
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
 *
 * Remove the connection from the manager's database.
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
 *
 * Determine the number of outstanding batch commands across all connections.
 */
uint32_t CommunicationsManager::batchCount() {

    std::unique_lock<std::mutex> scopedLock(m_mutex);
    uint32_t batchCount = 0;
    for (auto connection : m_connectionList)
        batchCount += connection->batchCount();

    return batchCount;
}

