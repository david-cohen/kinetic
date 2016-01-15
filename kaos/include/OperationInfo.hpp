/*
 * Copyright (c) [2016] Western Digital Technologies, Inc. All rights reserved.
 */
#pragma once
#ifndef OPERATION_INFO_HPP
#define OPERATION_INFO_HPP

/*
 * Include Files
 */
#include "Connection.hpp"
#include "KineticMessage.hpp"
#include "Kinetic.pb.hpp"

/**
 * Operation Information (Plain old data)
 *
 */
struct OperationInfo {

    const com::seagate::kinetic::proto::Command_MessageType  m_requestType;             //!< Type of message
    const Operation                                          m_operation;               //!< Operation to be performed for this request
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
};

#endif
