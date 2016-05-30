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
#include <iomanip>
#include "gtest/gtest.h"
#include "KineticMessageFraming.hpp"

TEST(Kinetic_Message_Framing_Unit_Test, Message_Framing_Size_Test) {
    ASSERT_EQ(sizeof(KineticMessageFraming), 9U);
}

TEST(Kinetic_Message_Framing_Unit_Test, Message_Framing_Magic_Number_Test) {
    ASSERT_EQ(KINETIC_MESSAGE_FRAMING_MAGIC_NUMBER, 0x46);
}

TEST(Kinetic_Message_Framing_Unit_Test, Default_Constructor_Test) {
    KineticMessageFraming messageFraming;
    ASSERT_EQ(messageFraming.magicNumber(), 0U);
    ASSERT_EQ(messageFraming.messageSize(), 0U);
    ASSERT_EQ(messageFraming.valueSize(), 0U);
}

TEST(Kinetic_Message_Framing_Unit_Test, Constructor_Single_Bit_Init_Test) {
    for (uint32_t shift = 0; shift < 8; shift++) {
        uint32_t value = 1 << shift;
        KineticMessageFraming messageFraming(value, 0, 0);
        ASSERT_EQ(messageFraming.magicNumber(), value);
        ASSERT_EQ(messageFraming.messageSize(), 0U);
        ASSERT_EQ(messageFraming.valueSize(), 0U);
    }

    for (uint32_t shift = 0; shift < 32; shift++) {
        uint32_t value = 1 << shift;
        KineticMessageFraming messageFraming(0, value, 0);
        ASSERT_EQ(messageFraming.magicNumber(), 0U);
        ASSERT_EQ(messageFraming.messageSize(), value);
        ASSERT_EQ(messageFraming.valueSize(), 0U);
    }
    for (uint32_t shift = 0; shift < 32; shift++) {
        uint32_t value = 1 << shift;
        KineticMessageFraming messageFraming(0, 0, value);
        ASSERT_EQ(messageFraming.magicNumber(), 0U);
        ASSERT_EQ(messageFraming.messageSize(), 0U);
        ASSERT_EQ(messageFraming.valueSize(), value);
    }
}

TEST(Kinetic_Message_Framing_Unit_Test, Constructor_Multi_Bit_Init_Test) {
    uint32_t value = 0;
    for (uint32_t shift = 0; shift < 8; shift++) {
        value |= 1 << shift;
        KineticMessageFraming messageFraming(value, 0, 0);
        ASSERT_EQ(messageFraming.magicNumber(), value);
        ASSERT_EQ(messageFraming.messageSize(), 0U);
        ASSERT_EQ(messageFraming.valueSize(), 0U);
    }
    value = 0;
    for (uint32_t shift = 0; shift < 32; shift++) {
        value |= 1 << shift;
        KineticMessageFraming messageFraming(0, value, 0);
        ASSERT_EQ(messageFraming.magicNumber(), 0U);
        ASSERT_EQ(messageFraming.messageSize(), value);
        ASSERT_EQ(messageFraming.valueSize(), 0U);
    }
    value = 0;
    for (uint32_t shift = 0; shift < 32; shift++) {
        value |= 1 << shift;
        KineticMessageFraming messageFraming(0, 0, value);
        ASSERT_EQ(messageFraming.magicNumber(), 0U);
        ASSERT_EQ(messageFraming.messageSize(), 0U);
        ASSERT_EQ(messageFraming.valueSize(), value);
    }
}

TEST(Kinetic_Message_Framing_Unit_Test, Constructor_Endian_Conversion_Test) {
    KineticMessageFraming messageFraming(KINETIC_MESSAGE_FRAMING_MAGIC_NUMBER, 0xfedcba98U, 0x76543210U);
    uint8_t* messageBuffer = reinterpret_cast<uint8_t*>(&messageFraming);

    ASSERT_EQ(messageBuffer[0], KINETIC_MESSAGE_FRAMING_MAGIC_NUMBER);
    ASSERT_EQ(messageBuffer[1], 0xfeU);
    ASSERT_EQ(messageBuffer[2], 0xdcU);
    ASSERT_EQ(messageBuffer[3], 0xbaU);
    ASSERT_EQ(messageBuffer[4], 0x98U);
    ASSERT_EQ(messageBuffer[5], 0x76U);
    ASSERT_EQ(messageBuffer[6], 0x54U);
    ASSERT_EQ(messageBuffer[7], 0x32U);
    ASSERT_EQ(messageBuffer[8], 0x10U);
}

TEST(Kinetic_Message_Framing_Unit_Test, Set_Get_Single_Bit_Test) {
    for (uint32_t shift = 0; shift < 8; shift++) {
        uint32_t value = 1 << shift;
        KineticMessageFraming messageFraming;
        messageFraming.setMagicNumber(value);
        ASSERT_EQ(messageFraming.magicNumber(), value);
        ASSERT_EQ(messageFraming.messageSize(), 0U);
        ASSERT_EQ(messageFraming.valueSize(), 0U);
    }
    for (uint32_t shift = 0; shift < 32; shift++) {
        uint32_t value = 1 << shift;
        KineticMessageFraming messageFraming;
        messageFraming.setMessageSize(value);
        ASSERT_EQ(messageFraming.magicNumber(), 0U);
        ASSERT_EQ(messageFraming.messageSize(), value);
        ASSERT_EQ(messageFraming.valueSize(), 0U);
    }
    for (uint32_t shift = 0; shift < 32; shift++) {
        uint32_t value = 1 << shift;
        KineticMessageFraming messageFraming;
        messageFraming.setValueSize(value);
        ASSERT_EQ(messageFraming.magicNumber(), 0U);
        ASSERT_EQ(messageFraming.messageSize(), 0U);
        ASSERT_EQ(messageFraming.valueSize(), value);
    }
}

TEST(Kinetic_Message_Framing_Unit_Test, Set_Get_Multi_Bit_Test) {
    uint32_t value = 0;
    for (uint32_t shift = 0; shift < 8; shift++) {
        value |= 1 << shift;
        KineticMessageFraming messageFraming;
        messageFraming.setMagicNumber(value);
        ASSERT_EQ(messageFraming.magicNumber(), value);
        ASSERT_EQ(messageFraming.messageSize(), 0U);
        ASSERT_EQ(messageFraming.valueSize(), 0U);
    }
    value = 0;
    for (uint32_t shift = 0; shift < 32; shift++) {
        value |= 1 << shift;
        KineticMessageFraming messageFraming;
        messageFraming.setMessageSize(value);
        ASSERT_EQ(messageFraming.magicNumber(), 0U);
        ASSERT_EQ(messageFraming.messageSize(), value);
        ASSERT_EQ(messageFraming.valueSize(), 0U);
    }
    value = 0;
    for (uint32_t shift = 0; shift < 32; shift++) {
        value |= 1 << shift;
        KineticMessageFraming messageFraming;
        messageFraming.setValueSize(value);
        ASSERT_EQ(messageFraming.magicNumber(), 0U);
        ASSERT_EQ(messageFraming.messageSize(), 0U);
        ASSERT_EQ(messageFraming.valueSize(), value);
    }
}

TEST(Kinetic_Message_Framing_Unit_Test, Get_Endian_Conversion_Test) {
    uint8_t messageBuffer[sizeof(KineticMessageFraming)] = { KINETIC_MESSAGE_FRAMING_MAGIC_NUMBER, 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef};

    KineticMessageFraming* messageFraming = reinterpret_cast<KineticMessageFraming*>(messageBuffer);
    ASSERT_EQ(messageFraming->magicNumber(), KINETIC_MESSAGE_FRAMING_MAGIC_NUMBER);
    ASSERT_EQ(messageFraming->messageSize(), 0x01234567U);
    ASSERT_EQ(messageFraming->valueSize(), 0x89abcdefU);
}

TEST(Kinetic_Message_Framing_Unit_Test, Put_Endian_Conversion_Test) {
    KineticMessageFraming messageFraming;
    messageFraming.setMagicNumber(KINETIC_MESSAGE_FRAMING_MAGIC_NUMBER);
    messageFraming.setMessageSize(0xfedcba98U);
    messageFraming.setValueSize(0x76543210U);

    uint8_t* messageBuffer = reinterpret_cast<uint8_t*>(&messageFraming);

    ASSERT_EQ(messageBuffer[0], KINETIC_MESSAGE_FRAMING_MAGIC_NUMBER);
    ASSERT_EQ(messageBuffer[1], 0xfeU);
    ASSERT_EQ(messageBuffer[2], 0xdcU);
    ASSERT_EQ(messageBuffer[3], 0xbaU);
    ASSERT_EQ(messageBuffer[4], 0x98U);
    ASSERT_EQ(messageBuffer[5], 0x76U);
    ASSERT_EQ(messageBuffer[6], 0x54U);
    ASSERT_EQ(messageBuffer[7], 0x32U);
    ASSERT_EQ(messageBuffer[8], 0x10U);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

