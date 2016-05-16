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

/**
 * A message handler for Kinetic messages.  A message handler is called for each Kinetic request
 * received.
 */
class MessageHandler {
public:

    /*
     * Public Class Member Functions
     */
    static void processRequest(Transaction* transaction);
    static void processError(Transaction* transaction);
    static void processPutRequest(Transaction* transaction);
    static void processSetupRequest(Transaction* transaction);
    static void processSecurityRequest(Transaction* transaction);
    static void processGetRequest(Transaction* transaction);
    static void processGetNextRequest(Transaction* transaction);
    static void processGetPreviousRequest(Transaction* transaction);
    static void processGetVersionRequest(Transaction* transaction);
    static void processGetKeyRangeRequest(Transaction* transaction);
    static void processDeleteRequest(Transaction* transaction);
    static void processFlushRequest(Transaction* transaction);
    static void processNoopRequest(Transaction* transaction);
    static void processPinOpRequest(Transaction* transaction);
    static void processOptimizeMediaRequest(Transaction* transaction);
    static void processP2pPushRequest(Transaction* transaction);
    static void processGetLogRequest(Transaction* transaction);
    static void processStartBatchRequest(Transaction* transaction);
    static void processEndBatchRequest(Transaction* transaction);
    static void processAbortBatchRequest(Transaction* transaction);
    static void processInvalidRequest(Transaction* transaction);

private:

    /*
     * Private Inline Member Functions
     */
    static inline uint32_t messageTypeToIndex(::com::seagate::kinetic::proto::Command_MessageType messageType) {return static_cast<uint32_t>(messageType) >> 1;}

    DISALLOW_COPY_AND_ASSIGN(MessageHandler);
};

#endif
