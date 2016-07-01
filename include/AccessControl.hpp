/*
 * Copyright (c) 2014-2016 Western Digital Corporation or its affiliates <copyrightagent@wdc.com>
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
#ifndef ACCESS_CONTROL_HPP
#define ACCESS_CONTROL_HPP

/*
 * Include Files
 */
#include <stdint.h>
#include <list>
#include <memory>
#include <string>
#include <unordered_map>
#include "Hmac.hpp"
#include "Kinetic.pb.hpp"
#include "AccessScope.hpp"

/**
 * Describes the access limits that a single user has to perform operations on a Kinetic device.
 */
class AccessControl {
public:
    /*
     * Constructor
     */
    AccessControl(int64_t identity, std::string hmacKey, HmacAlgorithm hmacAlgorithm, AccessScopeList scopeList);

    /*
     * Public Member Functions
     */
    bool operationPermitted(Operation operation, bool operationInvolvesKey, const ::com::seagate::kinetic::proto::Command_Body& commandBody) const;
    inline int64_t identity() const {return m_identity;}
    inline const std::string& hmacKey() const {return m_hmacKey;}
    inline HmacAlgorithm hmacAlgorithm() const {return m_hmacAlgorithm;}
    inline const AccessScopeList& scopeList() const {return m_scopeList;}
    inline bool permissionToRead(const std::string& key) const { return permissionToPerformOperation(key, m_readScopeList);}
    inline bool permissionToGetRange(const std::string& key) const { return permissionToPerformOperation(key, m_rangeScopeList);}
    inline bool tlsRequired(Operation operation) const {
        return OPERATION_TO_UINT32(operation) < m_tlsRequiredArray.size() ? m_tlsRequiredArray[OPERATION_TO_UINT32(operation)] : false;
    }

private:
    /*
     * Private Member Functions
     */
    AccessScopeList getFilteredScopeList(Operation filterOperation) const;
    OperationSizedBoolArray getTlsRequiredArray() const;
    bool permissionToPerformOperation(const std::string& key, const AccessScopeList& scopeList) const;

    /*
     * Private Data Members
     */
    const int64_t                   m_identity;          //!< Identity of the user whose access this defines
    const std::string               m_hmacKey;           //!< The key to be used to generate messages' HMAC
    const HmacAlgorithm             m_hmacAlgorithm;     //!< The algorithm to be used to generate messages' HMAC
    const AccessScopeList           m_scopeList;         //!< List that defines the user's access/restrictions with all operations
    const AccessScopeList           m_readScopeList;     //!< List that defines the user's access/restrictions with read operations
    const AccessScopeList           m_rangeScopeList;    //!< List that defines the user's access/restrictions with range operations
    const OperationSizedBoolArray   m_tlsRequiredArray;  //!< Array used to determine if an operation requires secure communications
};

/*
 * Access Control Shared Pointer, List, and Unordered Map
 */
typedef std::shared_ptr<AccessControl> AccessControlPtr;
typedef std::list<AccessControlPtr> AccessControlList;
typedef std::unordered_map<int64_t, AccessControlPtr> AccessControlMap;

#endif
