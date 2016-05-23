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
#ifndef ACCESS_SCOPE_HPP
#define ACCESS_SCOPE_HPP

/*
 * Include Files
 */
#include <stdint.h>
#include <list>
#include <array>
#include <string>

/*
 * Kinetic operations that a user can be given permission to perform.
 */
enum class Operation : uint32_t {
    READ     = 0,
    WRITE    = 1,
    DELETE   = 2,
    RANGE    = 3,
    SETUP    = 4,
    P2POP    = 5,
    GETLOG   = 6,
    SECURITY = 7,
    INVALID  = 8,
};

/*
 * The following define conversion macros for converting an Operation enum to and from a 32-bit
 * unsigned integer, the number of possible Kinetic operations, and a boolean array that has one
 * entry for each operation.
 */
#define OPERATION_TO_UINT32(operation) (static_cast<uint32_t>(operation))
#define UINT32_TO_OPERATION(uint32) (static_cast<Operation>(uint32))
const uint32_t NUMBER_OF_OPERATIONS = OPERATION_TO_UINT32(Operation::INVALID);
typedef std::array<bool, NUMBER_OF_OPERATIONS> OperationSizedBoolArray;

/**
 * Describes the operations that a user has permission to perform on a Kinetic device as well as
 * some optional additional requirements needed to perform the permitted operations.  The additional
 * requirements are: using secure communications (TLS/SSL) or only accessing objects whose key
 * contains a specified substring at a specified offset in the key.  This object is based on the
 * Kinetic Scope protocol buffer message. A user access can be defined by more than one access
 * scope.
 */
class AccessScope {
public:

    /*
     * Constructor
     */
    AccessScope(bool tlsRequired, std::string keySubstring, uint32_t keySubstringOffset, OperationSizedBoolArray operationArray)
        : m_tlsRequired(tlsRequired), m_keySubstring(keySubstring), m_keySubstringOffset(keySubstring.size() > 0 ? keySubstringOffset : 0),
          m_minimumKeySize(keySubstring.size() + m_keySubstringOffset), m_permittedOperationArray(operationArray) {}

    /*
     * Accessors
     */
    inline bool tlsRequired() const {return m_tlsRequired;}
    inline const std::string& keySubstring() const {return m_keySubstring;}
    inline uint32_t keySubstringOffset() const {return m_keySubstringOffset;}
    inline uint32_t minimumKeySize() const {return m_minimumKeySize;}
    inline bool operationPermitted(Operation operation) const {
        return OPERATION_TO_UINT32(operation) < m_permittedOperationArray.size()
               ? m_permittedOperationArray[OPERATION_TO_UINT32(operation)] : false;
    }

private:

    /*
     * Private Data Objects
     */
    const bool                      m_tlsRequired;              //!< True if these operations can only be performed when using (TLS/SSL)
    const std::string               m_keySubstring;             //!< If specified, key must contain specified key substring at specified key offset
    const uint32_t                  m_keySubstringOffset;       //!< If specified, key must contain specified key substring at specified key offset
    const uint32_t                  m_minimumKeySize;           //!< Minimum allowed key size when the key must match a specified substring
    const OperationSizedBoolArray   m_permittedOperationArray;  //!< Indicates the operations that the user is permitted to perform
};

/*
 * Access Scope List
 */
typedef std::list<AccessScope> AccessScopeList;

#endif
