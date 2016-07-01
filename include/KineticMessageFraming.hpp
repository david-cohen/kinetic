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
#pragma once
#ifndef KINETIC_MESSAGE_FRAMING_HPP
#define KINETIC_MESSAGE_FRAMING_HPP

/*
 * Include Files
 */
#include <stdint.h>
#include <arpa/inet.h>

/*
 * Contains the framing data for a Kinetic Message. Its three data members are the first nine bytes
 * of a Kinetic PDU.
 */
class KineticMessageFraming {
public:
    /*
     * Constructors
     */
    KineticMessageFraming()
        : m_magicNumber(0), m_messageSize(0), m_valueSize(0) {}

    KineticMessageFraming(uint8_t  magicNumber, uint32_t messageSize, uint32_t valueSize)
        : m_magicNumber(magicNumber), m_messageSize(htonl(messageSize)), m_valueSize(htonl(valueSize)) {}

    /*
     * Getters (which convert sizes from the host format to big endian)
     */
    inline uint8_t magicNumber() const {return m_magicNumber;}
    inline uint32_t messageSize() const {return ntohl(m_messageSize);}
    inline uint32_t valueSize() const {return ntohl(m_valueSize);}

    /*
     * Setters (which convert sizes from big endian to the host format)
     */
    void setMagicNumber(uint8_t magicNumber) {m_magicNumber = magicNumber;}
    void setMessageSize(uint32_t size) {m_messageSize = htonl(size);}
    void setValueSize(uint32_t size) {m_valueSize = htonl(size);}

private:
    /*
     * Private Data Members
     */
    uint8_t     m_magicNumber;  //!< Kinetic PDU start of frame indicator
    uint32_t    m_messageSize;  //!< Number of bytes for the protocol buffer message
    uint32_t    m_valueSize;    //!< Number of bytes for the optional get/put value
} __attribute__((packed));

/*
 * Value used to identify the start of a message frame.
 */
const uint8_t KINETIC_MESSAGE_FRAMING_MAGIC_NUMBER(0x46);

#endif
