/*
 * Copyright (c) [2014 - 2016] Western Digital Technologies, Inc. All rights reserved.
 */
#pragma once
#ifndef MESSAGE_EXCEPTION_HPP
#define MESSAGE_EXCEPTION_HPP

/*
 * Include Files
 */
#include <string>
#include <exception>
#include "KineticMessage.hpp"

/**
 * An exception thrown due to an error encountered while processing a Kinetic Message.  The error
 * information is recorded as a status code and status message so it can be used to populate the
 * status fields of a Kinetic response message.
 */
class MessageException: public std::exception {

public:

    /*
     * Constructors/Destructor
     */
    MessageException(com::seagate::kinetic::proto::Command_Status_StatusCode statusCode, const std::string& message)
        : m_statusCode(statusCode), m_message(message) {}

    explicit MessageException(com::seagate::kinetic::proto::Command_Status_StatusCode statusCode)
        : m_statusCode(statusCode), m_message() {}

    ~MessageException() throw() {}

    /*
     * Public Accessors
     */
    inline com::seagate::kinetic::proto::Command_Status_StatusCode statusCode() {return m_statusCode;}
    inline const std::string& statusMessage() {return m_message;}
    inline virtual const char* what() const throw() {return m_message.c_str();}

private:

    /*
     * Private Data Members
     */
    const com::seagate::kinetic::proto::Command_Status_StatusCode m_statusCode;     //!< Numeric indicator or error
    const std::string                                             m_message;        //!< Text description of error
};

#endif
