/*
 * Copyright (c) [2016] Western Digital Technologies, Inc. All rights reserved.
 */
#pragma once
#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

/*
 * Include Files
 */
#include <string>
#include "AccessControl.hpp"
#include "KineticMessage.hpp"

/*
 * Incomplete Class Definition (to avoid circular dependencies)
 */
class Connection;

/*
 * Connection Error
 */
enum class ConnectionError {
    NONE          = 0,
    VALUE_TOO_BIG = 1,
    IO_ERROR      = 2,
};

/**
 * Transaction (Plain old data)
 *
 * Describes a Kinetic transaction, which includes of the request message, the optional response
 * message, and other context information such as the connection and access control.
 */
struct Transaction {
    explicit Transaction(Connection* transactionConnection)
        : connection(transactionConnection), request(new KineticMessage()), response(new KineticMessage()), error(ConnectionError::NONE) {}

    Connection* const   connection;     //!< Connection used for the transaction
    KineticMessagePtr   request;        //!< Request message
    KineticMessagePtr   response;       //!< Response message (may not be used)
    ConnectionError     error;          //!< Connection related error
    std::string         errorMessage;   //!< Text description of error
    AccessControlPtr    accessControl;  //!< Access allowed for transaction
};

#endif
