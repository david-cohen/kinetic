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
#pragma once
#ifndef MESSAGE_HANDLER_HPP
#define MESSAGE_HANDLER_HPP

/*
 * Include Files
 */
#include <stdint.h>
#include <string>
#include "Common.hpp"
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
    inline uint32_t messageTypeToIndex(::com::seagate::kinetic::proto::Command_MessageType messageType) {return static_cast<uint32_t>(messageType) >> 1;}

    /*
     * Private Data Members
     */

    Connection* const       m_connection;           //!< Connection messages are tranferred through
    ObjectStoreInterface&   m_objectStore;          //!< Server's object store
    ServerSettings&         m_serverSettings;       //!< Server's user settings
    MessageStatistics&      m_messageStatistics;    //!< Statistics on processed messages

    DISALLOW_COPY_AND_ASSIGN(MessageHandler);
};

#endif
