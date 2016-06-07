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
#include <vector>
#include "gtest/gtest.h"
#include "Logger.hpp"
#include "Kinetic.pb.hpp"
#include "AccessScope.hpp"
#include "GlobalConfig.hpp"

/*
 * Used Namespace Members
 */
using com::seagate::kinetic::proto::Command_Security_ACL_HMACAlgorithm;
using com::seagate::kinetic::proto::Command_Security_ACL_HMACAlgorithm_HmacSHA1;
using com::seagate::kinetic::proto::Command_Security_ACL_Permission;
using com::seagate::kinetic::proto::Command_Security_ACL_Permission_READ;
using com::seagate::kinetic::proto::Command_Security_ACL_Permission_WRITE;
using com::seagate::kinetic::proto::Command_Security_ACL_Permission_DELETE;
using com::seagate::kinetic::proto::Command_Security_ACL_Permission_RANGE;
using com::seagate::kinetic::proto::Command_Security_ACL_Permission_SETUP;
using com::seagate::kinetic::proto::Command_Security_ACL_Permission_P2POP;
using com::seagate::kinetic::proto::Command_Security_ACL_Permission_GETLOG;
using com::seagate::kinetic::proto::Command_Security_ACL_Permission_SECURITY;

/*
 * Global Variables
 */
GlobalConfig globalConfig;
LogControl logControl;

/**
 * Create Large String
 *
 * @return a string with the maximum key size
 */
std::string createLargeString() {
    uint32_t stringSize = globalConfig.maxKeySize();
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
std::string createBinaryString() {
    std::string binaryString;
    for (uint32_t index = 0; index < 0x100; index++)
        binaryString += index;

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
 * Tests the HMAC format conversion.
 */
TEST(Access_Scope_Unit_Test, Hmac_Algorithm_From_Message_Format_Test) {
    ASSERT_EQ(AccessScope::fromMessageFormat(Command_Security_ACL_HMACAlgorithm_HmacSHA1), HmacAlgorithm::SHA1);
    ASSERT_EQ(AccessScope::fromMessageFormat(static_cast<Command_Security_ACL_HMACAlgorithm>(102)), HmacAlgorithm::UNKNOWN);
}

/**
 * Tests the Operation format conversion.
 */
TEST(Access_Scope_Unit_Test, Operation_From_Message_Format_Test) {
    ASSERT_EQ(AccessScope::fromMessageFormat(Command_Security_ACL_Permission_READ), Operation::READ);
    ASSERT_EQ(AccessScope::fromMessageFormat(Command_Security_ACL_Permission_WRITE), Operation::WRITE);
    ASSERT_EQ(AccessScope::fromMessageFormat(Command_Security_ACL_Permission_DELETE), Operation::DELETE);
    ASSERT_EQ(AccessScope::fromMessageFormat(Command_Security_ACL_Permission_RANGE), Operation::RANGE);
    ASSERT_EQ(AccessScope::fromMessageFormat(Command_Security_ACL_Permission_SETUP), Operation::SETUP);
    ASSERT_EQ(AccessScope::fromMessageFormat(Command_Security_ACL_Permission_GETLOG), Operation::GETLOG);
    ASSERT_EQ(AccessScope::fromMessageFormat(Command_Security_ACL_Permission_SECURITY), Operation::SECURITY);
    ASSERT_EQ(AccessScope::fromMessageFormat(static_cast<Command_Security_ACL_Permission>(105)), Operation::INVALID);
}

/**
 * Tests that the AccessScope object is correctly initialized when created with a varity of
 * parameters and that the getter functions work correctly.
 */
TEST(Access_Scope_Unit_Test, Core_Functionality_Test) {
    std::vector<bool> tlsRequiredArray = {false, true};
    std::vector<std::string> keySubstringArray = {"", "0", createBinaryString(), createLargeString()};
    std::vector<size_t> keySubstringOffsetArray = {0, 1, globalConfig.maxKeySize() / 4, globalConfig.maxKeySize() - 1};

    /*
     * Create an AccessScope object for all the different combination of parameters.
     */
    for (uint32_t tlsRequiredIndex = 0; tlsRequiredIndex < tlsRequiredArray.size(); ++tlsRequiredIndex) {
        bool tlsRequired = tlsRequiredArray[tlsRequiredIndex];
        for (uint32_t keySubstringIndex = 0; keySubstringIndex < keySubstringArray.size(); ++keySubstringIndex) {
            std::string keySubstring = keySubstringArray[keySubstringIndex];
            for (uint32_t keySubstringOffsetIndex = 0; keySubstringOffsetIndex < keySubstringOffsetArray.size(); ++keySubstringOffsetIndex) {
                uint32_t keySubstringOffset = keySubstringOffsetArray[keySubstringOffsetIndex];
                for (uint32_t patternCount = 0; patternCount < ((1 << NUMBER_OF_OPERATIONS) - 1); ++patternCount) {
                    OperationSizedBoolArray operationArray = createOperationArray(patternCount);
                    AccessScope accessScope(tlsRequired, keySubstring, keySubstringOffset, operationArray);

                    /*
                     * If non-zero offset is not valid if the key substring is not specified.  The
                     * AccessScope class will set the offset to zero so we must do the same thing
                     * before comparing expected values.
                     */
                    if (keySubstring.size() == 0)
                        keySubstringOffset = 0;

                    ASSERT_EQ(accessScope.tlsRequired(), tlsRequired);
                    ASSERT_STREQ(accessScope.keySubstring().c_str(), keySubstring.c_str());
                    ASSERT_EQ(accessScope.keySubstringOffset(), keySubstringOffset);
                    ASSERT_EQ(accessScope.minimumKeySize(), keySubstring.size() + keySubstringOffset);
                    for (uint32_t operation = 0; operation < NUMBER_OF_OPERATIONS; ++operation)
                        ASSERT_EQ(accessScope.operationPermitted(UINT32_TO_OPERATION(operation)), operationArray[operation]);
                }
            }
        }
    }
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

