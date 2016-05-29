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
#ifndef BATCH_INTERFACE_HPP
#define BATCH_INTERFACE_HPP

/*
 * Include Files
 */
#include <memory>
#include <string>
#include "Kinetic.pb.hpp"

/**
 * Defines the abstract object needed to perform batch operations using the object store interface.
 */
class BatchInterface {
public:
    virtual void putEntry(const com::seagate::kinetic::proto::Command_KeyValue& params, const std::string& value) = 0;
    virtual void deleteEntry(const com::seagate::kinetic::proto::Command_KeyValue& params) = 0;
    virtual void commit() = 0;
};

typedef std::shared_ptr<BatchInterface> BatchInterfacePtr;

#endif
