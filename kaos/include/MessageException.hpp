/*
 * Copyright (c) 2014-2016 Western Digital Technologies, Inc. <copyrightagent@wdc.com>
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
