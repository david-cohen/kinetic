/*
    Copyright (c) [2014 - 2015] Western Digital Technologies, Inc. All rights reserved.
*/

#pragma once
#ifndef KINETIC_MESSAGE_HPP
#define KINETIC_MESSAGE_HPP

/*
    Include Files
*/

#include <stdint.h>
#include <list>
#include <string>
#include <memory>
#include "Hmac.hpp"
#include "Common.hpp"
#include "Kinetic.pb.hpp"
#include "MessageException.hpp"
#include "KineticMessageFraming.hpp"

/**
    Kinetic Message

    This class is a wrapper for a Kinetic protocol buffer message and its assoicated object value.
    Although the protocol buffer has many substructures, at the top level, it is made up of a
    encoded command and authentication information (authentication type and HMAC authentication
    parameters or PIN authentication parameters).  In addition to combining the message with the
    value, it also provides an interface to the decode command.
*/

class KineticMessage {
public:

    /*
        Constructor
    */

    KineticMessage() : m_protoMessage(new com::seagate::kinetic::proto::Message()),
        m_command(new com::seagate::kinetic::proto::Command()) {}

    /*
        Command Functions
    */

    inline bool has_command() {return m_command != nullptr;}
    inline const ::com::seagate::kinetic::proto::Command* command() {return m_command.get();}
    inline ::com::seagate::kinetic::proto::Command* mutable_command() {return m_command.get();}
    inline const ::std::string& commandbytes() {return m_protoMessage->commandbytes();}
    inline void build_commandbytes() {m_protoMessage->set_commandbytes(m_command->SerializeAsString());}

    /*
        HMAC Functions
    */

    inline bool has_authtype() {return m_protoMessage->has_authtype();}
    inline ::com::seagate::kinetic::proto::Message_AuthType authtype() {return m_protoMessage->authtype();}
    inline void set_authtype(::com::seagate::kinetic::proto::Message_AuthType authtype) {m_protoMessage->set_authtype(authtype);}

    inline bool has_hmacauth() {return m_protoMessage->has_hmacauth();}
    inline const ::com::seagate::kinetic::proto::Message_HMACauth& hmacauth() {return m_protoMessage->hmacauth();}
    inline ::com::seagate::kinetic::proto::Message_HMACauth* mutable_hmacauth() {return m_protoMessage->mutable_hmacauth();}

    inline bool has_pinauth() {return m_protoMessage->has_pinauth();}
    inline const ::com::seagate::kinetic::proto::Message_PINauth& pinauth() {return m_protoMessage->pinauth();}

    void generateHmac(const std::string& key, HmacAlgorithm algorithm) {
        m_protoMessage->mutable_hmacauth()->set_hmac(Hmac::compute(m_protoMessage->commandbytes(), key, algorithm));
    }

    bool validateHmac(const std::string& key, HmacAlgorithm algorithm) {
        if (!m_protoMessage->hmacauth().has_hmac())
            return false;
        std::string expectedHmac(Hmac::compute(m_protoMessage->commandbytes(), key, algorithm));
        return (expectedHmac == m_protoMessage->hmacauth().hmac());
    }

    /*
        Value Functions
    */

    inline std::string& value() {return m_value;}
    inline void setValue(const char* value, size_t valueSize) {m_value.assign(value, valueSize);}

    /*
        Serialize/Deserialize Functions
    */

    inline bool serializeData(char* buffer, uint32_t size) {return m_protoMessage->SerializeToArray(buffer, size);}

    inline bool deserializeData(char* buffer, uint32_t size) {
        if (!m_protoMessage->ParseFromArray(buffer, size))
            return false;
        return m_command->ParseFromString(m_protoMessage->commandbytes());
    }

    /*
        Message Size Functions
    */

    inline uint32_t serializedSize() { return m_protoMessage->ByteSize();}
    inline uint32_t totalSize() {return sizeof(KineticMessageFraming) + m_protoMessage->ByteSize() + m_value.size();}

private:

    /*
        Private Data Members
    */

    std::shared_ptr<com::seagate::kinetic::proto::Message> m_protoMessage;
    std::shared_ptr<com::seagate::kinetic::proto::Command> m_command;
    std::string                                            m_value;

    DISALLOW_COPY_AND_ASSIGN(KineticMessage);
};

/*
    Shared pointer and list for the Kinetic message
*/

typedef std::shared_ptr<KineticMessage> KineticMessagePtr;
typedef std::list<KineticMessagePtr> KineticMessageList;

#endif