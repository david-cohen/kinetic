/*
 * Copyright (c) 2014-2016 Western Digital Technologies, Inc. <copyrightagent@wdc.com>
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
#include "Common.hpp"
#include "ObjectStore.hpp"
#include "ServerSettings.hpp"
#include "HeartbeatProvider.hpp"
#include "MessageStatistics.hpp"
#include "ListenerInterface.hpp"

class Connection;

class Server {

public:

    Server(std::string pidFileName, bool foreground);
    ServerSettings& settings() {return m_settings;}
    ObjectStore& objectStore() {return m_objectStore;}
    MessageStatistics& messageStatistics() {return m_messageStatistics;}
    int32_t run();
    void addConnection(Connection* connection);
    void removeConnection(Connection* connection);
    uint32_t batchCount();

private:

    std::string                     m_pidFileName;
    bool                            m_foreground;
    ServerSettings                  m_settings;
    MessageStatistics               m_messageStatistics;
    ObjectStore                     m_objectStore;
    std::list<Connection*>          m_connectionList;       //!< List of active connections
    std::list<ListenerInterfacePtr> m_listenerList;         //!< List of active listeners
    HeartbeatProvider               m_heartbeatProvider;    //!< Provider of heartbeat messages
    std::mutex                      m_mutex;                //!< Mutex to make class thread safe

    DISALLOW_COPY_AND_ASSIGN(Server);
};

#endif
