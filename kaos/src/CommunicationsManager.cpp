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
 * Initializes the Communications Manager object by initializing its list of connection listeners.
 * Currently, there are only two - one for encrypted communication on the SSL port and one for clear
 * text communications on the TCP port.
*/
CommunicationsManager::CommunicationsManager() {

    ListenerInterfacePtr sslListener(new ConnectionListener<SslStream>(systemConfig.sslPort()));
    ListenerInterfacePtr clearTextListener(new ConnectionListener<ClearTextStream>(systemConfig.tcpPort()));
    m_listenerList.push_back(sslListener);
    m_listenerList.push_back(clearTextListener);
}

/**
 * Starts the heartbeat message provider, which allows discovery of this Kinetic device.  Also,
 * starts the listener threads, which enables client communications.
 */
void CommunicationsManager::start() {

    m_heartbeatProvider.start();

    for (auto listener : m_listenerList)
        listener->start();
}

/**
 * Stops the heartbeat message provider, which prevents discovery of this Kinetic device.  Also,
 * stops the listener threads, which disables client communications.
 */
void CommunicationsManager::stop() {

    m_heartbeatProvider.stop();

    for (auto listener : m_listenerList)
        listener->stop();
}

/**
 * Adds a connection to the manager's database and permits it to be used if the maximum number of
 * connections hasn't been reached.  Otherwise, it rejects the connection by throwing an exception,
 * which causes the connection to be closed.
 *
 * @param   connection  The connection being added
 *
 * @throws  A runtime error if the maximum number of connections are already open
 */
void CommunicationsManager::addConnection(Connection* connection) {

    std::unique_lock<std::mutex> scopedLock(m_mutex);
    if (m_connectionList.size() >= systemConfig.maxConnections())
        throw std::runtime_error("No connections available");

    m_connectionList.push_back(connection);
}

/**
 * Removes the connection from the manager's database.
 *
 * @param   connection  The connection being removed
 */
void CommunicationsManager::removeConnection(Connection* connection) {

    std::unique_lock<std::mutex> scopedLock(m_mutex);
    m_connectionList.remove(connection);
    delete connection;
}

/**
 * Determines the number of outstanding batch commands across all connections.
 *
 * @return  The number of active batch commands
 */
uint32_t CommunicationsManager::batchCount() {

    std::unique_lock<std::mutex> scopedLock(m_mutex);
    uint32_t batchCount = 0;
    for (auto connection : m_connectionList)
        batchCount += connection->batchCount();

    return batchCount;
}

