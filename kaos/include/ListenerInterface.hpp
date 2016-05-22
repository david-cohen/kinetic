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
#ifndef LISTENER_INTERFACE_HPP
#define LISTENER_INTERFACE_HPP

/*
 * Include Files
 */
#include <memory>

/*
 * Interface for a socket listener (used for new connections).
 */
class ListenerInterface {

public:
    virtual bool start() = 0;
    virtual void stop() = 0;
};

/*
 * Listener Interface Pointer
 */
typedef std::shared_ptr<ListenerInterface> ListenerInterfacePtr;

#endif
