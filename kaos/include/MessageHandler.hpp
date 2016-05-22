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
#ifndef MESSAGE_HANDLER_HPP
#define MESSAGE_HANDLER_HPP

/*
 * Include Files
 */
#include <stdint.h>
#include <string>
#include "Connection.hpp"
#include "Kinetic.pb.hpp"
#include "Transaction.hpp"
#include "ServerSettings.hpp"
#include "MessageStatistics.hpp"
#include "ObjectStoreInterface.hpp"

/**
 * A message handler for Kinetic messages.  A message handler is called for each Kinetic request
 * received.
 */
class MessageHandler {
public:

    /*
     * Constructor
     */
    explicit MessageHandler(Connection* connection);

    /*
     * Public Class Member Functions
     */
    void processRequest(Transaction* transaction);
    void processError(Transaction* transaction);
    void processPutRequest(Transaction* transaction);
    void processSetupRequest(Transaction* transaction);
    void processSecurityRequest(Transaction* transaction);
    void processGetRequest(Transaction* transaction);
    void processGetNextRequest(Transaction* transaction);
    void processGetPreviousRequest(Transaction* transaction);
    void processGetVersionRequest(Transaction* transaction);
    void processGetKeyRangeRequest(Transaction* transaction);
    void processDeleteRequest(Transaction* transaction);
    void processFlushRequest(Transaction* transaction);
    void processNoopRequest(Transaction* transaction);
    void processPinOpRequest(Transaction* transaction);
    void processOptimizeMediaRequest(Transaction* transaction);
    void processP2pPushRequest(Transaction* transaction);
    void processGetLogRequest(Transaction* transaction);
    void processStartBatchRequest(Transaction* transaction);
    void processEndBatchRequest(Transaction* transaction);
    void processAbortBatchRequest(Transaction* transaction);
    void processInvalidRequest(Transaction* transaction);

private:

    /*
     * Private Inline Member Functions
     */
    inline uint32_t messageTypeToIndex(::com::seagate::kinetic::proto::Command_MessageType messageType) {
        return static_cast<uint32_t>(messageType) >> 1;
    }

    /*
     * Private Data Members
     */

    Connection* const       m_connection;           //!< Connection messages are tranferred through
    ObjectStoreInterface&   m_objectStore;          //!< Server's object store
    ServerSettings&         m_serverSettings;       //!< Server's user settings
    MessageStatistics&      m_messageStatistics;    //!< Statistics on processed messages
};

#endif
