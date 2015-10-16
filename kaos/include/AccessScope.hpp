/*
    Copyright (c) [2014 - 2015] Western Digital Technologies, Inc. All rights reserved.
*/

#pragma once
#ifndef ACCESS_SCOPE_HPP
#define ACCESS_SCOPE_HPP

/*
    Include Files
*/

#include <stdint.h>
#include <list>
#include <array>
#include <string>

/*
    Kinetic operations that a user can be given permission to perform.
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
    The following define conversion macros for converted an Operation enum to and from a 32-bit
    unsigned integer, the number of possible Kinetic operations, and a boolean array that has one
    entry for each operation, and .
*/

#define OPERATION_TO_UINT32(operation) (static_cast<uint32_t>(operation))
#define UINT32_TO_OPERATION(uint32) (static_cast<Operation>(uint32))
const uint32_t NUMBER_OF_OPERATIONS = OPERATION_TO_UINT32(Operation::INVALID);
typedef std::array<bool, NUMBER_OF_OPERATIONS> OperationSizedBoolArray;

/**
    Access Scope

    The operations that a user has permission to perform on a Kinetic device is defined by one or
    more access scopes.  Each scope can also indicate (optional) additional requirements needed to
    perform the permitted operations.  The additional requirements are: using secure communications
    (TLS/SSL) or only accessing objects whose key contains a specified substring at a specified
    offset in the key.  This object is based on the Kinetic Scope protocol buffer message.  All of
    its contents are constants so it is thread safe.
*/

class AccessScope {
public:

    /*
        Constructor
    */

    AccessScope(bool tlsRequired, std::string keySubstring, uint32_t keySubstringOffset, OperationSizedBoolArray operationArray)
        : m_tlsRequired(tlsRequired), m_keySubstring(keySubstring), m_keySubstringOffset(keySubstring.size() > 0 ? keySubstringOffset : 0),
          m_minimumKeySize(keySubstring.size() + m_keySubstringOffset), m_permittedOperationArray(operationArray) {}

    /*
        Getters
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
        Private Data Objects
    */

    const bool                      m_tlsRequired;              //!< True if these operations can only be performed when secure communications are being used (TLS/SSL)
    const std::string               m_keySubstring;             //!< If specified, key must contain specified key substring at specified key offset
    const uint32_t                  m_keySubstringOffset;       //!< If specified, key must contain specified key substring at specified key offset
    const uint32_t                  m_minimumKeySize;           //!< Minimum allowed key size when the key must match a specified substring
    const OperationSizedBoolArray   m_permittedOperationArray;  //!< Indicates the operations that the user is permitted to perform
};

typedef std::list<AccessScope> AccessScopeList;

#endif
