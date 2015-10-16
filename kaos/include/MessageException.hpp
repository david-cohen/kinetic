/*
    Copyright (c) [2014 - 2015] Western Digital Technologies, Inc. All rights reserved.
*/

#pragma once
#ifndef MESSAGE_EXCEPTION_HPP
#define MESSAGE_EXCEPTION_HPP

/*
    Include Files
*/

#include <string>
#include <sstream>
#include <exception>
#include "KineticMessage.hpp"

/**
    Message Exception

    An exception thrown due to an error encountered while processing a Kinetic Message.  The error
    information is recorded as a status code and status message so it can be used to populate the
    status fields of a Kinetic response message.
*/

class MessageException: public std::exception {

public:

    /*
        Constructor/Destructor
    */

    MessageException(com::seagate::kinetic::proto::Command_Status_StatusCode statusCode, const std::string& message)
        : m_statusCode(statusCode), m_message(message) {}

    explicit MessageException(com::seagate::kinetic::proto::Command_Status_StatusCode statusCode)
        : m_statusCode(statusCode), m_message() {}

    MessageException(com::seagate::kinetic::proto::Command_Status_StatusCode statusCode, std::ostream& messageStream)
        : m_statusCode(statusCode), m_message(buildMessage(messageStream)) {}

    ~MessageException() throw() {}

    /*
        Public Member Function
    */

    inline com::seagate::kinetic::proto::Command_Status_StatusCode statusCode() {return m_statusCode;}
    inline const std::string& statusMessage() {return m_message;}
    inline virtual const char* what() const throw() {return m_message.c_str();}

private:

    std::string buildMessage(std::ostream& messageStream) {
        std::stringstream stream;
        stream << messageStream.rdbuf();
        return stream.str();
    }


    /*
        Private Data Members
    */

    const com::seagate::kinetic::proto::Command_Status_StatusCode m_statusCode;     //!< Enum that indicates category of error
    const std::string                                             m_message;        //!< Text description of specific error
};

#endif
