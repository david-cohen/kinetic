/*
 * Copyright (c) 2014-2016 Western Digital Technologies, Inc. <copyrightagent@wdc.com>
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
#ifndef OPERATION_INFO_HPP
#define OPERATION_INFO_HPP

/*
 * Include Files
 */
#include "Kinetic.pb.hpp"
#include "Transaction.hpp"
#include "KineticMessage.hpp"

/*
 * Incomplete Class Definition
 */
class MessageHandler;

/*
 * Request Handler Function Type
 */
typedef void (MessageHandler::* RequestHandler)(Transaction* transaction);

/**
 * Contains operation information (one for each operation), which is used to process requests.
 */
class OperationInfo {
public:
    /**
     * Constructor
     *
     * @param requestType           Specified Kinetic request type
     * @param operation             Type of operation being performed
     * @param processRequest        Function to process request
     * @param operationInvolvesKey  True if the operation is key-based (such as a get)
     */
    OperationInfo(com::seagate::kinetic::proto::Command_MessageType requestType, Operation operation,
                  RequestHandler processRequest, bool operationInvolvesKey)
        : m_requestType(requestType), m_responseType(static_cast<com::seagate::kinetic::proto::Command_MessageType>(requestType - 1)),
          m_operation(operation), m_operationInvolvesKey(operationInvolvesKey), m_processRequest(processRequest),
          m_requiredAuthenticationType(requestType == com::seagate::kinetic::proto::Command_MessageType_PINOP
                                       ? com::seagate::kinetic::proto::Message_AuthType::Message_AuthType_PINAUTH :
                                       com::seagate::kinetic::proto::Message_AuthType::Message_AuthType_HMACAUTH) {
    }

    /*
     * Public Accessors
     */
    inline com::seagate::kinetic::proto::Command_MessageType requestType() const {return m_requestType;}
    inline com::seagate::kinetic::proto::Command_MessageType responseType() const {return m_responseType;}
    inline Operation operation() const {return m_operation;}
    inline bool operationInvolvesKey() const {return m_operationInvolvesKey;}
    inline RequestHandler processRequest() const {return m_processRequest;}
    inline com::seagate::kinetic::proto::Message_AuthType requiredAuthenticationType() const {return m_requiredAuthenticationType;}

private:
    /*
     * Private Data Members
     */
    const com::seagate::kinetic::proto::Command_MessageType m_requestType;                  //!< Type of request message
    const com::seagate::kinetic::proto::Command_MessageType m_responseType;                 //!< Type of corresponding response message
    const Operation                                         m_operation;                    //!< Operation to be performed for this request
    const bool                                              m_operationInvolvesKey;         //!< True if this is a key-based operation
    const RequestHandler                                    m_processRequest;               //!< Function to process message type
    const com::seagate::kinetic::proto::Message_AuthType    m_requiredAuthenticationType;   //!< Authentication required for this type of message
};

#endif
