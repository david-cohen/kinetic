/*
 * Copyright (c) [2014 - 2016] Western Digital Technologies, Inc.
 *
 * This code is CONFIDENTIAL and a TRADE SECRET of Western Digital Technologies, Inc. and its
 * affiliates ("WD").  This code is protected under copyright laws as an unpublished work of WD.
 * Notice is for informational purposes only and does not imply publication.
 *
 * The receipt or possession of this code does not convey any rights to reproduce or disclose its
 * contents, or to manufacture, use, or sell anything that it may describe, in whole or in part,
 * without the specific written consent of WD.  Any reproduction or distribution of this code
 * without the express written consent of WD is strictly prohibited, is a violation of the copyright
 * laws, and may subject you to criminal prosecution.
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
    inline uint8_t magicNumber() {return m_magicNumber;}
    inline uint32_t messageSize() {return ntohl(m_messageSize);}
    inline uint32_t valueSize() {return ntohl(m_valueSize);}

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
