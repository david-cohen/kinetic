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
#include "AccessControl.hpp"
#include "KineticMessage.hpp"
#include "ConnectionHandler.hpp"

typedef struct {

    inline Operation operation() {return m_operation;}
    inline bool operationInvolvesKey() {return m_operationInvolvesKey;}
    inline com::seagate::kinetic::proto::Message_AuthType requiredAuthenticationType() {return m_requiredAuthenticationType;}

    const com::seagate::kinetic::proto::Command_MessageType  requestType;                                       //!< Type of message
    const com::seagate::kinetic::proto::Command_MessageType  responseType;                                      //!< Associated response type
    const Operation                                          m_operation;                                       //!< Operation to be performed for this request
    const com::seagate::kinetic::proto::Message_AuthType     m_requiredAuthenticationType;
    const bool                                               m_operationInvolvesKey;
    void (*perform)(KineticMessagePtr& requestMessage, KineticMessagePtr& responseMessage);                    //!< Function to process message type
} OperationInfo;

/**
    Message Handler
*/

class MessageHandler {
public:

    /*
        Constructor
    */

    explicit MessageHandler(ConnectionHandler* connectionHandler);

    /*
        Public Instance Member Functions
    */

    KineticMessagePtr processRequest(KineticMessagePtr& requestMessage);
    KineticMessagePtr processError(KineticMessagePtr& requestMessage, ConnectionError error, const std::string& errorMessage);

    /*
        Public Class Member Functions
    */

    static void processPutRequest(KineticMessagePtr& requestMessage, KineticMessagePtr& responseMessage);
    static void processSetupRequest(KineticMessagePtr& requestMessage, KineticMessagePtr& responseMessage);
    static void processSecurityRequest(KineticMessagePtr& requestMessage, KineticMessagePtr& responseMessage);
    static void processGetRequest(KineticMessagePtr& requestMessage, KineticMessagePtr& responseMessage);
    static void processGetNextRequest(KineticMessagePtr& requestMessage, KineticMessagePtr& responseMessage);
    static void processGetPreviousRequest(KineticMessagePtr& requestMessage, KineticMessagePtr& responseMessage);
    static void processGetVersionRequest(KineticMessagePtr& requestMessage, KineticMessagePtr& responseMessage);
    static void processGetKeyRangeRequest(KineticMessagePtr& requestMessage, KineticMessagePtr& responseMessage);
    static void processDeleteRequest(KineticMessagePtr& requestMessage, KineticMessagePtr& responseMessage);
    static void processFlushRequest(KineticMessagePtr& requestMessage, KineticMessagePtr& responseMessage);
    static void processNoopRequest(KineticMessagePtr& requestMessage, KineticMessagePtr& responseMessage);
    static void processPinOpRequest(KineticMessagePtr& requestMessage, KineticMessagePtr& responseMessage);
    static void processP2pPushRequest(KineticMessagePtr& requestMessage, KineticMessagePtr& responseMessage);
    static void processGetLogRequest(KineticMessagePtr& requestMessage, KineticMessagePtr& responseMessage);
    static void processInvalidRequest(KineticMessagePtr& requestMessage, KineticMessagePtr& responseMessage);

private:

    /*
        Private Instance Member Functions
    */

    OperationInfo& initialMessageProcessing(KineticMessagePtr& requestMessage, KineticMessagePtr& responseMessage, AccessControlPtr& accessControl);

    /*
        Private Inline Member Functions
    */

    inline uint32_t messageTypeToIndex(::com::seagate::kinetic::proto::Command_MessageType messageType) {return static_cast<uint32_t>(messageType) >> 1;}

    /*
        Private Data Member
    */

    ConnectionHandler* const m_connectionHandler;    //!< Assoicated connection

    DISALLOW_COPY_AND_ASSIGN(MessageHandler);
};

#endif
