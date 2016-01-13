/*
 * Copyright (c) [2014 - 2016] Western Digital Technologies, Inc. All rights reserved.
 */

/*
 * Include Files
 */
#include <stdint.h>
#include <string>
#include "gtest/gtest.h"
#include "Translator.hpp"
#include "Kinetic.pb.hpp"

TEST(Translator_Unit_Test, Hmac_Algorithm_From_Settings_Format_Test) {

    ASSERT_EQ(kaos::Settings_ACL_HmacAlgorithm_HmacAlgorithm_ARRAYSIZE, 2);
    ASSERT_EQ(Translator::fromSettingsFormat(kaos::Settings_ACL_HmacAlgorithm_HMAC_SHA1), HmacAlgorithm::SHA1);
    ASSERT_EQ(Translator::fromSettingsFormat(kaos::Settings_ACL_HmacAlgorithm_HMAC_INVALID), HmacAlgorithm::UNKNOWN);
    ASSERT_EQ(Translator::fromSettingsFormat(static_cast<kaos::Settings_ACL_HmacAlgorithm>(kaos::Settings_ACL_HmacAlgorithm_HmacAlgorithm_ARRAYSIZE)), HmacAlgorithm::UNKNOWN);
}

TEST(Translator_Unit_Test, Hmac_Algorithm_To_Settings_Format) {

    ASSERT_EQ(Translator::toSettingsFormat(HmacAlgorithm::SHA1), kaos::Settings_ACL_HmacAlgorithm_HMAC_SHA1);
    ASSERT_EQ(Translator::toSettingsFormat(HmacAlgorithm::UNKNOWN), kaos::Settings_ACL_HmacAlgorithm_HMAC_INVALID);
//  ASSERT_EQ(Translator.toSettingsFormat(static_cast<kaos::Settings_ACL_HmacAlgorithm>(kaos::Settings_ACL_HmacAlgorithm_HmacAlgorithm_ARRAYSIZE)), HmacAlgorithm::UNKNOWN);
}

#if 0
HmacAlgorithm
Translator::fromMessageFormat(com::seagate::kinetic::proto::Command_Security_ACL_HMACAlgorithm hmacAlgorithm) {
    if (hmacAlgorithm == com::seagate::kinetic::proto::Command_Security_ACL_HMACAlgorithm::Command_Security_ACL_HMACAlgorithm_HmacSHA1)
        return HmacAlgorithm::SHA1;
    else
        return HmacAlgorithm::UNKNOWN;
}
#endif

TEST(Translator_Unit_Test, Hmac_Algorithm_From_Message_Format) {
//  ASSERT_EQ(com::seagate::kinetic::proto::Command_Security_ACL_HMACAlgorithm::Settings_ACL_HmacAlgorithm_HmacAlgorithm_ARRAYSIZE, 2);
    ASSERT_EQ(Translator::fromMessageFormat(com::seagate::kinetic::proto::Command_Security_ACL_HMACAlgorithm::Command_Security_ACL_HMACAlgorithm_HmacSHA1), HmacAlgorithm::SHA1);
//  ASSERT_EQ(Translator::fromMessageFormat(com::seagate::kinetic::proto::Command_Security_ACL_HMACAlgorithm::Settings_ACL_HmacAlgorithm_HMAC_INVALID), HmacAlgorithm::UNKNOWN);
}

#if 0
Operation
Translator::fromSettingsFormat(kaos::Settings_ACL_Operation operation) {
    switch (operation) {
        case kaos::Settings_ACL_Operation::Settings_ACL_Operation_READ:
            return Operation::READ;
        case kaos::Settings_ACL_Operation::Settings_ACL_Operation_WRITE:
            return Operation::WRITE;
        case kaos::Settings_ACL_Operation::Settings_ACL_Operation_DELETE:
            return Operation::DELETE;
        case kaos::Settings_ACL_Operation::Settings_ACL_Operation_RANGE:
            return Operation::RANGE;
        case kaos::Settings_ACL_Operation::Settings_ACL_Operation_SETUP:
            return Operation::SETUP;
        case kaos::Settings_ACL_Operation::Settings_ACL_Operation_P2POP:
            return Operation::P2POP;
        case kaos::Settings_ACL_Operation::Settings_ACL_Operation_GETLOG:
            return Operation::GETLOG;
        case kaos::Settings_ACL_Operation::Settings_ACL_Operation_SECURITY:
            return Operation::SECURITY;
        default:
            break;
    }
    return Operation::INVALID;
}
#endif

TEST(Translator_Unit_Test, Operation_From_Setting_Format) {

    ASSERT_EQ(Translator::fromSettingsFormat(kaos::Settings_ACL_Operation::Settings_ACL_Operation_READ), Operation::READ);
    ASSERT_EQ(Translator::fromSettingsFormat(kaos::Settings_ACL_Operation::Settings_ACL_Operation_WRITE), Operation::WRITE);
    ASSERT_EQ(Translator::fromSettingsFormat(kaos::Settings_ACL_Operation::Settings_ACL_Operation_DELETE), Operation::DELETE);
    ASSERT_EQ(Translator::fromSettingsFormat(kaos::Settings_ACL_Operation::Settings_ACL_Operation_RANGE), Operation::RANGE);
    ASSERT_EQ(Translator::fromSettingsFormat(kaos::Settings_ACL_Operation::Settings_ACL_Operation_SETUP), Operation::SETUP);
    ASSERT_EQ(Translator::fromSettingsFormat(kaos::Settings_ACL_Operation::Settings_ACL_Operation_P2POP), Operation::P2POP);
    ASSERT_EQ(Translator::fromSettingsFormat(kaos::Settings_ACL_Operation::Settings_ACL_Operation_GETLOG), Operation::GETLOG);
    ASSERT_EQ(Translator::fromSettingsFormat(kaos::Settings_ACL_Operation::Settings_ACL_Operation_SECURITY), Operation::SECURITY);
//    ASSERT_EQ(Translator::fromSettingsFormat(kaos::Settings_ACL_Operation_Operation_ARRAYSIZE), Operation::INVALID);                                 );
}
/*
    TEST(Translator_Unit_Test, Operation_To_Setting_Format_Test) {

    ASSERT_EQ(Translator::toSettingsFormat(Operation::READ), kaos::Settings_ACL_Operation::Settings_ACL_Operation_READ);
    ASSERT_EQ(Translator::toSettingsFormat(Operation::WRITE), kaos::Settings_ACL_Operation::Settings_ACL_Operation_WRITE);
    ASSERT_EQ(Translator::toSettingsFormat(Operation::DELETE), kaos::Settings_ACL_Operation::Settings_ACL_Operation_DELETE);
    ASSERT_EQ(Translator::toSettingsFormat(Operation::RANGE), kaos::Settings_ACL_Operation::Settings_ACL_Operation_RANGE);
    ASSERT_EQ(Translator::toSettingsFormat(Operation::SETUP), kaos::Settings_ACL_Operation::Settings_ACL_Operation_SETUP);
    ASSERT_EQ(Translator::toSettingsFormat(Operation::P2POP), kaos::Settings_ACL_Operation::Settings_ACL_Operation_P2POP);
    ASSERT_EQ(Translator::toSettingsFormat(Operation::GETLOG), kaos::Settings_ACL_Operation::Settings_ACL_Operation_GETLOG);
    ASSERT_EQ(Translator::toSettingsFormat(Operation::SECURITY), kaos::Settings_ACL_Operation::Settings_ACL_Operation_SECURITY);
    ASSERT_EQ(Translator::toSettingsFormat(static_cast<Operation>(static_cast<uint32_t>(Operation::INVALID) + 1)),
                                           kaos::Settings_ACL_Operation::Settings_ACL_Operation_GETLOG);
    }
*/
int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

