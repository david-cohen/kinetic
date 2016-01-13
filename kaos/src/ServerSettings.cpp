/*
 * Copyright (c) [2014 - 2016] Western Digital Technologies, Inc. All rights reserved.
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
#include "Common.hpp"
#include "Translator.hpp"
#include "Settings.pb.hpp"
#include "SystemConfig.hpp"
#include "AccessControl.hpp"
#include "ServerSettings.hpp"

/*
 * Server Settings
 */
ServerSettings::ServerSettings(std::string filename)
    : m_filename(filename) {

    if (!load())
        setDefaults();
}

AccessControlPtr
ServerSettings::accessControl(int64_t identity) {
    AccessControlMap::const_iterator iter = m_accessControlMap.find(identity);
    return iter == m_accessControlMap.end() ? nullptr : iter->second;
}

void
ServerSettings::updateAccessControl(std::list<AccessControlPtr> newAccessControlList) {
    for (auto accessControl : newAccessControlList) {
        if (this->accessControl(accessControl->identity()) != nullptr)
            m_accessControlMap.erase(accessControl->identity());
        m_accessControlMap.insert({{accessControl->identity(), accessControl}});
    }
}

void
ServerSettings::save() {
    std::unique_ptr<kaos::Settings> settings(new kaos::Settings());

    settings->set_clusterversion(m_clusterVersion);
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

void
ServerSettings::setDefaults() {

    setClusterVersion(systemConfig.defaultClusterVersion());
    m_lockPin = systemConfig.defaultLockPin();
    m_erasePin = systemConfig.defaultErasePin();
    m_accessControlMap.clear();

    OperationSizedBoolArray operationArray;
    operationArray.fill(true);
    AccessScope scope(systemConfig.accessControlDefaultTlsRequired(),
                      systemConfig.accessScopeDefaultKeySubstring(),
                      systemConfig.accessScopeDefaultKeySubstringOffset(), operationArray);
    AccessScopeList scopeList;
    scopeList.push_back(scope);
    AccessControlPtr accessControl(new AccessControl(systemConfig.accessControlDefaultIdentity(),
                                   systemConfig.accessControlDefaultHmacKey(),
                                   systemConfig.accessControlDefaultHmacAlgorithm(), scopeList));
    std::list<AccessControlPtr> accessControlList;
    accessControlList.push_back(accessControl);
    updateAccessControl(accessControlList);
#if 0
    save();
#endif
}

/*
 * Load
 *
 * Need to add multiple copies and add hash of their value
 */
bool
ServerSettings::load() {


    struct stat info;
    if (stat(m_filename.c_str(), &info) != STATUS_SUCCESS)
        return false;

    std::unique_ptr<kaos::Settings> settings(new kaos::Settings());
    std::fstream input(m_filename.c_str(), std::ios::in | std::ios::binary);
    if (!settings->ParseFromIstream(&input)) {
        std::cerr << "Failed to parse settings" << std::endl;
        return false;
    }

    setClusterVersion(settings->clusterversion());
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
