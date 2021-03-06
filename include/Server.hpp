/*
 * Copyright (c) 2014-2016 Western Digital Corporation or its affiliates <copyrightagent@wdc.com>
 * @author Gary Ballance <gary.ballance@wdc.com>
 *
 * SPDX-License-Identifier: GPL-2.0+
 * This file is part of Kinetic Advanced Object Store (KAOS).
 *
 * This program is free software: you may copy, redistribute and/or modify it under the terms of the
 * GNU General Public License as published by the Free Software Foundation, either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
 * even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program; if
 * not, write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA. <http://www.gnu.org/licenses/>
 */
#pragma once
#ifndef SERVER_HPP
#define SERVER_HPP

/*
 * Include Files
 */
#include <stdint.h>
#include <list>
#include <mutex>
#include <string>
#include "ServerSettings.hpp"
#include "HeartbeatProvider.hpp"
#include "MessageStatistics.hpp"
#include "ListenerInterface.hpp"
#include "RocksDbObjectStore.hpp"

/*
 * Incomplete Class Definition
 */
class Connection;

/**
 * Kinetic Object Store Server.
 */
class Server {
public:
    /*
     * Constructor
     */
    Server();

    /*
     * Public Accessors
     */
    ServerSettings& settings() {return m_settings;}
    ObjectStoreInterface* objectStore() const {return m_objectStore;}
    MessageStatistics& messageStatistics() {return m_messageStatistics;}

    /*
     * Public Member Functions
     */
    int32_t run(bool runInForeground);
    uint32_t activeBatchCommands();
    void addConnection(Connection* connection);
    void removeConnection(Connection* connection);

private:
    /*
     * Private Data Members
     */
    ServerSettings                  m_settings;             //!< User configurable server settings
    ObjectStoreInterface* const     m_objectStore;          //!< Server's object store database
    MessageStatistics               m_messageStatistics;    //!< Statistics on messages processed
    std::list<Connection*>          m_connectionList;       //!< List of active connections
    std::list<ListenerInterfacePtr> m_listenerList;         //!< List of active listeners
    HeartbeatProvider               m_heartbeatProvider;    //!< Provider of heartbeat messages
    std::mutex                      m_mutex;                //!< Mutex to make class thread safe
};

#endif
