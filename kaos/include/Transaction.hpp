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
#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

/*
 * Include Files
 */
#include <string>
#include "AccessControl.hpp"
#include "KineticMessage.hpp"

/**
 * Describes a single Kinetic request and (optional) response transaction, which includes the
 * request message, optional response message, and needed context information such as the access
 * control.
 */
class Transaction {
public:
    /*
     * Constructor
     */
    Transaction()
        : m_request(), m_response(), m_hasResponse(true), m_accessControl() {}

    /*
     * Public Accessors
     */
    inline KineticMessage& request() {return m_request;}
    inline KineticMessage& response() {return m_response;}
    inline bool hasResponse() {return m_hasResponse;}
    inline void setNoResponse() {m_hasResponse = false;}
    inline AccessControlPtr& accessControl() {return m_accessControl;}
    inline bool hasAccessControl() {return m_accessControl != nullptr;}
    inline void setAccessControl(AccessControlPtr accessControl) {m_accessControl = accessControl;}

private:
    /*
     * Private Data Members
     */
    KineticMessage      m_request;          //!< Request message
    KineticMessage      m_response;         //!< Response message (may not be used)
    bool                m_hasResponse;      //!< True if a response is to be sent
    AccessControlPtr    m_accessControl;    //!< Access allowed for transaction
};

#endif
