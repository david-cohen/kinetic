/*
    Copyright (c) [2014 - 2015] Western Digital Technologies, Inc. All rights reserved.
*/

#pragma once
#ifndef MESSAGE_HANDLER_HPP
#define MESSAGE_HANDLER_HPP

/*
    Include Files
*/

#include <stdint.h>
#include <list>
#include <string>
#include "Common.hpp"
#include "Connection.hpp"
#include "AccessControl.hpp"
#include "KineticMessage.hpp"

typedef struct {

    const com::seagate::kinetic::proto::Command_MessageType  m_requestType;                     //!< Type of message
    const Operation                                          m_operation;                       //!< Operation to be performed for this request
    const bool                                               m_operationInvolvesKey;

    void (*perform)(Transaction& transaction);     //!< Function to process message type

    inline Operation operation() {return m_operation;}
    inline com::seagate::kinetic::proto::Command_MessageType responseType() {
        return static_cast<com::seagate::kinetic::proto::Command_MessageType>(m_requestType - 1);
    }
    inline bool operationInvolvesKey() {return m_operationInvolvesKey;}
    inline com::seagate::kinetic::proto::Message_AuthType requiredAuthenticationType() {
            return m_requestType == com::seagate::kinetic::proto::Command_MessageType_PINOP
                   ? com::seagate::kinetic::proto::Message_AuthType::Message_AuthType_PINAUTH
                   : com::seagate::kinetic::proto::Message_AuthType::Message_AuthType_HMACAUTH;
    }
} OperationInfo;

/**
    Message Handler
*/

class MessageHandler {
public:

    /*
        Public Class Member Functions
    */

    static void processRequest(Transaction& transaction);
    static void processError(Transaction& transaction);
    static void processPutRequest(Transaction& transaction);
    static void processSetupRequest(Transaction& transaction);
    static void processSecurityRequest(Transaction& transaction);
    static void processGetRequest(Transaction& transaction);
    static void processGetNextRequest(Transaction& transaction);
    static void processGetPreviousRequest(Transaction& transaction);
    static void processGetVersionRequest(Transaction& transaction);
    static void processGetKeyRangeRequest(Transaction& transaction);
    static void processDeleteRequest(Transaction& transaction);
    static void processFlushRequest(Transaction& transaction);
    static void processNoopRequest(Transaction& transaction);
    static void processPinOpRequest(Transaction& transaction);
    static void processOptimizeMediaRequest(Transaction& transaction);
    static void processP2pPushRequest(Transaction& transaction);
    static void processGetLogRequest(Transaction& transaction);
    static void processStartBatchRequest(Transaction& transaction);
    static void processEndBatchRequest(Transaction& transaction);
    static void processAbortBatchRequest(Transaction& transaction);
    static void processInvalidRequest(Transaction& transaction);
    static void handleInvalidBatchRequest(com::seagate::kinetic::proto::Command_Status_StatusCode statusCode, const std::string& message);

private:

    /*
        Private Inline Member Functions
    */

    static inline uint32_t messageTypeToIndex(::com::seagate::kinetic::proto::Command_MessageType messageType) {return static_cast<uint32_t>(messageType) >> 1;}

    DISALLOW_COPY_AND_ASSIGN(MessageHandler);
};

#endif
