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

/*
 * Include Files
 */
#include <stdint.h>
#include <sys/stat.h>
#include <list>
#include <string>
#include <memory>
#include <fstream>
#include <iostream>
#include "Hmac.hpp"
#include "Logger.hpp"
#include "Translator.hpp"
#include "Settings.pb.hpp"
#include "GlobalConfig.hpp"
#include "AccessControl.hpp"
#include "ServerSettings.hpp"

/*
 * Initializes the Server Settings object.
 */
ServerSettings::ServerSettings()
    : m_filename(globalConfig.serverSettingsFile()) {

    /*
     * If possible, load the setting from persistent store.  Otherwise, set them to their default
     * values.
     */
    if (!load())
        setDefaults();
}

/*
 * Initializes the Server Settings object.
 *
 * @param   filename    Name of the file used to maintain the server settings
 */
ServerSettings::ServerSettings(const std::string& filename)
    : m_filename(filename) {

    /*
     * If possible, load the setting from persistent store.  Otherwise, set them to their default
     * values.
     */
    if (!load())
        setDefaults();
}

/**
 * Gets the access control for the identity specified.
 *
 * @param   identity    The identity of the user of access control is being requested
 *
 * @return  Pointer to the access control for the specified user
 */
AccessControlPtr ServerSettings::accessControl(int64_t identity) {
    AccessControlMap::const_iterator iter = m_accessControlMap.find(identity);
    return iter == m_accessControlMap.end() ? nullptr : iter->second;
}

/**
 * Replaces the previous access control with the new one specified.
 *
 * @param   newAccessControlList    New access control to use
 */
void ServerSettings::updateAccessControl(std::list<AccessControlPtr> newAccessControlList) {
    for (auto accessControl : newAccessControlList) {
        if (this->accessControl(accessControl->identity()) != nullptr)
            m_accessControlMap.erase(accessControl->identity());
        m_accessControlMap.insert({{accessControl->identity(), accessControl}});
    }
}

/**
 * Save the in memory server settings to persistence storage.
 */
void ServerSettings::save() {
    std::unique_ptr<kaos::Settings> settings(new kaos::Settings());

    settings->set_clusterversion(m_clusterVersion);
    settings->set_locked(m_locked);
    settings->set_lockpin(m_lockPin);
    settings->set_erasepin(m_erasePin);

    for (auto iter = m_accessControlMap.begin(); iter != m_accessControlMap.end(); ++iter) {
        auto accessControl = iter->second;
        kaos::Settings_ACL* accessControlSetting = settings->add_acl();
        accessControlSetting->set_identity(accessControl->identity());
        accessControlSetting->set_hmackey(accessControl->hmacKey());
        accessControlSetting->set_hmacalgorithm(Translator::toSettingsFormat(accessControl->hmacAlgorithm()));
        for (auto scope : accessControl->scopeList()) {
            kaos::Settings_ACL_Scope* scopeSetting = accessControlSetting->add_scope();
            scopeSetting->set_tlsrequired(scope.tlsRequired());
            scopeSetting->set_keysubstring(scope.keySubstring());
            scopeSetting->set_keysubstringoffset(scope.keySubstringOffset());
            for (uint32_t operation = 0; operation < NUMBER_OF_OPERATIONS; operation++) {
                if (scope.operationPermitted(UINT32_TO_OPERATION(operation)))
                    scopeSetting->add_operation(Translator::toSettingsFormat(UINT32_TO_OPERATION(operation)));
            }
        }
    }
    std::fstream out(m_filename.c_str(), std::ios::out | std::ios::binary | std::ios::trunc);
    settings->SerializeToOstream(&out);
    out.close();
}

/**
 * Set the values in the server settings to their default values and saves them to persistent
 * storage.
 */
void ServerSettings::setDefaults() {

    setClusterVersion(globalConfig.defaultClusterVersion());
    m_locked = globalConfig.defaultLocked();
    m_lockPin = globalConfig.defaultLockPin();
    m_erasePin = globalConfig.defaultErasePin();
    m_accessControlMap.clear();

    OperationSizedBoolArray operationArray;
    operationArray.fill(true);
    AccessScope scope(globalConfig.accessControlDefaultTlsRequired(),
                      globalConfig.accessScopeDefaultKeySubstring(),
                      globalConfig.accessScopeDefaultKeySubstringOffset(), operationArray);
    AccessScopeList scopeList;
    scopeList.push_back(scope);
    AccessControlPtr accessControl(new AccessControl(globalConfig.accessControlDefaultIdentity(),
                                   globalConfig.accessControlDefaultHmacKey(),
                                   globalConfig.accessControlDefaultHmacAlgorithm(), scopeList));
    std::list<AccessControlPtr> accessControlList;
    accessControlList.push_back(accessControl);
    updateAccessControl(accessControlList);
    save();
}

/*
 * Load the settings into memory from their persistent storage.
 */
bool ServerSettings::load() {

    struct stat info;
    if (stat(m_filename.c_str(), &info) != STATUS_SUCCESS)
        return false;

    std::unique_ptr<kaos::Settings> settings(new kaos::Settings());
    std::fstream input(m_filename.c_str(), std::ios::in | std::ios::binary);
    if (!settings->ParseFromIstream(&input)) {
        LOG(ERROR) << "Failed to load server settings";
        return false;
    }

    setClusterVersion(settings->clusterversion());
    setLocked(settings->locked());
    setLockPin(settings->lockpin());
    setErasePin(settings->erasepin());

    AccessControlList accessControlList;

    for (auto aclIndex = 0; aclIndex < settings->acl_size(); aclIndex++) {

        const ::kaos::Settings_ACL& acl = settings->acl(aclIndex);

        int64_t identity(acl.identity());
        std::string hmacKey(acl.hmackey());
        HmacAlgorithm hmacAlgorithm(Translator::fromSettingsFormat(acl.hmacalgorithm()));

        AccessScopeList scopeList;
        for (auto scopeIndex = 0; scopeIndex < acl.scope_size(); scopeIndex++) {
            const kaos::Settings_ACL_Scope& aclScope = acl.scope(scopeIndex);

            bool tlsRequired(false);
            uint32_t keySubstringOffset(0);
            std::string keySubString("");
            if (aclScope.has_tlsrequired())
                tlsRequired = aclScope.tlsrequired();
            if (aclScope.has_keysubstring()) {
                keySubString = aclScope.keysubstring();
                if (aclScope.has_keysubstringoffset())
                    keySubstringOffset = aclScope.keysubstringoffset();
            }

            OperationSizedBoolArray operationArray;
            operationArray.fill(false);
            for (auto operationIndex = 0; operationIndex < aclScope.operation_size(); operationIndex++) {
                Operation operation = Translator::fromSettingsFormat(aclScope.operation(operationIndex));
                if (OPERATION_TO_UINT32(operation) < operationArray.size())
                    operationArray[OPERATION_TO_UINT32(operation)] = true;
            }

            AccessScope accessScope(tlsRequired, keySubString, keySubstringOffset, operationArray);
            scopeList.push_back(accessScope);
        }
        AccessControlPtr accessControl(new AccessControl(identity, hmacKey, hmacAlgorithm, scopeList));
        accessControlList.push_back(accessControl);
    }
    updateAccessControl(accessControlList);
    return true;
}
