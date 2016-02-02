/*
 * Copyright (c) [2014 - 2016] Western Digital Technologies, Inc. All rights reserved.
 */

/*
 * Include Files
 */
#include <stdint.h>
#include <string>
#include <vector>
#include <climits>
#include <utility>
#include "gtest/gtest.h"
#include "Logger.hpp"
#include "SystemConfig.hpp"
#include "AccessControl.hpp"
#include "KineticMessage.hpp"

/*
 * Global Variables
 */
SystemConfig systemConfig;
LogControl logControl;

/**
 * Create Large String
 *
 * @return a string with the maximum key size
 */
std::string createLargeString() {

    uint32_t stringSize = systemConfig.maxHmacKeySize();
    std::string pattern = "0123456789abcdef";
    std::string sizedString;
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
std::string createBinaryString(uint32_t count = 0x100, uint32_t offset = 0) {

    std::string binaryString;
    for (uint32_t index = 0; index < count; index++)
        binaryString += (offset + index);

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

/**
 * Create Access Control
 *
 * @param  keySubstring        permission's required key substring
 * @param  keySubstringOffset  permission's required key substring offset
 *
 * @return the access control initialized with specified values
 */
AccessControl createAccessControl(std::string keySubstring, uint32_t keySubstringOffset) {

    int64_t identity = systemConfig.accessControlDefaultIdentity();
    std::string hmacKey = systemConfig.accessControlDefaultHmacKey();
    HmacAlgorithm hmacAlgorithm = systemConfig.accessControlDefaultHmacAlgorithm();
    bool tlsRequired = systemConfig.accessControlDefaultTlsRequired();
    OperationSizedBoolArray operationArray;
    operationArray.fill(true);

    AccessScopeList scopeList;
    AccessScope accessScope(tlsRequired, keySubstring, keySubstringOffset, operationArray);
    scopeList.push_back(accessScope);
    AccessControl accessControl(identity, hmacKey, hmacAlgorithm, scopeList);
    return std::move(accessControl);
}

/**
 * Core Functionality Test
 *
 * Tests that the AccessControl object is correctly initialized when created with a varity of
 * parameters and that the getter functions work correctly.
 */
TEST(Access_Control_Unit_Test, Core_Functionality_Test) {

    std::vector<int64_t> identityArray = {0, 1, LLONG_MAX};
    std::vector<std::string> hmacKeyArray = {"0", createBinaryString(), createLargeString()};
    std::vector<HmacAlgorithm> hmacAlgorithmArray = {HmacAlgorithm::SHA1, HmacAlgorithm::UNKNOWN};
    std::vector<bool> tlsRequiredArray = {false, true};
    std::vector<std::string> keySubstringArray = {"", "0", createBinaryString(), createLargeString()};
    std::vector<size_t> keySubstringOffsetArray = {0, 1, systemConfig.maxKeySize() / 4, systemConfig.maxKeySize() - 1};
    KineticMessagePtr message(new KineticMessage());
    message->mutable_command()->mutable_body()->mutable_keyvalue()->set_key("SampleKey");

    /*
     * Create an AccessControl object for all the different combination of parameters.
     */
    for (uint32_t identityIndex = 0; identityIndex < identityArray.size(); ++identityIndex) {
        int64_t identity = identityArray[identityIndex];
        for (uint32_t hmacKeyIndex = 0; hmacKeyIndex < hmacKeyArray.size(); ++hmacKeyIndex) {
            std::string hmacKey = hmacKeyArray[hmacKeyIndex];
            for (uint32_t hmacAlgorithmIndex = 0; hmacAlgorithmIndex < hmacAlgorithmArray.size(); ++hmacAlgorithmIndex) {
                HmacAlgorithm hmacAlgorithm = hmacAlgorithmArray[hmacAlgorithmIndex];

                for (uint32_t tlsRequiredIndex = 0; tlsRequiredIndex < tlsRequiredArray.size(); ++tlsRequiredIndex) {
                    bool tlsRequired = tlsRequiredArray[tlsRequiredIndex];
                    for (uint32_t keySubstringIndex = 0; keySubstringIndex < keySubstringArray.size(); ++keySubstringIndex) {
                        std::string keySubstring = keySubstringArray[keySubstringIndex];
                        for (uint32_t keySubstringOffsetIndex = 0; keySubstringOffsetIndex < keySubstringOffsetArray.size(); ++keySubstringOffsetIndex) {
                            uint32_t keySubstringOffset = keySubstringOffsetArray[keySubstringOffsetIndex];
                            for (uint32_t patternCount = 0; patternCount < ((1 << NUMBER_OF_OPERATIONS) - 1); ++patternCount) {
                                OperationSizedBoolArray operationArray = createOperationArray(patternCount);

                                AccessScopeList scopeList;
                                {
                                    AccessScope accessScope(tlsRequired, keySubstring, keySubstringOffset, operationArray);
                                    scopeList.push_back(accessScope);
                                }
                                AccessControl accessControl(identity, hmacKey, hmacAlgorithm, scopeList);

                                /*
                                 * If non-zero offset is not valid if the key substring is not
                                 * specified.  The AccessScope class will set the offset to zero
                                 * so we must do the same thing before comparing expected values.
                                 */
                                if (keySubstring.size() == 0)
                                    keySubstringOffset = 0;

                                ASSERT_EQ(accessControl.identity(), identity);
                                ASSERT_STREQ(accessControl.hmacKey().c_str(), hmacKey.c_str());
                                ASSERT_EQ(static_cast<uint32_t>(accessControl.hmacAlgorithm()), static_cast<uint32_t>(hmacAlgorithm));

                                ASSERT_EQ(accessControl.scopeList().size(), 1U);

                                const AccessScope& accessScope = accessControl.scopeList().front();
                                ASSERT_EQ(accessScope.tlsRequired(), tlsRequired);
                                ASSERT_STREQ(accessScope.keySubstring().c_str(), keySubstring.c_str());
                                ASSERT_EQ(accessScope.keySubstringOffset(), keySubstringOffset);
                                ASSERT_EQ(accessScope.minimumKeySize(), keySubstring.size() + keySubstringOffset);

                                for (uint32_t operation = 0; operation < NUMBER_OF_OPERATIONS; ++operation) {
                                    bool operationInvolvesKey = ((UINT32_TO_OPERATION(operation) == Operation::WRITE)
                                                                 | (UINT32_TO_OPERATION(operation) == Operation::READ)
                                                                 | (UINT32_TO_OPERATION(operation) == Operation::DELETE));
                                    ASSERT_EQ(accessScope.operationPermitted(UINT32_TO_OPERATION(operation)), operationArray[operation]);
                                    ASSERT_EQ(accessControl.tlsRequired(UINT32_TO_OPERATION(operation)), (operationArray[operation] && accessScope.tlsRequired()));
                                    if (keySubstring.size() == 0)
                                        ASSERT_EQ(accessControl.operationPermitted(UINT32_TO_OPERATION(operation), operationInvolvesKey,
                                                  message->command()->body()), operationArray[operation]);
                                }

                                if (keySubstring.size() == 0) {
                                    ASSERT_EQ(accessControl.permissionToRead("DummyKey"), operationArray[OPERATION_TO_UINT32(Operation::READ)]);
                                    ASSERT_EQ(accessControl.permissionToGetRange("DummyKey"), operationArray[OPERATION_TO_UINT32(Operation::RANGE)]);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

TEST(Access_Control_Unit_Test, Permission_Single_Scope_Without_Offset_No_Match_Wrong_Text_Test) {

    std::string requestKey("SampleKey");
    KineticMessagePtr message(new KineticMessage());
    message->mutable_command()->mutable_body()->mutable_keyvalue()->set_key(requestKey);
    AccessControl accessControl = createAccessControl("Dummy", 0);
    ASSERT_FALSE(accessControl.operationPermitted(Operation::READ, true, message->command()->body()));
    ASSERT_FALSE(accessControl.permissionToRead(requestKey));
    ASSERT_FALSE(accessControl.permissionToGetRange(requestKey));
}

TEST(Access_Control_Unit_Test, Permission_Single_Scope_Without_Offset_No_Match_Wrong_Case_Test) {

    std::string requestKey("SampleKey");
    KineticMessagePtr message(new KineticMessage());
    message->mutable_command()->mutable_body()->mutable_keyvalue()->set_key(requestKey);
    AccessControl accessControl = createAccessControl("samplekey", 0);
    ASSERT_FALSE(accessControl.operationPermitted(Operation::READ, true, message->command()->body()));
    ASSERT_FALSE(accessControl.permissionToRead(requestKey));
    ASSERT_FALSE(accessControl.permissionToGetRange(requestKey));
}

TEST(Access_Control_Unit_Test, Permission_Single_Scope_Without_Offset_Simple_Match_Test) {

    std::string requestKey("SampleKey");
    KineticMessagePtr message(new KineticMessage());
    message->mutable_command()->mutable_body()->mutable_keyvalue()->set_key(requestKey);
    AccessControl accessControl = createAccessControl("Sample", 0);
    ASSERT_TRUE(accessControl.operationPermitted(Operation::READ, true, message->command()->body()));
    ASSERT_TRUE(accessControl.permissionToRead(requestKey));
    ASSERT_TRUE(accessControl.permissionToGetRange(requestKey));
}

TEST(Access_Control_Unit_Test, Permission_Single_Scope_Without_Offset_Match_Of_Minimum_Sized_Text_Key_Test) {

    std::string requestKey("abcdefghijklmnopqrstuvwxyz");
    KineticMessagePtr message(new KineticMessage());
    message->mutable_command()->mutable_body()->mutable_keyvalue()->set_key(requestKey);
    AccessControl accessControl = createAccessControl("a", 0);
    ASSERT_TRUE(accessControl.operationPermitted(Operation::READ, true, message->command()->body()));
    ASSERT_TRUE(accessControl.permissionToRead(requestKey));
    ASSERT_TRUE(accessControl.permissionToGetRange(requestKey));
}

TEST(Access_Control_Unit_Test, Permission_Single_Scope_Without_Offset_Exact_Match_Of_Minimum_Sized_Text_Key_Test) {

    std::string requestKey("a");
    KineticMessagePtr message(new KineticMessage());
    message->mutable_command()->mutable_body()->mutable_keyvalue()->set_key(requestKey);
    AccessControl accessControl = createAccessControl("a", 0);
    ASSERT_TRUE(accessControl.operationPermitted(Operation::READ, true, message->command()->body()));
    ASSERT_TRUE(accessControl.permissionToRead(requestKey));
    ASSERT_TRUE(accessControl.permissionToGetRange(requestKey));
}

TEST(Access_Control_Unit_Test, Permission_Single_Scope_Without_Offset_Match_Of_Maximum_Sized_Text_Key_Test) {

    std::string requestKey(createLargeString());
    KineticMessagePtr message(new KineticMessage());
    message->mutable_command()->mutable_body()->mutable_keyvalue()->set_key(requestKey);
    AccessControl accessControl = createAccessControl(createLargeString(), 0);
    ASSERT_TRUE(accessControl.operationPermitted(Operation::READ, true, message->command()->body()));
    ASSERT_TRUE(accessControl.permissionToRead(requestKey));
    ASSERT_TRUE(accessControl.permissionToGetRange(requestKey));
}

TEST(Access_Control_Unit_Test, Permission_Single_Scope_Without_Offset_Exact_Match_Of_Maximum_Sized_Text_Key_Test) {

    std::string requestKey(createLargeString());
    KineticMessagePtr message(new KineticMessage());
    message->mutable_command()->mutable_body()->mutable_keyvalue()->set_key(requestKey);
    AccessControl accessControl = createAccessControl(createLargeString(), 0);
    ASSERT_TRUE(accessControl.operationPermitted(Operation::READ, true, message->command()->body()));
    ASSERT_TRUE(accessControl.permissionToRead(requestKey));
    ASSERT_TRUE(accessControl.permissionToGetRange(requestKey));
}

TEST(Access_Control_Unit_Test, Permission_Single_Scope_Without_Offset_Exact_Match_Of_Binary_Key_Test) {

    std::string requestKey(createBinaryString());
    KineticMessagePtr message(new KineticMessage());
    message->mutable_command()->mutable_body()->mutable_keyvalue()->set_key(requestKey);
    AccessControl accessControl = createAccessControl(requestKey, 0);
    ASSERT_TRUE(accessControl.operationPermitted(Operation::READ, true, message->command()->body()));
    ASSERT_TRUE(accessControl.permissionToRead(requestKey));
    ASSERT_TRUE(accessControl.permissionToGetRange(requestKey));
}

TEST(Access_Control_Unit_Test, Permission_Single_Scope_With_Offset_No_Match_Of_Key_Test) {

    std::string requestKey("ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890");
    KineticMessagePtr message(new KineticMessage());
    message->mutable_command()->mutable_body()->mutable_keyvalue()->set_key(requestKey);

    for (uint32_t offset = 0; offset < 40; offset++) {
        if (offset != 10) {
            AccessControl accessControl = createAccessControl("KLMNOPQRST", offset);
            ASSERT_FALSE(accessControl.operationPermitted(Operation::READ, true, message->command()->body()));
            ASSERT_FALSE(accessControl.permissionToRead(requestKey));
            ASSERT_FALSE(accessControl.permissionToGetRange(requestKey));
        }
    }
}

TEST(Access_Control_Unit_Test, Permission_Single_Scope_With_Offset_Key_Smaller_Than_Offset_No_Match_Of_Key_Test) {

    std::string requestKey("ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890");
    KineticMessagePtr message(new KineticMessage());
    message->mutable_command()->mutable_body()->mutable_keyvalue()->set_key(requestKey);
    AccessControl accessControl = createAccessControl("KLMNOPQRST", 100);
    ASSERT_FALSE(accessControl.operationPermitted(Operation::READ, true, message->command()->body()));
    ASSERT_FALSE(accessControl.permissionToRead(requestKey));
    ASSERT_FALSE(accessControl.permissionToGetRange(requestKey));
}

TEST(Access_Control_Unit_Test, Permission_Single_Scope_With_Offset_Match_Of_Text_Key_Test) {

    std::string requestKey("ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890");
    KineticMessagePtr message(new KineticMessage());
    message->mutable_command()->mutable_body()->mutable_keyvalue()->set_key(requestKey);
    AccessControl accessControl = createAccessControl("KLMNOPQRST", 10);
    ASSERT_TRUE(accessControl.operationPermitted(Operation::READ, true, message->command()->body()));
    ASSERT_TRUE(accessControl.permissionToRead(requestKey));
    ASSERT_TRUE(accessControl.permissionToGetRange(requestKey));
}

TEST(Access_Control_Unit_Test, Permission_Single_Scope_With_Offset_Match_Of_Binary_Key_Test) {

    std::string requestKey(createBinaryString());
    KineticMessagePtr message(new KineticMessage());
    message->mutable_command()->mutable_body()->mutable_keyvalue()->set_key(requestKey);
    AccessControl accessControl = createAccessControl(createBinaryString(10, 10), 10);
    ASSERT_TRUE(accessControl.operationPermitted(Operation::READ, true, message->command()->body()));
    ASSERT_TRUE(accessControl.permissionToRead(requestKey));
    ASSERT_TRUE(accessControl.permissionToGetRange(requestKey));
}

TEST(Access_Control_Unit_Test, Permission_Single_Scope_With_Offset_Operation_Has_No_Key_Test) {

    KineticMessagePtr message(new KineticMessage());
    AccessControl accessControl = createAccessControl("KLMNOPQRST", 10);
    ASSERT_TRUE(accessControl.operationPermitted(Operation::SETUP, false, message->command()->body()));
}

// Still need to test with multiple scopes

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

