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
 * The message handler for Kinetic messages, which is called for each Kinetic request received.
 * There is one message handler for each connection.
 */
class MessageHandler {
public:
    /*
     * Constructor
     */
    explicit MessageHandler(Connection* const connection);

    /*
     * Public Member Functions
     */
    void processRequest(Transaction* const transaction);
    void processPutRequest(Transaction* const transaction);
    void processSetupRequest(Transaction* const transaction);
    void processSecurityRequest(Transaction* const transaction);
    void processGetRequest(Transaction* const transaction);
    void processGetNextRequest(Transaction* const transaction);
    void processGetPreviousRequest(Transaction* const transaction);
    void processGetVersionRequest(Transaction* const transaction);
    void processGetKeyRangeRequest(Transaction* const transaction);
    void processDeleteRequest(Transaction* const transaction);
    void processFlushRequest(Transaction* const transaction);
    void processNoopRequest(Transaction* const transaction);
    void processPinOpRequest(Transaction* const transaction);
    void processOptimizeMediaRequest(Transaction* const transaction);
    void processP2pPushRequest(Transaction* const transaction);
    void processGetLogRequest(Transaction* const transaction);
    void processStartBatchRequest(Transaction* const transaction);
    void processEndBatchRequest(Transaction* const transaction);
    void processAbortBatchRequest(Transaction* const transaction);
    void processInvalidRequest(Transaction* const transaction);
    void buildResponseWithError(Transaction* const transaction, com::seagate::kinetic::proto::Command_Status_StatusCode errorCode,
                                const std::string& errorMessage);
    /*
     * Public Class Member Functions
     */
    static void buildUnsolicitedStatusMessage(Connection* const connection, KineticMessage& response);

private:
    /*
     * Private Inline Member Functions
     */
    inline uint32_t messageTypeToIndex(::com::seagate::kinetic::proto::Command_MessageType messageType) {
        return static_cast<uint32_t>(messageType) >> 1;
    }

    inline com::seagate::kinetic::proto::Command_MessageType requestToResponseType(com::seagate::kinetic::proto::Command_MessageType messageType) {
        return static_cast<::com::seagate::kinetic::proto::Command_MessageType>(static_cast<uint32_t>(messageType) - 1);
    }

    /*
     * Private Data Members
     */
    Connection* const           m_connection;           //!< Connection messages are transferred through
    ObjectStoreInterface* const m_objectStore;          //!< Server's object store
    ServerSettings&             m_serverSettings;       //!< Server's user settings
    MessageStatistics&          m_messageStatistics;    //!< Statistics on processed messages
};

#endif
