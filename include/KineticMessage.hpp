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
#ifndef KINETIC_MESSAGE_HPP
#define KINETIC_MESSAGE_HPP

/*
 * Include Files
 */
#include <stdint.h>
#include <map>
#include <list>
#include <string>
#include <memory>
#include "Hmac.hpp"
#include "Kinetic.pb.hpp"
#include "MessageException.hpp"
#include "KineticMessageFraming.hpp"

/**
 * Contains the contents of a Kinetic protocol buffer message and its associated object value.
 * Although the protocol buffer has many substructure, at the top level, it is made up of encoded
 * command and authentication information (authentication type and HMAC authentication parameters or
 * PIN authentication parameters).  In addition to combining the message with the value, it also
 * provides an interface to the decoded command.
 */
class KineticMessage {
public:
    /*
     * Constructor
     */
    KineticMessage() : m_protoMessage(new com::seagate::kinetic::proto::Message()),
        m_command(new com::seagate::kinetic::proto::Command()) {}

    /*
     * Command Functions
     */
    inline bool has_command() const {return m_command != nullptr;}
    inline const ::com::seagate::kinetic::proto::Command* command() const {return m_command.get();}
    inline ::com::seagate::kinetic::proto::Command* mutable_command() const {return m_command.get();}
    inline const ::std::string& commandbytes() const {return m_protoMessage->commandbytes();}
    inline void build_commandbytes() {m_protoMessage->set_commandbytes(m_command->SerializeAsString());}

    /*
     * HMAC Functions
     */
    inline bool has_authtype() const {return m_protoMessage->has_authtype();}
    inline ::com::seagate::kinetic::proto::Message_AuthType authtype() const {return m_protoMessage->authtype();}
    inline void set_authtype(::com::seagate::kinetic::proto::Message_AuthType authtype) {m_protoMessage->set_authtype(authtype);}

    inline bool has_hmacauth() const {return m_protoMessage->has_hmacauth();}
    inline const ::com::seagate::kinetic::proto::Message_HMACauth& hmacauth() const {return m_protoMessage->hmacauth();}
    inline ::com::seagate::kinetic::proto::Message_HMACauth* mutable_hmacauth() {return m_protoMessage->mutable_hmacauth();}

    inline bool has_pinauth() const {return m_protoMessage->has_pinauth();}
    inline const ::com::seagate::kinetic::proto::Message_PINauth& pinauth() const {return m_protoMessage->pinauth();}

    void generateHmac(const std::string& key, HmacAlgorithm algorithm) {
        m_protoMessage->mutable_hmacauth()->set_hmac(Hmac::compute(m_protoMessage->commandbytes(), key, algorithm));
    }

    bool validateHmac(const std::string& key, HmacAlgorithm algorithm) const {
        if (!m_protoMessage->hmacauth().has_hmac())
            return false;
        std::string expectedHmac(Hmac::compute(m_protoMessage->commandbytes(), key, algorithm));
        return (expectedHmac == m_protoMessage->hmacauth().hmac());
    }

    /*
     * Value Functions
     */
    inline std::string& value() {return m_value;}
    inline void setValue(const char* value, size_t valueSize) {m_value.assign(value, valueSize);}

    /*
     * Serialize/Deserialize Functions
     */
    inline bool serializeData(char* buffer, uint32_t size) {
        return m_protoMessage->SerializeToArray(buffer, size);
    }

    inline bool deserializeData(char* buffer, uint32_t size) {
        return (!m_protoMessage->ParseFromArray(buffer, size)) ? false : m_command->ParseFromString(m_protoMessage->commandbytes());
    }

    /*
     * Message Size Functions
     */
    inline uint32_t serializedSize() const { return m_protoMessage->ByteSize();}
    inline uint32_t totalSize() const {return sizeof(KineticMessageFraming) + m_protoMessage->ByteSize() + m_value.size();}

private:
    /*
     * Private Data Members
     */
    std::shared_ptr<com::seagate::kinetic::proto::Message> m_protoMessage;  //!< The kinetic message
    std::shared_ptr<com::seagate::kinetic::proto::Command> m_command;       //!< The message command (which is inside in the message)
    std::string                                            m_value;         //!< Kinetic message value (which is outside the message)
};

/*
 * Map, list, and pointers for Kinetic messages
 */
typedef std::list<KineticMessage*> KineticMessageList;
typedef std::shared_ptr<KineticMessageList> KineticMessageListPtr;
typedef std::map<uint32_t, KineticMessageListPtr> KineticMessageListMap;

#endif
