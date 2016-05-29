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
    Transaction()
        : request(new KineticMessage()), response(new KineticMessage()), accessControl() {}

    KineticMessagePtr   request;        //!< Request message
    KineticMessagePtr   response;       //!< Response message (may not be used)
    AccessControlPtr    accessControl;  //!< Access allowed for transaction
};

#endif
