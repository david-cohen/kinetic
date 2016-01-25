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

/*
 * Request Handler Function Type.
 */
typedef void (* RequestHandler)(Transaction& transaction);

/**
 * Contains operation information (one for each operation), which is used to process requests.
 */
struct OperationInfo {

    const com::seagate::kinetic::proto::Command_MessageType requestType;                        //!< Type of request message
    const com::seagate::kinetic::proto::Command_MessageType responseType;                       //!< Type of corresponding response message
    const Operation                                         operation;                          //!< Operation to be performed for this request
    const bool                                              operationInvolvesKey;               //!< True if this is a key-based operation
    const RequestHandler                                    processRequest;                     //!< Function to process message type
    const com::seagate::kinetic::proto::Message_AuthType    requiredAuthenticationType;         //!< Authentication required for this type of message

    /**
     * Constructor
     *
     * @param p_requestType             Specified Kinetic request type
     * @param p_operation               Type of operation being performed
     * @param p_processRequest          Function to process request
     * @param p_operationInvolvesKey    True if the operation is key-based (such as a get)
     */
    OperationInfo(com::seagate::kinetic::proto::Command_MessageType p_requestType, Operation p_operation, RequestHandler p_processRequest, bool p_operationInvolvesKey)
        : requestType(p_requestType), responseType(static_cast<com::seagate::kinetic::proto::Command_MessageType>(p_requestType - 1)),
          operation(p_operation), operationInvolvesKey(p_operationInvolvesKey), processRequest(p_processRequest),
          requiredAuthenticationType(p_requestType == com::seagate::kinetic::proto::Command_MessageType_PINOP
                                     ? com::seagate::kinetic::proto::Message_AuthType::Message_AuthType_PINAUTH :
                                     com::seagate::kinetic::proto::Message_AuthType::Message_AuthType_HMACAUTH) {
    }
};

#endif
