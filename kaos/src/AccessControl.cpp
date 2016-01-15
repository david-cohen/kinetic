/*
 * Copyright (c) [2014 - 2016] Western Digital Technologies, Inc. All rights reserved.
 */

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
#include "AccessControl.hpp"

/**
 * Access Control Constructor
 *
 * @param  identity        value of identity for new access control
 * @param  hmacKey         HMAC key of new access control
 * @param  hmacAlgorithm   HMAC algorithm of new access control
 * @param  scopeList       List of access scope for new access control
 */
AccessControl::AccessControl(int64_t identity, std::string hmacKey, HmacAlgorithm hmacAlgorithm, AccessScopeList scopeList)
    : m_identity(identity), m_hmacKey(hmacKey), m_hmacAlgorithm(hmacAlgorithm), m_scopeList(scopeList),
      m_readScopeList(getFilteredScopeList(Operation::READ)), m_rangeScopeList(getFilteredScopeList(Operation::RANGE)),
      m_tlsRequiredArray(getTlsRequiredArray()) {
}

/**
 * Operation Permitted
 *
 * @param  operation               the operation to be performed
 * @param  operationInvolvesKey    True if the operation uses a key
 * @param  commandBody             body of the request (used to get key if it has one)
 *
 * @return true if the operation has be performed, false otherwise
 *
 * Determine if the specified operation is permitted to be performed by checking the access control
 * settings.  Kinetic's access settings indicate what operations are permitted and if the operation
 * is permitted and involves a key, a further restriction may be specify that the key (for commands
 * with keys) contain a specified substring at a specified offset.
 */
bool
AccessControl::operationPermitted(Operation operation, bool operationInvolvesKey, const ::com::seagate::kinetic::proto::Command_Body& commandBody) const {

    if (operation == Operation::INVALID)
        return true;

    for (AccessScope scope : m_scopeList) {
        if (scope.operationPermitted(operation)) {
            const std::string& requiredKeySubstring = scope.keySubstring();
            if (requiredKeySubstring.empty() || !operationInvolvesKey)
                return true;
            if (commandBody.keyvalue().has_key()) {
                const std::string& key = commandBody.keyvalue().key();
                if ((requiredKeySubstring.empty()) || ((scope.minimumKeySize() <= key.size())
                                                       && (key.substr(scope.keySubstringOffset(), requiredKeySubstring.size()) == requiredKeySubstring))) {
                    return true;
                }
            }
        }
    }
    return false;
}

/**
 * Get Filtered Scope List
 *
 * @param  filterOperation the operation which the scope list is to be built for
 *
 * @return a list of scopes that only apply to the specified operation
 *
 * Build a list that describes the permitted access for the commands that perform the specified
 * operation.  This allows for a fast access check for the given operation (by not having to search
 * through access descriptors that don't apply to the operation being checked.
 */
AccessScopeList
AccessControl::getFilteredScopeList(Operation filterOperation) const {
    AccessScopeList filteredScopeList;
    for (auto scope : m_scopeList) {
        if (scope.operationPermitted(filterOperation)) {
            filteredScopeList.push_back(scope);
        }
    }
    return filteredScopeList;
}

/**
 * Get TLS Required Array
 *
 * @return an array that describes which operations (if any) require TLS/SSL)
 *
 * Based on the access settings, a look-up-table is build to allow for a quick check if the
 * operation requires TLS/SSL.
 */
OperationSizedBoolArray
AccessControl::getTlsRequiredArray() const {
    OperationSizedBoolArray tlsRequiredArray;
    tlsRequiredArray.fill(false);
    for (auto scope : m_scopeList) {
        if (scope.tlsRequired()) {
            for (uint32_t operation = 0; operation < NUMBER_OF_OPERATIONS; operation++) {
                if (scope.operationPermitted(UINT32_TO_OPERATION(operation))) {
                    tlsRequiredArray[operation] = true;
                }
            }
        }
    }
    return tlsRequiredArray;
}

/**
 * Permission To Perform Operation
 *
 * @param  key         the key to use for operation
 * @param  scopeList   operation specific list of scopes
 *
 * @return true if the key can be used for the operation
 *
 * Determines if the operation can be performed with the specified key (by checking the specified
 * access settings that correspond to operation being requested).
 */
bool
AccessControl::permissionToPerformOperation(const std::string& key, const AccessScopeList& scopeList) const {
    for (AccessScope scope : scopeList) {
        std::string requiredKeySubstring = scope.keySubstring();
        if ((requiredKeySubstring.empty()) || ((key.size() >= scope.minimumKeySize())
                                               && (key.substr(scope.keySubstringOffset(), requiredKeySubstring.size()) == requiredKeySubstring))) {
            return true;
        }
    }
    return false;
}
