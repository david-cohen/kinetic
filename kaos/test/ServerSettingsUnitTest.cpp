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

/*
 * Include Files
 */
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <list>
#include <vector>
#include <memory>
#include <string>
#include <climits>
#include "gtest/gtest.h"
#include "Hmac.hpp"
#include "Logger.hpp"
#include "Settings.pb.hpp"
#include "GlobalConfig.hpp"
#include "AccessControl.hpp"
#include "ServerSettings.hpp"
#include "KineticMessage.hpp"

/*
 * Used Namespaces
 */
using std::string;

/*
 * Global Variables
 */
GlobalConfig globalConfig;
LogControl logControl;

/*
 * Constants
 */
static const char* UNIT_TEST_SETTINGS_FILE("/tmp/testSettings");

bool
settingsFileExist(string filename) {
    struct stat info;
    return stat(filename.c_str(), &info) == STATUS_SUCCESS;
}

void
deleteSavedSettings() {
    if (settingsFileExist(UNIT_TEST_SETTINGS_FILE)) {
        string deleteCommand("rm " + string(UNIT_TEST_SETTINGS_FILE));
        system(deleteCommand.c_str());
    }
}

class Server_Settings_Unit_Test : public ::testing::Test {
protected:
    void SetUp() {
        deleteSavedSettings();
    }
    void TearDown() {
        deleteSavedSettings();
    }
};

/**
 * Create Large String
 *
 * @return a string with the maximum key size
 */
string createTextString(uint32_t stringSize) {
    string pattern = "0123456789abcdef";
    string sizedString;
    for (uint32_t index = 0; index < (stringSize / pattern.size()); index++)
        sizedString += pattern;

    for (uint32_t index = 0; index < (stringSize % pattern.size()); index++)
        sizedString += "" + pattern[index];

    return sizedString;
}

/**
 * Create Binary String
 *
 * @return a string contains binary values from 0 to 0xff
 */
string createBinaryString(uint32_t stringSize) {
    string binaryString;
    for (uint32_t index = 0; index < stringSize; index++)
        binaryString += (index & 0xff);

    return binaryString;
}

/**
 * Create Operation Array
 *
 * @param  bitmap  a bitmap that indicates which operations are to be allowed, each bit represents
 *                 a different operation
 *
 * @return the operation array initialized based on the specified bitmap
 */
OperationSizedBoolArray createOperationArray(uint32_t bitmap) {
    OperationSizedBoolArray operationArray;
    for (uint32_t operation = 0; operation < operationArray.size(); operation++)
        operationArray[operation] = (bitmap & (1 << operation)) ? true : false;

    return move(operationArray);
}

TEST_F(Server_Settings_Unit_Test, Hmac_Algorithm_From_Settings_Format_Test) {
    ASSERT_EQ(kaos::Settings_ACL_HmacAlgorithm_HmacAlgorithm_ARRAYSIZE, 2);
    ASSERT_EQ(ServerSettings::fromSettingsFormat(kaos::Settings_ACL_HmacAlgorithm_HMAC_SHA1), HmacAlgorithm::SHA1);
    ASSERT_EQ(ServerSettings::fromSettingsFormat(kaos::Settings_ACL_HmacAlgorithm_HMAC_INVALID), HmacAlgorithm::UNKNOWN);
    kaos::Settings_ACL_HmacAlgorithm unknownAlgorithm = static_cast<kaos::Settings_ACL_HmacAlgorithm>(100);
    ASSERT_EQ(ServerSettings::fromSettingsFormat(unknownAlgorithm), HmacAlgorithm::UNKNOWN);
}

TEST_F(Server_Settings_Unit_Test, Hmac_Algorithm_To_Settings_Format_Test) {
    ASSERT_EQ(ServerSettings::toSettingsFormat(HmacAlgorithm::SHA1), kaos::Settings_ACL_HmacAlgorithm_HMAC_SHA1);
    ASSERT_EQ(ServerSettings::toSettingsFormat(HmacAlgorithm::UNKNOWN), kaos::Settings_ACL_HmacAlgorithm_HMAC_INVALID);
    ASSERT_EQ(ServerSettings::toSettingsFormat(static_cast<HmacAlgorithm>(101)), kaos::Settings_ACL_HmacAlgorithm_HMAC_INVALID);
}

TEST_F(Server_Settings_Unit_Test, Operation_From_Setting_Format_Test) {
    ASSERT_EQ(ServerSettings::fromSettingsFormat(kaos::Settings_ACL_Operation::Settings_ACL_Operation_READ), Operation::READ);
    ASSERT_EQ(ServerSettings::fromSettingsFormat(kaos::Settings_ACL_Operation::Settings_ACL_Operation_WRITE), Operation::WRITE);
    ASSERT_EQ(ServerSettings::fromSettingsFormat(kaos::Settings_ACL_Operation::Settings_ACL_Operation_DELETE), Operation::DELETE);
    ASSERT_EQ(ServerSettings::fromSettingsFormat(kaos::Settings_ACL_Operation::Settings_ACL_Operation_RANGE), Operation::RANGE);
    ASSERT_EQ(ServerSettings::fromSettingsFormat(kaos::Settings_ACL_Operation::Settings_ACL_Operation_SETUP), Operation::SETUP);
    ASSERT_EQ(ServerSettings::fromSettingsFormat(kaos::Settings_ACL_Operation::Settings_ACL_Operation_P2POP), Operation::P2POP);
    ASSERT_EQ(ServerSettings::fromSettingsFormat(kaos::Settings_ACL_Operation::Settings_ACL_Operation_GETLOG), Operation::GETLOG);
    ASSERT_EQ(ServerSettings::fromSettingsFormat(kaos::Settings_ACL_Operation::Settings_ACL_Operation_SECURITY), Operation::SECURITY);
    ASSERT_EQ(ServerSettings::fromSettingsFormat(static_cast<kaos::Settings_ACL_Operation>(103)), Operation::INVALID);
}

TEST_F(Server_Settings_Unit_Test, Operation_To_Setting_Format_Test) {
    ASSERT_EQ(ServerSettings::toSettingsFormat(Operation::READ), kaos::Settings_ACL_Operation::Settings_ACL_Operation_READ);
    ASSERT_EQ(ServerSettings::toSettingsFormat(Operation::WRITE), kaos::Settings_ACL_Operation::Settings_ACL_Operation_WRITE);
    ASSERT_EQ(ServerSettings::toSettingsFormat(Operation::DELETE), kaos::Settings_ACL_Operation::Settings_ACL_Operation_DELETE);
    ASSERT_EQ(ServerSettings::toSettingsFormat(Operation::RANGE), kaos::Settings_ACL_Operation::Settings_ACL_Operation_RANGE);
    ASSERT_EQ(ServerSettings::toSettingsFormat(Operation::SETUP), kaos::Settings_ACL_Operation::Settings_ACL_Operation_SETUP);
    ASSERT_EQ(ServerSettings::toSettingsFormat(Operation::P2POP), kaos::Settings_ACL_Operation::Settings_ACL_Operation_P2POP);
    ASSERT_EQ(ServerSettings::toSettingsFormat(Operation::GETLOG), kaos::Settings_ACL_Operation::Settings_ACL_Operation_GETLOG);
    ASSERT_EQ(ServerSettings::toSettingsFormat(Operation::SECURITY), kaos::Settings_ACL_Operation::Settings_ACL_Operation_SECURITY);
    ASSERT_EQ(ServerSettings::toSettingsFormat(static_cast<Operation>(104)), kaos::Settings_ACL_Operation::Settings_ACL_Operation_GETLOG);
}

TEST_F(Server_Settings_Unit_Test, Default_Values_On_Initial_Creation) {
    /*
     * Make sure that the test settings file does not exist (it should have been deleted in setup).
     */
    ASSERT_FALSE(settingsFileExist(UNIT_TEST_SETTINGS_FILE));
    ServerSettings serverSettings(UNIT_TEST_SETTINGS_FILE);

    /*
     * Check server settings default values.
     */
    ASSERT_TRUE(serverSettings.locked() == globalConfig.defaultLocked());
    ASSERT_TRUE(serverSettings.lockPin() == globalConfig.defaultLockPin());
    ASSERT_TRUE(serverSettings.erasePin() == globalConfig.defaultErasePin());
    ASSERT_EQ(serverSettings.clusterVersion(), globalConfig.defaultClusterVersion());
    ASSERT_EQ(serverSettings.accessControlMap().size(), 1U);

    /*
     * Check access control default values.
     */
    AccessControlPtr accessControl(serverSettings.accessControl(globalConfig.accessControlDefaultIdentity()));
    ASSERT_NE(accessControl, nullptr);

    ASSERT_EQ(accessControl->identity(), globalConfig.accessControlDefaultIdentity());
    ASSERT_STREQ(accessControl->hmacKey().c_str(), globalConfig.accessControlDefaultHmacKey().c_str());
    ASSERT_TRUE(accessControl->hmacAlgorithm() == globalConfig.accessControlDefaultHmacAlgorithm());

    std::unique_ptr<KineticMessage> message(new KineticMessage());
    for (uint32_t operation = 0; operation < NUMBER_OF_OPERATIONS; operation++) {
        bool operationInvolvesKey = ((UINT32_TO_OPERATION(operation) == Operation::WRITE)
                                     | (UINT32_TO_OPERATION(operation) == Operation::READ)
                                     | (UINT32_TO_OPERATION(operation) == Operation::DELETE));
        ASSERT_EQ(accessControl->operationPermitted(UINT32_TO_OPERATION(operation), operationInvolvesKey, message->command()->body()), true);
        ASSERT_FALSE(accessControl->tlsRequired(UINT32_TO_OPERATION(operation)));
    }

    ASSERT_TRUE(accessControl->permissionToRead(""));
    ASSERT_TRUE(accessControl->permissionToRead("1234567890"));
    ASSERT_TRUE(accessControl->permissionToGetRange(""));
    ASSERT_TRUE(accessControl->permissionToGetRange("1234567890"));
    ASSERT_EQ(accessControl->scopeList().size(), 1U);

    /*
     * Check access scope default values.
     */
    const AccessScope& accessScope = accessControl->scopeList().front();
    ASSERT_EQ(accessScope.tlsRequired(), globalConfig.accessControlDefaultTlsRequired());
    ASSERT_STREQ(accessScope.keySubstring().c_str(), globalConfig.accessScopeDefaultKeySubstring().c_str());
    ASSERT_EQ(accessScope.keySubstringOffset(), globalConfig.accessScopeDefaultKeySubstringOffset());
    ASSERT_EQ(accessScope.minimumKeySize(), globalConfig.accessScopeDefaultKeySubstring().size()
              + globalConfig.accessScopeDefaultKeySubstringOffset());

    for (uint32_t operation = 0; operation < NUMBER_OF_OPERATIONS; ++operation)
        ASSERT_EQ(accessScope.operationPermitted(UINT32_TO_OPERATION(operation)), true);
}

TEST_F(Server_Settings_Unit_Test, Default_Values_Persisted_After_Initial_Creation) {
    /*
     * Make sure that the test settings file does not exist (it should have been deleted in setup).
     */
    ASSERT_FALSE(settingsFileExist(UNIT_TEST_SETTINGS_FILE));
    ServerSettings serverSettings(UNIT_TEST_SETTINGS_FILE);

    /*
     * Check server settings default values.
     */
    ASSERT_TRUE(serverSettings.locked() == globalConfig.defaultLocked());
    ASSERT_TRUE(serverSettings.lockPin() == globalConfig.defaultLockPin());
    ASSERT_TRUE(serverSettings.erasePin() == globalConfig.defaultErasePin());
    ASSERT_EQ(serverSettings.clusterVersion(), globalConfig.defaultClusterVersion());
    ASSERT_EQ(serverSettings.accessControlMap().size(), 1U);

    /*
     * Check access control default values.
     */
    AccessControlPtr accessControl(serverSettings.accessControl(globalConfig.accessControlDefaultIdentity()));
    ASSERT_NE(accessControl, nullptr);

    ASSERT_EQ(accessControl->identity(), globalConfig.accessControlDefaultIdentity());
    ASSERT_STREQ(accessControl->hmacKey().c_str(), globalConfig.accessControlDefaultHmacKey().c_str());
    ASSERT_TRUE(accessControl->hmacAlgorithm() == globalConfig.accessControlDefaultHmacAlgorithm());

    std::unique_ptr<KineticMessage> message(new KineticMessage());
    for (uint32_t operation = 0; operation < NUMBER_OF_OPERATIONS; operation++) {
        bool operationInvolvesKey = ((UINT32_TO_OPERATION(operation) == Operation::WRITE)
                                     | (UINT32_TO_OPERATION(operation) == Operation::READ)
                                     | (UINT32_TO_OPERATION(operation) == Operation::DELETE));
        ASSERT_EQ(accessControl->operationPermitted(UINT32_TO_OPERATION(operation),
                  operationInvolvesKey, message->command()->body()), true);
        ASSERT_FALSE(accessControl->tlsRequired(UINT32_TO_OPERATION(operation)));
    }

    ASSERT_TRUE(accessControl->permissionToRead(""));
    ASSERT_TRUE(accessControl->permissionToRead("1234567890"));
    ASSERT_TRUE(accessControl->permissionToGetRange(""));
    ASSERT_TRUE(accessControl->permissionToGetRange("1234567890"));
    ASSERT_EQ(accessControl->scopeList().size(), 1U);

    /*
     * Check access scope default values.
     */
    const AccessScope& accessScope = accessControl->scopeList().front();
    ASSERT_EQ(accessScope.tlsRequired(), globalConfig.accessControlDefaultTlsRequired());
    ASSERT_STREQ(accessScope.keySubstring().c_str(), globalConfig.accessScopeDefaultKeySubstring().c_str());
    ASSERT_EQ(accessScope.keySubstringOffset(), globalConfig.accessScopeDefaultKeySubstringOffset());
    ASSERT_EQ(accessScope.minimumKeySize(), globalConfig.accessScopeDefaultKeySubstring().size()
              + globalConfig.accessScopeDefaultKeySubstringOffset());

    for (uint32_t operation = 0; operation < NUMBER_OF_OPERATIONS; ++operation)
        ASSERT_EQ(accessScope.operationPermitted(UINT32_TO_OPERATION(operation)), true);
}

TEST_F(Server_Settings_Unit_Test, Set_Get_Save_Load_Locked_Test) {
    /*
     * Make sure that the test settings file does not exist (it should have been deleted in setup).
     */
    ASSERT_FALSE(settingsFileExist(UNIT_TEST_SETTINGS_FILE));

    /*
     * Check server settings default values.
     */
    {
        ServerSettings serverSettings(UNIT_TEST_SETTINGS_FILE);
        ASSERT_TRUE(serverSettings.locked() == globalConfig.defaultLocked());
        ASSERT_TRUE(serverSettings.lockPin() == globalConfig.defaultLockPin());
        ASSERT_TRUE(serverSettings.erasePin() == globalConfig.defaultErasePin());
        ASSERT_EQ(serverSettings.clusterVersion(), globalConfig.defaultClusterVersion());
        ASSERT_EQ(serverSettings.accessControlMap().size(), 1U);

        serverSettings.setLocked(true);
        ASSERT_TRUE(serverSettings.locked());
        ASSERT_TRUE(serverSettings.lockPin() == globalConfig.defaultLockPin());
        ASSERT_TRUE(serverSettings.erasePin() == globalConfig.defaultErasePin());
        ASSERT_EQ(serverSettings.clusterVersion(), globalConfig.defaultClusterVersion());
        ASSERT_EQ(serverSettings.accessControlMap().size(), 1U);
        serverSettings.save();
    }

    /*
     * Check that the locked value was saved and restored correctly when true.
     */
    {
        ServerSettings serverSettings(UNIT_TEST_SETTINGS_FILE);
        ASSERT_TRUE(serverSettings.locked());
        ASSERT_TRUE(serverSettings.lockPin() == globalConfig.defaultLockPin());
        ASSERT_TRUE(serverSettings.erasePin() == globalConfig.defaultErasePin());
        ASSERT_EQ(serverSettings.clusterVersion(), globalConfig.defaultClusterVersion());
        ASSERT_EQ(serverSettings.accessControlMap().size(), 1U);

        serverSettings.setLocked(false);
        ASSERT_FALSE(serverSettings.locked());
        ASSERT_TRUE(serverSettings.lockPin() == globalConfig.defaultLockPin());
        ASSERT_TRUE(serverSettings.erasePin() == globalConfig.defaultErasePin());
        ASSERT_EQ(serverSettings.clusterVersion(), globalConfig.defaultClusterVersion());
        ASSERT_EQ(serverSettings.accessControlMap().size(), 1U);
        serverSettings.save();
    }

    /*
     * Check that the locked value was saved and restored correctly when false.
     */
    {
        ServerSettings serverSettings(UNIT_TEST_SETTINGS_FILE);
        ASSERT_FALSE(serverSettings.locked());
        ASSERT_TRUE(serverSettings.lockPin() == globalConfig.defaultLockPin());
        ASSERT_TRUE(serverSettings.erasePin() == globalConfig.defaultErasePin());
        ASSERT_EQ(serverSettings.clusterVersion(), globalConfig.defaultClusterVersion());
        ASSERT_EQ(serverSettings.accessControlMap().size(), 1U);
    }
}

TEST_F(Server_Settings_Unit_Test, Set_Get_Save_Load_Pin_Test) {
    /*
     * Make sure that the test settings file does not exist (it should have been deleted in setup).
     */
    ASSERT_FALSE(settingsFileExist(UNIT_TEST_SETTINGS_FILE));

    std::vector<string> pinArray = {"a", createBinaryString(globalConfig.maxPinSize()), createTextString(globalConfig.maxPinSize()), ""};
    for (uint32_t pinIndex = 0; pinIndex < pinArray.size(); ++pinIndex) {
        string newLockPin = pinArray[pinIndex];
        string newErasePin = pinArray[pinArray.size() - 1 - pinIndex];
        {
            ServerSettings serverSettings(UNIT_TEST_SETTINGS_FILE);
            serverSettings.setLockPin(newLockPin);
            serverSettings.setErasePin(newErasePin);
            serverSettings.save();
            ASSERT_TRUE(serverSettings.lockPin() == newLockPin);
            ASSERT_TRUE(serverSettings.erasePin() == newErasePin);
            ASSERT_EQ(serverSettings.clusterVersion(), globalConfig.defaultClusterVersion());
            ASSERT_EQ(serverSettings.accessControlMap().size(), 1U);
        }

        {
            ServerSettings serverSettings(UNIT_TEST_SETTINGS_FILE);
            ASSERT_TRUE(serverSettings.locked() == globalConfig.defaultLocked());
            ASSERT_TRUE(serverSettings.lockPin() == newLockPin);
            ASSERT_TRUE(serverSettings.erasePin() == newErasePin);
            ASSERT_EQ(serverSettings.clusterVersion(), globalConfig.defaultClusterVersion());
            ASSERT_EQ(serverSettings.accessControlMap().size(), 1U);
        }
    }
}

TEST_F(Server_Settings_Unit_Test, Set_Get_Save_Load_Cluster_Version_Test) {
    /*
     * Make sure that the test settings file does not exist (it should have been deleted in setup).
     */
    ASSERT_FALSE(settingsFileExist(UNIT_TEST_SETTINGS_FILE));

    std::vector<int64_t> clusterVersionArray = {LLONG_MAX, LLONG_MAX / 2, LLONG_MAX / 4, 1, 0};
    for (uint32_t clusterVersionIndex = 0; clusterVersionIndex < clusterVersionArray.size(); ++clusterVersionIndex) {
        int64_t newClusterVersion = clusterVersionArray[clusterVersionIndex];
        {
            ServerSettings serverSettings(UNIT_TEST_SETTINGS_FILE);
            serverSettings.setClusterVersion(newClusterVersion);
            serverSettings.save();
            ASSERT_EQ(serverSettings.clusterVersion(), newClusterVersion);
            ASSERT_TRUE(serverSettings.locked() == globalConfig.defaultLocked());
            ASSERT_TRUE(serverSettings.lockPin() == globalConfig.defaultLockPin());
            ASSERT_TRUE(serverSettings.erasePin() == globalConfig.defaultErasePin());
            ASSERT_EQ(serverSettings.accessControlMap().size(), 1U);
        }
        {
            ServerSettings serverSettings(UNIT_TEST_SETTINGS_FILE);
            ASSERT_EQ(serverSettings.clusterVersion(), newClusterVersion);
            ASSERT_TRUE(serverSettings.locked() == globalConfig.defaultLocked());
            ASSERT_TRUE(serverSettings.lockPin() == globalConfig.defaultLockPin());
            ASSERT_TRUE(serverSettings.erasePin() == globalConfig.defaultErasePin());
            ASSERT_EQ(serverSettings.accessControlMap().size(), 1U);
        }
    }
}

TEST_F(Server_Settings_Unit_Test, Set_Get_Save_Load_Access_Control_Test) {
    /*
     * Make sure that the test settings file does not exist (it should have been deleted in setup).
     */
    ASSERT_FALSE(settingsFileExist(UNIT_TEST_SETTINGS_FILE));

    std::vector<int64_t> identityArray = {0, LLONG_MAX};
    std::vector<string> hmacKeyArray = {"0", createBinaryString(globalConfig.maxHmacKeySize()), createTextString(globalConfig.maxHmacKeySize())};
    std::vector<HmacAlgorithm> hmacAlgorithmArray = {HmacAlgorithm::SHA1, HmacAlgorithm::UNKNOWN};
    std::vector<bool> tlsRequiredArray = {false, true};
    std::vector<string> keySubstringArray = {"", "0", createBinaryString(globalConfig.maxKeySize()), createTextString(globalConfig.maxKeySize())};
    std::vector<size_t> keySubstringOffsetArray = {0, 1, globalConfig.maxKeySize() - 1};
    std::unique_ptr<KineticMessage> message(new KineticMessage());
    message->mutable_command()->mutable_body()->mutable_keyvalue()->set_key("SampleKey");

    /*
     * Create an AccessControl object for all the different combination of parameters.
     */
    for (int64_t identity : identityArray) {
        for (string hmacKey : hmacKeyArray) {
            for (HmacAlgorithm hmacAlgorithm : hmacAlgorithmArray) {
                for (bool tlsRequired : tlsRequiredArray) {
                    for (string keySubstring : keySubstringArray) {
                        for (uint32_t keySubstringOffset : keySubstringOffsetArray) {
                            for (uint32_t patternCount = 0; patternCount < ((1 << NUMBER_OF_OPERATIONS) - 1); ++patternCount) {
                                OperationSizedBoolArray operationArray = createOperationArray(patternCount);
                                {
                                    AccessScopeList scopeList;
                                    {
                                        AccessScope accessScope(tlsRequired, keySubstring, keySubstringOffset, operationArray);
                                        scopeList.push_back(accessScope);
                                    }
                                    AccessControlPtr accessControl(new AccessControl(identity, hmacKey, hmacAlgorithm, scopeList));
                                    std::list<AccessControlPtr> accessControlList;
                                    accessControlList.push_back(accessControl);

                                    ServerSettings serverSettings(UNIT_TEST_SETTINGS_FILE);
                                    serverSettings.updateAccessControl(accessControlList);
                                    serverSettings.save();
                                }

                                ServerSettings serverSettings(UNIT_TEST_SETTINGS_FILE);
                                AccessControlPtr accessControl = serverSettings.accessControl(identity);

                                /*
                                 * If non-zero offset is not valid if the key substring is not specified.  The
                                 * AccessScope class will set the offset to zero so we must do the same thing
                                 * before comparing expected values.
                                 */
                                if (keySubstring.size() == 0)
                                    keySubstringOffset = 0;

                                ASSERT_EQ(accessControl->identity(), identity);
                                ASSERT_STREQ(accessControl->hmacKey().c_str(), hmacKey.c_str());
                                ASSERT_EQ(static_cast<uint32_t>(accessControl->hmacAlgorithm()), static_cast<uint32_t>(hmacAlgorithm));

                                ASSERT_EQ(accessControl->scopeList().size(), 1U);

                                const AccessScope& accessScope = accessControl->scopeList().front();
                                ASSERT_EQ(accessScope.tlsRequired(), tlsRequired);
                                ASSERT_STREQ(accessScope.keySubstring().c_str(), keySubstring.c_str());
                                ASSERT_EQ(accessScope.keySubstringOffset(), keySubstringOffset);
                                ASSERT_EQ(accessScope.minimumKeySize(), keySubstring.size() + keySubstringOffset);

                                for (uint32_t operation = 0; operation < NUMBER_OF_OPERATIONS; ++operation) {
                                    bool operationInvolvesKey = ((UINT32_TO_OPERATION(operation) == Operation::WRITE)
                                                                 | (UINT32_TO_OPERATION(operation) == Operation::READ)
                                                                 | (UINT32_TO_OPERATION(operation) == Operation::DELETE));
                                    ASSERT_EQ(accessScope.operationPermitted(UINT32_TO_OPERATION(operation)), operationArray[operation]);
                                    ASSERT_EQ(accessControl->tlsRequired(UINT32_TO_OPERATION(operation)),
                                              (operationArray[operation] && accessScope.tlsRequired()));
                                    if (keySubstring.size() == 0)
                                        ASSERT_EQ(accessControl->operationPermitted(UINT32_TO_OPERATION(operation),
                                                  operationInvolvesKey, message->command()->body()), operationArray[operation]);
                                }

                                if (keySubstring.size() == 0) {
                                    ASSERT_EQ(accessControl->permissionToRead("DummyKey"),
                                              operationArray[OPERATION_TO_UINT32(Operation::READ)]);
                                    ASSERT_EQ(accessControl->permissionToGetRange("DummyKey"),
                                              operationArray[OPERATION_TO_UINT32(Operation::RANGE)]);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

