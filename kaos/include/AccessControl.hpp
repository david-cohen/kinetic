/*
    Copyright (c) [2014 - 2015] Western Digital Technologies, Inc. All rights reserved.
*/

#pragma once
#ifndef ACCESS_CONTROL_HPP
#define ACCESS_CONTROL_HPP

/*
    Include Files
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
    Access Control

    The Kinetic Protocol supports restricting the operations that a user (identity) can perform using
    Access Control Lists (ACLs).  An access control object defines the access of a single user.  All
    the contents of the object are constants so it is thread safe.
*/

class AccessControl {
public:

    /*
        Constructor
    */

    AccessControl(int64_t identity, std::string hmacKey, HmacAlgorithm hmacAlgorithm, AccessScopeList scopeList);

    /*
        Public Member Functions
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
        Private Member Functions
    */

    AccessScopeList getFilteredScopeList(Operation filterOperation) const;
    OperationSizedBoolArray getTlsRequiredArray() const;
    bool permissionToPerformOperation(const std::string& key, const AccessScopeList& scopeList) const;

    /*
        Private Data Members
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
    Access Control Shared Pointer and Unordered Map
*/

typedef std::shared_ptr<AccessControl> AccessControlPtr;
typedef std::list<AccessControlPtr> AccessControlList;
typedef std::unordered_map<int64_t, AccessControlPtr> AccessControlMap;

#endif
