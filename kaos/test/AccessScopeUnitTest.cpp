/*
 * Copyright (c) [2014 - 2016] Western Digital Technologies, Inc. All rights reserved.
 */

/*
 * Include Files
 */
#include <stdint.h>
#include <string>
#include <vector>
#include "gtest/gtest.h"
#include "AccessScope.hpp"
#include "SystemConfig.hpp"

SystemConfig systemConfig;

/**
 * Create Large String
 *
 * @return a string with the maximum key size
 */
std::string createLargeString() {

    uint32_t stringSize = systemConfig.maxKeySize();
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
 * Core Functionality Test
 *
 * Tests that the AccessScope object is correctly initialized when created with a varity of
 * parameters and that the getter functions work correctly.
 */
TEST(Access_Scope_Unit_Test, Core_Functionality_Test) {

    std::vector<bool> tlsRequiredArray = {false, true};
    std::vector<std::string> keySubstringArray = {"", "0", createBinaryString(), createLargeString()};
    std::vector<size_t> keySubstringOffsetArray = {0, 1, systemConfig.maxKeySize() / 4, systemConfig.maxKeySize() - 1};

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

