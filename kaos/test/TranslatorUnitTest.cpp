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
#include <string>
#include "gtest/gtest.h"
#include "Translator.hpp"
#include "Kinetic.pb.hpp"
#include "Settings.pb.hpp"

/*
 * Used Namespace Members
 */
using com::seagate::kinetic::proto::Command_Security_ACL_HMACAlgorithm;
using com::seagate::kinetic::proto::Command_Security_ACL_HMACAlgorithm_HmacSHA1;
using com::seagate::kinetic::proto::Command_Security_ACL_Permission;
using com::seagate::kinetic::proto::Command_Algorithm;
using com::seagate::kinetic::proto::Command_PinOperation_PinOpType;
using com::seagate::kinetic::proto::Message_AuthType;
using com::seagate::kinetic::proto::Command_MessageType;
using com::seagate::kinetic::proto::Command_GetLog_Type;
using com::seagate::kinetic::proto::Command_Synchronization;
using com::seagate::kinetic::proto::Command_Status_StatusCode;
using com::seagate::kinetic::proto::Command_Security_ACL_Permission_READ;
using com::seagate::kinetic::proto::Command_Security_ACL_Permission_WRITE;
using com::seagate::kinetic::proto::Command_Security_ACL_Permission_DELETE;
using com::seagate::kinetic::proto::Command_Security_ACL_Permission_RANGE;
using com::seagate::kinetic::proto::Command_Security_ACL_Permission_SETUP;
using com::seagate::kinetic::proto::Command_Security_ACL_Permission_P2POP;
using com::seagate::kinetic::proto::Command_Security_ACL_Permission_GETLOG;
using com::seagate::kinetic::proto::Command_Security_ACL_Permission_SECURITY;
using com::seagate::kinetic::proto::Command_Algorithm_INVALID_ALGORITHM;
using com::seagate::kinetic::proto::Command_Algorithm_SHA1;
using com::seagate::kinetic::proto::Command_Algorithm_SHA2;
using com::seagate::kinetic::proto::Command_Algorithm_SHA3;
using com::seagate::kinetic::proto::Command_Algorithm_CRC32;
using com::seagate::kinetic::proto::Command_Algorithm_CRC64;
using com::seagate::kinetic::proto::Command_PinOperation_PinOpType_UNLOCK_PINOP;
using com::seagate::kinetic::proto::Command_PinOperation_PinOpType_LOCK_PINOP;
using com::seagate::kinetic::proto::Command_PinOperation_PinOpType_ERASE_PINOP;
using com::seagate::kinetic::proto::Command_PinOperation_PinOpType_SECURE_ERASE_PINOP;
using com::seagate::kinetic::proto::Command_PinOperation_PinOpType_INVALID_PINOP;
using com::seagate::kinetic::proto::Command_Security_ACL_HMACAlgorithm_INVALID_HMAC_ALGORITHM;
using com::seagate::kinetic::proto::Message_AuthType_INVALID_AUTH_TYPE;
using com::seagate::kinetic::proto::Message_AuthType_HMACAUTH;
using com::seagate::kinetic::proto::Message_AuthType_PINAUTH;
using com::seagate::kinetic::proto::Message_AuthType_UNSOLICITEDSTATUS;
using com::seagate::kinetic::proto::Command_MessageType_GET;
using com::seagate::kinetic::proto::Command_MessageType_GET_RESPONSE;
using com::seagate::kinetic::proto::Command_MessageType_PUT;
using com::seagate::kinetic::proto::Command_MessageType_PUT_RESPONSE;
using com::seagate::kinetic::proto::Command_MessageType_DELETE;
using com::seagate::kinetic::proto::Command_MessageType_DELETE_RESPONSE;
using com::seagate::kinetic::proto::Command_MessageType_GETNEXT;
using com::seagate::kinetic::proto::Command_MessageType_GETNEXT_RESPONSE;
using com::seagate::kinetic::proto::Command_MessageType_GETPREVIOUS;
using com::seagate::kinetic::proto::Command_MessageType_GETPREVIOUS_RESPONSE;
using com::seagate::kinetic::proto::Command_MessageType_GETKEYRANGE;
using com::seagate::kinetic::proto::Command_MessageType_GETKEYRANGE_RESPONSE;
using com::seagate::kinetic::proto::Command_MessageType_GETVERSION;
using com::seagate::kinetic::proto::Command_MessageType_GETVERSION_RESPONSE;
using com::seagate::kinetic::proto::Command_MessageType_SETUP;
using com::seagate::kinetic::proto::Command_MessageType_SETUP_RESPONSE;
using com::seagate::kinetic::proto::Command_MessageType_GETLOG;
using com::seagate::kinetic::proto::Command_MessageType_GETLOG_RESPONSE;
using com::seagate::kinetic::proto::Command_MessageType_SECURITY;
using com::seagate::kinetic::proto::Command_MessageType_SECURITY_RESPONSE;
using com::seagate::kinetic::proto::Command_MessageType_PEER2PEERPUSH;
using com::seagate::kinetic::proto::Command_MessageType_PEER2PEERPUSH_RESPONSE;
using com::seagate::kinetic::proto::Command_MessageType_NOOP;
using com::seagate::kinetic::proto::Command_MessageType_NOOP_RESPONSE;
using com::seagate::kinetic::proto::Command_MessageType_FLUSHALLDATA;
using com::seagate::kinetic::proto::Command_MessageType_FLUSHALLDATA_RESPONSE;
using com::seagate::kinetic::proto::Command_MessageType_PINOP;
using com::seagate::kinetic::proto::Command_MessageType_PINOP_RESPONSE;
using com::seagate::kinetic::proto::Command_MessageType_MEDIASCAN;
using com::seagate::kinetic::proto::Command_MessageType_MEDIASCAN_RESPONSE;
using com::seagate::kinetic::proto::Command_MessageType_MEDIAOPTIMIZE;
using com::seagate::kinetic::proto::Command_MessageType_MEDIAOPTIMIZE_RESPONSE;
using com::seagate::kinetic::proto::Command_MessageType_START_BATCH;
using com::seagate::kinetic::proto::Command_MessageType_START_BATCH_RESPONSE;
using com::seagate::kinetic::proto::Command_MessageType_END_BATCH;
using com::seagate::kinetic::proto::Command_MessageType_END_BATCH_RESPONSE;
using com::seagate::kinetic::proto::Command_MessageType_ABORT_BATCH;
using com::seagate::kinetic::proto::Command_MessageType_ABORT_BATCH_RESPONSE;
using com::seagate::kinetic::proto::Command_GetLog_Type_UTILIZATIONS;
using com::seagate::kinetic::proto::Command_GetLog_Type_TEMPERATURES;
using com::seagate::kinetic::proto::Command_GetLog_Type_CAPACITIES;
using com::seagate::kinetic::proto::Command_GetLog_Type_CONFIGURATION;
using com::seagate::kinetic::proto::Command_GetLog_Type_STATISTICS;
using com::seagate::kinetic::proto::Command_GetLog_Type_MESSAGES;
using com::seagate::kinetic::proto::Command_GetLog_Type_LIMITS;
using com::seagate::kinetic::proto::Command_GetLog_Type_DEVICE;
using com::seagate::kinetic::proto::Command_Security_ACL_Permission_INVALID_PERMISSION;
using com::seagate::kinetic::proto::Command_Synchronization_WRITETHROUGH;
using com::seagate::kinetic::proto::Command_Synchronization_WRITEBACK;
using com::seagate::kinetic::proto::Command_Synchronization_FLUSH;

TEST(Translator_Unit_Test, Hmac_Algorithm_From_Settings_Format_Test) {
    ASSERT_EQ(kaos::Settings_ACL_HmacAlgorithm_HmacAlgorithm_ARRAYSIZE, 2);
    ASSERT_EQ(Translator::fromSettingsFormat(kaos::Settings_ACL_HmacAlgorithm_HMAC_SHA1), HmacAlgorithm::SHA1);
    ASSERT_EQ(Translator::fromSettingsFormat(kaos::Settings_ACL_HmacAlgorithm_HMAC_INVALID), HmacAlgorithm::UNKNOWN);
    kaos::Settings_ACL_HmacAlgorithm unknownAlgorithm = static_cast<kaos::Settings_ACL_HmacAlgorithm>(100);
    ASSERT_EQ(Translator::fromSettingsFormat(unknownAlgorithm),HmacAlgorithm::UNKNOWN);
}

TEST(Translator_Unit_Test, Hmac_Algorithm_To_Settings_Format_Test) {
    ASSERT_EQ(Translator::toSettingsFormat(HmacAlgorithm::SHA1), kaos::Settings_ACL_HmacAlgorithm_HMAC_SHA1);
    ASSERT_EQ(Translator::toSettingsFormat(HmacAlgorithm::UNKNOWN), kaos::Settings_ACL_HmacAlgorithm_HMAC_INVALID);
    ASSERT_EQ(Translator::toSettingsFormat(static_cast<HmacAlgorithm>(101)), kaos::Settings_ACL_HmacAlgorithm_HMAC_INVALID);
}

TEST(Translator_Unit_Test, Hmac_Algorithm_From_Message_Format_Test) {
    ASSERT_EQ(Translator::fromMessageFormat(Command_Security_ACL_HMACAlgorithm_HmacSHA1), HmacAlgorithm::SHA1);
    ASSERT_EQ(Translator::fromMessageFormat(static_cast<Command_Security_ACL_HMACAlgorithm>(102)), HmacAlgorithm::UNKNOWN);
}

TEST(Translator_Unit_Test, Operation_From_Setting_Format_Test) {
    ASSERT_EQ(Translator::fromSettingsFormat(kaos::Settings_ACL_Operation::Settings_ACL_Operation_READ), Operation::READ);
    ASSERT_EQ(Translator::fromSettingsFormat(kaos::Settings_ACL_Operation::Settings_ACL_Operation_WRITE), Operation::WRITE);
    ASSERT_EQ(Translator::fromSettingsFormat(kaos::Settings_ACL_Operation::Settings_ACL_Operation_DELETE), Operation::DELETE);
    ASSERT_EQ(Translator::fromSettingsFormat(kaos::Settings_ACL_Operation::Settings_ACL_Operation_RANGE), Operation::RANGE);
    ASSERT_EQ(Translator::fromSettingsFormat(kaos::Settings_ACL_Operation::Settings_ACL_Operation_SETUP), Operation::SETUP);
    ASSERT_EQ(Translator::fromSettingsFormat(kaos::Settings_ACL_Operation::Settings_ACL_Operation_P2POP), Operation::P2POP);
    ASSERT_EQ(Translator::fromSettingsFormat(kaos::Settings_ACL_Operation::Settings_ACL_Operation_GETLOG), Operation::GETLOG);
    ASSERT_EQ(Translator::fromSettingsFormat(kaos::Settings_ACL_Operation::Settings_ACL_Operation_SECURITY), Operation::SECURITY);
    ASSERT_EQ(Translator::fromSettingsFormat(static_cast<kaos::Settings_ACL_Operation>(103)), Operation::INVALID);
}

TEST(Translator_Unit_Test, Operation_To_Setting_Format_Test) {
    ASSERT_EQ(Translator::toSettingsFormat(Operation::READ), kaos::Settings_ACL_Operation::Settings_ACL_Operation_READ);
    ASSERT_EQ(Translator::toSettingsFormat(Operation::WRITE), kaos::Settings_ACL_Operation::Settings_ACL_Operation_WRITE);
    ASSERT_EQ(Translator::toSettingsFormat(Operation::DELETE), kaos::Settings_ACL_Operation::Settings_ACL_Operation_DELETE);
    ASSERT_EQ(Translator::toSettingsFormat(Operation::RANGE), kaos::Settings_ACL_Operation::Settings_ACL_Operation_RANGE);
    ASSERT_EQ(Translator::toSettingsFormat(Operation::SETUP), kaos::Settings_ACL_Operation::Settings_ACL_Operation_SETUP);
    ASSERT_EQ(Translator::toSettingsFormat(Operation::P2POP), kaos::Settings_ACL_Operation::Settings_ACL_Operation_P2POP);
    ASSERT_EQ(Translator::toSettingsFormat(Operation::GETLOG), kaos::Settings_ACL_Operation::Settings_ACL_Operation_GETLOG);
    ASSERT_EQ(Translator::toSettingsFormat(Operation::SECURITY), kaos::Settings_ACL_Operation::Settings_ACL_Operation_SECURITY);
    ASSERT_EQ(Translator::toSettingsFormat(static_cast<Operation>(104)), kaos::Settings_ACL_Operation::Settings_ACL_Operation_GETLOG);
}

TEST(Translator_Unit_Test, Operation_From_Message_Format_Test) {
    ASSERT_EQ(Translator::fromMessageFormat(Command_Security_ACL_Permission_READ), Operation::READ);
    ASSERT_EQ(Translator::fromMessageFormat(Command_Security_ACL_Permission_WRITE), Operation::WRITE);
    ASSERT_EQ(Translator::fromMessageFormat(Command_Security_ACL_Permission_DELETE), Operation::DELETE);
    ASSERT_EQ(Translator::fromMessageFormat(Command_Security_ACL_Permission_RANGE), Operation::RANGE);
    ASSERT_EQ(Translator::fromMessageFormat(Command_Security_ACL_Permission_SETUP), Operation::SETUP);
    ASSERT_EQ(Translator::fromMessageFormat(Command_Security_ACL_Permission_GETLOG), Operation::GETLOG);
    ASSERT_EQ(Translator::fromMessageFormat(Command_Security_ACL_Permission_SECURITY), Operation::SECURITY);
    ASSERT_EQ(Translator::fromMessageFormat(static_cast<Command_Security_ACL_Permission>(105)), Operation::INVALID);
}

TEST(Translator_Unit_Test, Bool_To_String_Test) {
    ASSERT_STREQ(Translator::toString(true).c_str(), "True");
    ASSERT_STREQ(Translator::toString(false).c_str(), "False");
}

TEST(Translator_Unit_Test, Algorithm_To_String_Test) {
    ASSERT_STREQ(Translator::toString(Command_Algorithm_INVALID_ALGORITHM).c_str(), "Invalid");
    ASSERT_STREQ(Translator::toString(Command_Algorithm_SHA1).c_str(), "SHA1");
    ASSERT_STREQ(Translator::toString(Command_Algorithm_SHA2).c_str(), "SHA2");
    ASSERT_STREQ(Translator::toString(Command_Algorithm_SHA3).c_str(), "SHA3");
    ASSERT_STREQ(Translator::toString(Command_Algorithm_CRC32).c_str(), "CRC32");
    ASSERT_STREQ(Translator::toString(Command_Algorithm_CRC64).c_str(), "CRC64");
    ASSERT_STREQ(Translator::toString(static_cast<Command_Algorithm>(106)).c_str(), "Unknown (106)");
}

TEST(Translator_Unit_Test, Pin_Op_Type_To_String_Test) {
    ASSERT_STREQ(Translator::toString(Command_PinOperation_PinOpType_UNLOCK_PINOP).c_str(), "Unlock");
    ASSERT_STREQ(Translator::toString(Command_PinOperation_PinOpType_LOCK_PINOP).c_str(), "Lock");
    ASSERT_STREQ(Translator::toString(Command_PinOperation_PinOpType_ERASE_PINOP).c_str(), "Erase");
    ASSERT_STREQ(Translator::toString(Command_PinOperation_PinOpType_SECURE_ERASE_PINOP).c_str(), "Secure Erase");
    ASSERT_STREQ(Translator::toString(Command_PinOperation_PinOpType_INVALID_PINOP).c_str(), "Invalid");
    ASSERT_STREQ(Translator::toString(static_cast<Command_PinOperation_PinOpType>(107)).c_str(), "Unknown (107)");
}

TEST(Translator_Unit_Test, Hmac_Algorithm_To_String_Test) {
    ASSERT_STREQ(Translator::toString(Command_Security_ACL_HMACAlgorithm_INVALID_HMAC_ALGORITHM).c_str(), "Invalid");
    ASSERT_STREQ(Translator::toString(Command_Security_ACL_HMACAlgorithm_HmacSHA1).c_str(), "HMAC-SHA1");
    ASSERT_STREQ(Translator::toString(static_cast<Command_Security_ACL_HMACAlgorithm>(108)).c_str(), "Unknown (108)");
}

TEST(Translator_Unit_Test, Message_AuthType_To_String_Test) {
    ASSERT_STREQ(Translator::toString(Message_AuthType_INVALID_AUTH_TYPE).c_str(), "Invalid");
    ASSERT_STREQ(Translator::toString(Message_AuthType_HMACAUTH).c_str(), "HMAC Authentication");
    ASSERT_STREQ(Translator::toString(Message_AuthType_PINAUTH).c_str(), "PIN Authentication");
    ASSERT_STREQ(Translator::toString(Message_AuthType_UNSOLICITEDSTATUS).c_str(), "Unsolicited Status");
    ASSERT_STREQ(Translator::toString(static_cast<Message_AuthType>(109)).c_str(), "Unknown (109)");
}

TEST(Translator_Unit_Test, Message_Type_To_String_Test) {
    ASSERT_STREQ(Translator::toString(Command_MessageType_GET).c_str(), "Get");
    ASSERT_STREQ(Translator::toString(Command_MessageType_GET_RESPONSE).c_str(), "Get Response");
    ASSERT_STREQ(Translator::toString(Command_MessageType_PUT).c_str(), "Put");
    ASSERT_STREQ(Translator::toString(Command_MessageType_PUT_RESPONSE).c_str(), "Put Response");
    ASSERT_STREQ(Translator::toString(Command_MessageType_DELETE).c_str(), "Delete");
    ASSERT_STREQ(Translator::toString(Command_MessageType_DELETE_RESPONSE).c_str(), "Delete Response");
    ASSERT_STREQ(Translator::toString(Command_MessageType_GETNEXT).c_str(), "Get Next");
    ASSERT_STREQ(Translator::toString(Command_MessageType_GETNEXT_RESPONSE).c_str(), "Get Next Response");
    ASSERT_STREQ(Translator::toString(Command_MessageType_GETPREVIOUS).c_str(), "Get Previous");
    ASSERT_STREQ(Translator::toString(Command_MessageType_GETPREVIOUS_RESPONSE).c_str(), "Get Previous Response");
    ASSERT_STREQ(Translator::toString(Command_MessageType_GETKEYRANGE).c_str(), "Get Key Range");
    ASSERT_STREQ(Translator::toString(Command_MessageType_GETKEYRANGE_RESPONSE).c_str(), "Get Key Range Response");
    ASSERT_STREQ(Translator::toString(Command_MessageType_GETVERSION).c_str(), "Get Version");
    ASSERT_STREQ(Translator::toString(Command_MessageType_GETVERSION_RESPONSE).c_str(), "Get Version Response");
    ASSERT_STREQ(Translator::toString(Command_MessageType_SETUP).c_str(), "Setup");
    ASSERT_STREQ(Translator::toString(Command_MessageType_SETUP_RESPONSE).c_str(), "Setup Response");
    ASSERT_STREQ(Translator::toString(Command_MessageType_GETLOG).c_str(), "Get Log");
    ASSERT_STREQ(Translator::toString(Command_MessageType_GETLOG_RESPONSE).c_str(), "Get Log Response");
    ASSERT_STREQ(Translator::toString(Command_MessageType_SECURITY).c_str(), "Security");
    ASSERT_STREQ(Translator::toString(Command_MessageType_SECURITY_RESPONSE).c_str(), "Security Response");
    ASSERT_STREQ(Translator::toString(Command_MessageType_PEER2PEERPUSH).c_str(), "Peer-to-Peer Push");
    ASSERT_STREQ(Translator::toString(Command_MessageType_PEER2PEERPUSH_RESPONSE).c_str(), "Peer-to-Peer Push Response");
    ASSERT_STREQ(Translator::toString(Command_MessageType_NOOP).c_str(), "No-Op");
    ASSERT_STREQ(Translator::toString(Command_MessageType_NOOP_RESPONSE).c_str(), "No-Op Response");
    ASSERT_STREQ(Translator::toString(Command_MessageType_FLUSHALLDATA).c_str(), "Flush All Data");
    ASSERT_STREQ(Translator::toString(Command_MessageType_FLUSHALLDATA_RESPONSE).c_str(), "Flush All Data Response");
    ASSERT_STREQ(Translator::toString(Command_MessageType_PINOP).c_str(), "PIN-Op");
    ASSERT_STREQ(Translator::toString(Command_MessageType_PINOP_RESPONSE).c_str(), "PIN-Op Response");
    ASSERT_STREQ(Translator::toString(Command_MessageType_MEDIASCAN).c_str(), "Media Scan");
    ASSERT_STREQ(Translator::toString(Command_MessageType_MEDIASCAN_RESPONSE).c_str(), "Media Scan Response");
    ASSERT_STREQ(Translator::toString(Command_MessageType_MEDIAOPTIMIZE).c_str(), "Media Optimize");
    ASSERT_STREQ(Translator::toString(Command_MessageType_MEDIAOPTIMIZE_RESPONSE).c_str(), "Media Optimize Response");
    ASSERT_STREQ(Translator::toString(Command_MessageType_START_BATCH).c_str(), "Start Batch");
    ASSERT_STREQ(Translator::toString(Command_MessageType_START_BATCH_RESPONSE).c_str(), "Start Batch Response");
    ASSERT_STREQ(Translator::toString(Command_MessageType_END_BATCH).c_str(), "End Batch");
    ASSERT_STREQ(Translator::toString(Command_MessageType_END_BATCH_RESPONSE).c_str(), "End Batch Response");
    ASSERT_STREQ(Translator::toString(Command_MessageType_ABORT_BATCH).c_str(), "Abort Batch");
    ASSERT_STREQ(Translator::toString(Command_MessageType_ABORT_BATCH_RESPONSE).c_str(), "Abort Batch Response");
    ASSERT_STREQ(Translator::toString(static_cast<Command_MessageType>(110)).c_str(), "Unknown (110)");
}

TEST(Translator_Unit_Test, Command_GetLog_Type_To_String_Test) {
    ASSERT_STREQ(Translator::toString(Command_GetLog_Type_UTILIZATIONS).c_str(), "Utilizations");
    ASSERT_STREQ(Translator::toString(Command_GetLog_Type_TEMPERATURES).c_str(), "Temperatures");
    ASSERT_STREQ(Translator::toString(Command_GetLog_Type_CAPACITIES).c_str(), "Capacities");
    ASSERT_STREQ(Translator::toString(Command_GetLog_Type_CONFIGURATION).c_str(), "Configuration");
    ASSERT_STREQ(Translator::toString(Command_GetLog_Type_STATISTICS).c_str(), "Statistics");
    ASSERT_STREQ(Translator::toString(Command_GetLog_Type_MESSAGES).c_str(), "Messages");
    ASSERT_STREQ(Translator::toString(Command_GetLog_Type_LIMITS).c_str(), "Limits");
    ASSERT_STREQ(Translator::toString(Command_GetLog_Type_DEVICE).c_str(), "Device");
    ASSERT_STREQ(Translator::toString(static_cast<Command_GetLog_Type>(111)).c_str(), "Unknown (111)");
}

TEST(Translator_Unit_Test, Command_Security_ACL_Permission_To_String_Test) {
    ASSERT_STREQ(Translator::toString(Command_Security_ACL_Permission_READ).c_str(), "Read");
    ASSERT_STREQ(Translator::toString(Command_Security_ACL_Permission_WRITE).c_str(), "Write");
    ASSERT_STREQ(Translator::toString(Command_Security_ACL_Permission_DELETE).c_str(), "Delete");
    ASSERT_STREQ(Translator::toString(Command_Security_ACL_Permission_RANGE).c_str(), "Range");
    ASSERT_STREQ(Translator::toString(Command_Security_ACL_Permission_SETUP).c_str(), "Setup");
    ASSERT_STREQ(Translator::toString(Command_Security_ACL_Permission_P2POP).c_str(), "Peer-to-Peer Operation");
    ASSERT_STREQ(Translator::toString(Command_Security_ACL_Permission_GETLOG).c_str(), "Get Log");
    ASSERT_STREQ(Translator::toString(Command_Security_ACL_Permission_SECURITY).c_str(), "Security");
    ASSERT_STREQ(Translator::toString(Command_Security_ACL_Permission_INVALID_PERMISSION).c_str(), "Invalid");
    ASSERT_STREQ(Translator::toString(static_cast<Command_Security_ACL_Permission>(112)).c_str(), "Unknown (112)");
}

TEST(Translator_Unit_Test, Command_Synchronization_To_String_Test) {
    ASSERT_STREQ(Translator::toString(Command_Synchronization_WRITETHROUGH).c_str(), "Write-Through");
    ASSERT_STREQ(Translator::toString(Command_Synchronization_WRITEBACK).c_str(), "Write-Back");
    ASSERT_STREQ(Translator::toString(Command_Synchronization_FLUSH).c_str(), "Flush");
    ASSERT_STREQ(Translator::toString(static_cast<Command_Synchronization>(113)).c_str(), "Unknown (113)");
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

