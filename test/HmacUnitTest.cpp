/*
 * Copyright (c) 2014-2016 Western Digital Corporation or its affiliates <copyrightagent@wdc.com>
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
#include <iomanip>
#include "gtest/gtest.h"
#include "Hmac.hpp"

/*
 * Used Namespaces
 */
using std::string;

/*
 * Each test checks for the proper HMAC generation and then the Kinetic HMAC generation (which
 * prepends the data size to the data being hashed).
 */

TEST(HMAC_Unit_Test, Empty_Test) {
    string data("");
    string key("");
    string expectedResult("\xfb\xdb\x1d\x1b\x18\xaa\x6c\x08\x32\x4b\x7d\x64\xb7\x1f\xb7\x63\x70\x69\x0e\x1d");

    string result = Hmac::compute(data, key, HmacAlgorithm::SHA1, HMAC_DO_NOT_PREPEND_SIZE);
    ASSERT_EQ(result.compare(expectedResult), 0);

    result = Hmac::compute(data, key, HmacAlgorithm::SHA1, HMAC_PREPEND_SIZE);
    ASSERT_EQ(result.compare(expectedResult), 0);
}

TEST(HMAC_Unit_Test, Wikipedia_Test) {
    string data("The quick brown fox jumps over the lazy dog");
    string key("key");
    string expectedResult("\xde\x7c\x9b\x85\xb8\xb7\x8a\xa6\xbc\x8a\x7a\x36\xf7\x0a\x90\x70\x1c\x9d\xb4\xd9");
    string expectedResultWithSize("\x19\x06\xb6\x42\x48\x4a\x80\xda\x0a\x3e\xe8\xac\xbb\x18\x93\x4c\x36\x8f\xc3\x8a");

    string result = Hmac::compute(data, key, HmacAlgorithm::SHA1, HMAC_DO_NOT_PREPEND_SIZE);
    ASSERT_EQ(result.compare(expectedResult), 0);

    result = Hmac::compute(data, key, HmacAlgorithm::SHA1, HMAC_PREPEND_SIZE);
    ASSERT_EQ(result.compare(expectedResultWithSize), 0);
}

TEST(HMAC_Unit_Test, RFC_2202_Test_Case_1) {
    string data("Hi There");
    string key(20, '\x0b');
    string expectedResult("\xb6\x17\x31\x86\x55\x05\x72\x64\xe2\x8b\xc0\xb6\xfb\x37\x8c\x8e\xf1\x46\xbe\x00", 20);
    string expectedResultWithSize("\xde\x19\xc6\x3f\xcf\x76\x6f\x62\xf9\x0e\x72\xff\x5c\xe0\xe8\xff\x79\x04\x18\xb5");

    string result = Hmac::compute(data, key, HmacAlgorithm::SHA1, HMAC_DO_NOT_PREPEND_SIZE);
    ASSERT_EQ(result.compare(expectedResult), 0);

    result = Hmac::compute(data, key, HmacAlgorithm::SHA1, HMAC_PREPEND_SIZE);
    ASSERT_EQ(result.compare(expectedResultWithSize), 0);
}

TEST(HMAC_Unit_Test, RFC_2202_Test_Case_2) {
    string data("what do ya want for nothing?");
    string key("Jefe");
    string expectedResult("\xef\xfc\xdf\x6a\xe5\xeb\x2f\xa2\xd2\x74\x16\xd5\xf1\x84\xdf\x9c\x25\x9a\x7c\x79");
    string expectedResultWithSize("\xbf\xb2\xa7\x49\xd2\x04\x6b\x0f\xf0\x98\x49\x7a\x39\x7d\x45\xd6\x3c\xe7\xff\x5b");

    string result = Hmac::compute(data, key, HmacAlgorithm::SHA1, HMAC_DO_NOT_PREPEND_SIZE);
    ASSERT_EQ(result.compare(expectedResult), 0);

    result = Hmac::compute(data, key, HmacAlgorithm::SHA1, HMAC_PREPEND_SIZE);
    ASSERT_EQ(result.compare(expectedResultWithSize), 0);
}

TEST(HMAC_Unit_Test, RFC_2202_Test_Case_3) {
    string data(50, '\xdd');
    string key(20, '\xaa');
    string expectedResult("\x12\x5d\x73\x42\xb9\xac\x11\xcd\x91\xa3\x9a\xf4\x8a\xa1\x7b\x4f\x63\xf1\x75\xd3");
    string expectedResultWithSize("\x2f\xc4\xf5\xf5\x9e\xc8\x12\x42\xd1\xbd\x10\xe7\x91\x64\xaf\xd0\x1e\x3b\x9e\x49");

    string result = Hmac::compute(data, key, HmacAlgorithm::SHA1, HMAC_DO_NOT_PREPEND_SIZE);
    ASSERT_EQ(result.compare(expectedResult), 0);

    result = Hmac::compute(data, key, HmacAlgorithm::SHA1, HMAC_PREPEND_SIZE);
    ASSERT_EQ(result.compare(expectedResultWithSize), 0);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

