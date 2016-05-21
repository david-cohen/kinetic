/*
 * Copyright (c) 2016 Western Digital Technologies, Inc.
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
#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

/*
 * Include Files
 */
#include <string>
#include "Kinetic.pb.hpp"
#include "AccessControl.hpp"
#include "KineticMessage.hpp"

/*
 * Incomplete Class Definition (to avoid circular dependencies)
 */
class Connection;

/**
 * Describes a Kinetic transaction (in a passive data structure), which includes of the request
 * message, the optional response message, and other context information such as the connection and
 * access control.
 */
struct Transaction {
    explicit Transaction(Connection* transactionConnection)
        : connection(transactionConnection), request(new KineticMessage()), response(new KineticMessage()), accessControl(),
          errorCode(com::seagate::kinetic::proto::Command_Status_StatusCode_INVALID_STATUS_CODE), errorMessage() {}

    Connection* const                                       connection;     //!< Connection used for the transaction
    KineticMessagePtr                                       request;        //!< Request message
    KineticMessagePtr                                       response;       //!< Response message (may not be used)
    AccessControlPtr                                        accessControl;  //!< Access allowed for transaction
    com::seagate::kinetic::proto::Command_Status_StatusCode errorCode;      //!< Error code of encountered error (if any)
    std::string                                             errorMessage;   //!< Text description of error (if any)
};

#endif
