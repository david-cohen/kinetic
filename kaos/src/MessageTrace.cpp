/*
 * Copyright (c) [2014 - 2016] Western Digital Technologies, Inc. All rights reserved.
 */

/*
 * Include Files
 */
#include <stdint.h>
#include <string>
#include <iomanip>
#include <iostream>
#include "Translator.hpp"
#include "MessageTrace.hpp"

/**
 * Outputs the contents of a Kinetic message.
 *
 * @param   messageFraming  The Kinetic message's framing data
 * @param   message         The Kinetic message to display
 */
void MessageTrace::outputContents(KineticMessageFraming& messageFraming, KineticMessage* message) {

    const uint32_t BYTE_MASK(0xff);
    std::cout << std::endl << "Kinetic PDU {" << std::endl;
    std::cout << "  Magic Number: " << ((uint32_t) messageFraming.magicNumber() & BYTE_MASK) << std::endl;
    std::cout << "  Message Size: " << messageFraming.messageSize() << std::endl;
    std::cout << "  Value Size: " << messageFraming.valueSize() << std::endl;

    std::cout << "  Protocol Buffer Message {" << std::endl;

    if (message->has_authtype()) {
        std::cout << "    Authentication Type: " << Translator::toString(message->authtype()) << std::endl;
    }

    if (message->has_pinauth()) {
        std::cout << "    PIN: ";
        outputString(message->pinauth().pin());
    }

    if (message->has_hmacauth()) {
        std::cout << "    Identity: " << message->hmacauth().identity() << std::endl;
        std::cout << "    HMAC: ";
        outputHexBytes(message->hmacauth().hmac());
    }

    if (message->has_command()) {
        std::cout << "    Command {" << std::endl;
        if (message->command()->has_header()) {
            std::cout << "      Header {" << std::endl;
            outputHeader(message->command()->header());
            std::cout << "      }" << std::endl;
        }
        if (message->command()->has_body()) {
            std::cout << "      Body {" << std::endl;
            outputBody(message->command()->body());
            std::cout << "      }" << std::endl;
        }
        if (message->command()->has_status()) {
            std::cout << "      Status {" << std::endl;
            outputStatus(message->command()->status());
            std::cout << "      }" << std::endl;
        }
        std::cout << "    }" << std::endl;
    }

    std::cout << "  }" << std::endl;
    if (!message->value().empty()) {
        const uint32_t MAX_VALUE_BYTES(16);
        std::cout << "  Value: ";
        if (message->value().size() <= MAX_VALUE_BYTES)
            outputString(message->value());
        else {
            outputString(message->value().substr(0, MAX_VALUE_BYTES), false);
            std::cout << "..." << std::endl;
        }
    }
    std::cout << "}" << std::endl;
}

/**
 * Outputs the contents of the Kinetic Command_Header field.
 *
 * @param   header  The protocol buffer header message
 */
void MessageTrace::outputHeader(const com::seagate::kinetic::proto::Command_Header& header) {

    if (header.has_messagetype())
        std::cout << "        Message Type: " << Translator::toString(header.messagetype()) << std::endl;
    if (header.has_connectionid())
        std::cout << "        Connection ID: " << header.connectionid() << std::endl;
    if (header.has_sequence())
        std::cout << "        Sequence: " << header.sequence() << std::endl;
    if (header.has_acksequence())
        std::cout << "        Ack Sequence: " << header.acksequence() << std::endl;
    if (header.has_clusterversion())
        std::cout << "        Cluster Version: " << header.clusterversion() << std::endl;
    if (header.has_timeout())
        std::cout << "        Timeout: " << header.timeout() << std::endl;
    if (header.has_earlyexit())
        std::cout << "        Early Exit: " << Translator::toString(header.earlyexit()) << std::endl;
    if (header.has_priority())
        std::cout << "        Priority: " << header.priority() << std::endl;
    if (header.has_timequanta())
        std::cout << "        Time Quanta: " << header.timequanta() << std::endl;
    if (header.has_batchid())
        std::cout << "        Batch ID: " << header.batchid() << std::endl;
}

/**
 * Outputs the contents of the Kinetic Command_KeyValue field.
 *
 * @param   keyvalue    The protocol buffer keyvalue message
 */
void MessageTrace::outputKeyValue(const com::seagate::kinetic::proto::Command_KeyValue& keyvalue) {

    if (keyvalue.has_key()) {
        std::cout << "          Key: ";
        outputString(keyvalue.key());
    }
    if (keyvalue.has_dbversion()) {
        std::cout << "          DB Version: ";
        outputString(keyvalue.dbversion());
    }
    if (keyvalue.has_algorithm())
        std::cout << "          Algorithm: " << Translator::toString(keyvalue.algorithm()) << std::endl;
    if (keyvalue.has_tag()) {
        std::cout << "          Tag: ";
        outputString(keyvalue.tag());
    }
    if (keyvalue.has_force())
        std::cout << "          Force: " << Translator::toString(keyvalue.force()) << std::endl;
    if (keyvalue.has_metadataonly())
        std::cout << "          Metadata Only: " << Translator::toString(keyvalue.metadataonly()) << std::endl;
    if (keyvalue.has_synchronization())
        std::cout << "          Synchronization: " << Translator::toString(keyvalue.synchronization()) << std::endl;
}

/**
 * Outputs the contents of the Kinetic Command_Range field.
 *
 * @param   range   The protocol buffer range message
 */
void MessageTrace::outputRange(const com::seagate::kinetic::proto::Command_Range& range) {

    if (range.has_startkey()) {
        std::cout << "          Start Key: ";
        outputString(range.startkey());
    }
    if (range.has_startkeyinclusive())
        std::cout << "          Start Key Inclusive: " << Translator::toString(range.startkeyinclusive()) << std::endl;
    if (range.has_endkey()) {
        std::cout << "          End Key: ";
        outputString(range.endkey());
    }

    if (range.has_endkeyinclusive())
        std::cout << "          End Key Inclusive: " << Translator::toString(range.endkeyinclusive()) << std::endl;
    if (range.has_maxreturned())
        std::cout << "          Max Returned: " << range.maxreturned() << std::endl;
    if (range.has_reverse())
        std::cout << "          Reverse: " << range.reverse() << std::endl;

    if (range.keys_size() > 0) {
        std::cout << "          Returned Keys: ";
        for (auto index = 0; index < range.keys_size(); index++) {
            outputString(range.keys(index), false);
            std::cout << ", ";
        }
        std::cout << std::endl;
    }
}

/**
 * Outputs the contents of the Kinetic Command_GetLog_Configuration field.
 *
 * @param   configuration   The protocol buffer configuration message
 */
void MessageTrace::outputConfiguration(const com::seagate::kinetic::proto::Command_GetLog_Configuration& configuration) {

    std::cout << "            Vendor: " << configuration.vendor() << std::endl;
    std::cout << "            Model: " << configuration.model() << std::endl;
    std::cout << "            Version: " << configuration.version() << std::endl;
    std::cout << "            Serial Number: " << configuration.serialnumber() << std::endl;
    std::cout << "            Compilation Date: " << configuration.compilationdate() << std::endl;
    std::cout << "            Source Hash: " << configuration.sourcehash() << std::endl;
    std::cout << "            Port: " << configuration.port() << std::endl;
    std::cout << "            TLS Port: " << configuration.tlsport() << std::endl;
}

/**
 * Outputs the contents of the Kinetic Command_GetLog_Statistics fields.
 *
 * @param   getLog  The protocol buffer getLog message (which contains the statistics)
 */
void MessageTrace::outputStatistics(const com::seagate::kinetic::proto::Command_GetLog& getLog) {

    for (int32_t index = 0; index < getLog.statistics_size(); index++) {
        const com::seagate::kinetic::proto::Command_GetLog_Statistics& statistics(getLog.statistics(index));
        std::cout << "            Statistic {" << std::endl;
        std::cout << "              Message Type: " << Translator::toString(statistics.messagetype()) << std::endl;
        std::cout << "              Byte Count: " << statistics.bytes() << std::endl;
        std::cout << "              Count: " << statistics.count() << std::endl;
        std::cout << "            }" << std::endl;
    }
}

/**
 * Outputs the contents of the Kinetic Command_GetLog_Capacity field.
 *
 * @param   capacity    The protocol buffer capacity message
 */
void MessageTrace::outputCapacity(const com::seagate::kinetic::proto::Command_GetLog_Capacity& capacity) {

    std::cout << "            Nominal: " << capacity.nominalcapacityinbytes() << std::endl;
    std::cout << "            Full: " << (100 * capacity.portionfull()) << " %" << std::endl;
}

/**
 * Outputs the contents of the Kinetic Command_GetLog_Limits field.
 *
 * @param   limits  The protocol buffer limits message
 */
void MessageTrace::outputLimits(const com::seagate::kinetic::proto::Command_GetLog_Limits& limits) {

    const ::google::protobuf::uint32 UNSUPPORTED_LIMIT(0xffffffff);
    if (limits.maxkeysize() != UNSUPPORTED_LIMIT)
        std::cout << "            Max Key Size: " << limits.maxkeysize() << std::endl;
    if (limits.maxvaluesize() != UNSUPPORTED_LIMIT)
        std::cout << "            Max Value Size: " << limits.maxvaluesize() << std::endl;
    if (limits.maxversionsize() != UNSUPPORTED_LIMIT)
        std::cout << "            Max Version Size: " << limits.maxversionsize() << std::endl;
    if (limits.maxtagsize() != UNSUPPORTED_LIMIT)
        std::cout << "            Max Tag Size: " << limits.maxtagsize() << std::endl;
    if (limits.maxkeyrangecount() != UNSUPPORTED_LIMIT)
        std::cout << "            Max Key Range Count: " << limits.maxkeyrangecount() << std::endl;
    if (limits.maxconnections() != UNSUPPORTED_LIMIT)
        std::cout << "            Max Connections: " << limits.maxconnections() << std::endl;
    if (limits.maxoutstandingreadrequests() != UNSUPPORTED_LIMIT)
        std::cout << "            Max Outstanding Read Requests: " << limits.maxoutstandingreadrequests() << std::endl;
    if (limits.maxoutstandingwriterequests() != UNSUPPORTED_LIMIT)
        std::cout << "            Max Outstanding Write Requests: " << limits.maxoutstandingwriterequests() << std::endl;
    if (limits.maxmessagesize() != UNSUPPORTED_LIMIT)
        std::cout << "            Max Message Size: " << limits.maxmessagesize() << std::endl;
    if (limits.maxidentitycount() != UNSUPPORTED_LIMIT)
        std::cout << "            Max Identity Count: " << limits.maxidentitycount() << std::endl;
}

/**
 * Outputs the contents of the Kinetic Command_GetLog field.
 *
 * @param   getLog  The protocol buffer getLog message
 */
void MessageTrace::outputGetLog(const com::seagate::kinetic::proto::Command_GetLog& getLog) {

    if (getLog.types_size() > 0) {
        std::cout << "          Types: ";
        for (auto index = 0; index < getLog.types_size(); index++) {
            std::cout << Translator::toString(getLog.types(index)) << ", ";
        }
        std::cout << std::endl;
    }

    if (getLog.utilizations_size() > 0) {
        std::cout << "          Utilization {" << std::endl;
        std::cout << "          }" << std::endl;
    }

    if (getLog.temperatures_size() > 0) {
        std::cout << "          Temperature {" << std::endl;
        std::cout << "          }" << std::endl;
    }

    if (getLog.statistics_size() > 0) {
        std::cout << "          Statistics {" << std::endl;
        outputStatistics(getLog);
        std::cout << "          }" << std::endl;
    }

    if (getLog.has_configuration()) {
        std::cout << "          Configuration {" << std::endl;
        outputConfiguration(getLog.configuration());
        std::cout << "          }" << std::endl;
    }

    if (getLog.has_capacity()) {
        std::cout << "          Capacity {" << std::endl;
        outputCapacity(getLog.capacity());
        std::cout << "          }" << std::endl;
    }

    if (getLog.has_limits()) {
        std::cout << "          Limits {" << std::endl;
        outputLimits(getLog.limits());
        std::cout << "          }" << std::endl;
    }

    if (getLog.has_messages()) {
        std::cout << "          Messages {" << std::endl;
        std::cout << "          }" << std::endl;
    }
}

/**
 * Outputs the contents of the Kinetic Command_Setup field.
 *
 * @param   setup   The protocol buffer setup message
 */
void MessageTrace::outputSetup(const com::seagate::kinetic::proto::Command_Setup& setup) {

    if (setup.has_newclusterversion())
        std::cout << "            New Cluster Version: " << setup.newclusterversion() << std::endl;

    if (setup.has_firmwaredownload())
        std::cout << "            Firmware Download: " << Translator::toString(setup.firmwaredownload()) << std::endl;
}

/**
 * Outputs the contents of the Kinetic Command_Security field.
 *
 * @param   security    The protocol buffer security message
 */
void MessageTrace::outputSecurity(const com::seagate::kinetic::proto::Command_Security& security) {

    std::cout << "          Old Lock PIN: ";
    outputString(security.oldlockpin());
    std::cout << "          New Lock PIN: ";
    outputString(security.newlockpin());
    std::cout << "          Old Erase PIN: ";
    outputString(security.olderasepin());
    std::cout << "          New Erase PIN: ";
    outputString(security.newerasepin());

    for (auto aclIndex = 0; aclIndex < security.acl_size(); aclIndex++) {
        std::cout << "          ACL {" << std::endl;
        const com::seagate::kinetic::proto::Command_Security_ACL& acl(security.acl(aclIndex));
        std::cout << "            Identity: " << acl.identity() << std::endl;
        std::cout << "            Key: ";
        outputString(acl.key());
        std::cout << "            HMAC Algorithm: " << Translator::toString(acl.hmacalgorithm()) << std::endl;
        for (auto scopeIndex = 0; scopeIndex < acl.scope_size(); scopeIndex++) {
            std::cout << "            Scope {" << std::endl;
            const com::seagate::kinetic::proto::Command_Security_ACL_Scope& scope(acl.scope(scopeIndex));
            std::cout << "              Offset: " << scope.offset() << std::endl;
            std::cout << "              Value: ";
            outputString(scope.value());
            std::cout << "              TLS Required: " << Translator::toString(scope.tlsrequired()) << std::endl;
            std::cout << "              Permission: ";
            for (auto permissionIndex = 0; permissionIndex < scope.permission_size(); permissionIndex++) {
                std::cout << Translator::toString(scope.permission(permissionIndex)) << ", ";
            }
            std::cout << std::endl;
            std::cout << "            }" << std::endl;
        }
        std::cout << "          }" << std::endl;
    }
}

/**
 * Outputs the contents of the Kinetic Command_PinOperation field.
 *
 * @param   security    The protocol buffer PIN operation message
 */
void MessageTrace::outputPinOp(const com::seagate::kinetic::proto::Command_PinOperation& pinop) {

    if (pinop.has_pinoptype())
        std::cout << "            PIN Operation: " << Translator::toString(pinop.pinoptype()) << std::endl;
}

/**
 * Outputs the contents of the Kinetic Command_Batch field.
 *
 * @param   security    The protocol buffer PIN operation message
 */
void MessageTrace::outputBatch(const com::seagate::kinetic::proto::Command_Batch& batch) {

    if (batch.has_count())
        std::cout << "            Count: " << batch.count() << std::endl;
    if (batch.has_failedsequence())
        std::cout << "            Failed Sequence: " << batch.failedsequence() << std::endl;

    std::cout << "            Sequence [";
    for (auto sequenceIndex = 0; sequenceIndex < batch.sequence_size(); sequenceIndex++) {
        std::cout << batch.sequence(sequenceIndex);
        if (sequenceIndex < (batch.sequence_size() - 1))
            std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}

/**
 * Outputs the contents of the Kinetic Command_Body field.
 *
 * @param   body    The protocol buffer body message
 */
void MessageTrace::outputBody(const com::seagate::kinetic::proto::Command_Body& body) {

    if (body.has_keyvalue()) {
        std::cout << "        Key/Value {" << std::endl;
        outputKeyValue(body.keyvalue());
        std::cout << "        }" << std::endl;
    }
    if (body.has_range()) {
        std::cout << "        Range {" << std::endl;
        outputRange(body.range());
        std::cout << "        }" << std::endl;
    }
    if (body.has_setup()) {
        std::cout << "        Setup {" << std::endl;
        outputSetup(body.setup());
        std::cout << "        }" << std::endl;
    }
    if (body.has_p2poperation()) {
        std::cout << "        Peer-to-Peer Operation {" << std::endl;
        std::cout << "        }" << std::endl;
    }
    if (body.has_getlog()) {
        std::cout << "        Get Log {" << std::endl;
        outputGetLog(body.getlog());
        std::cout << "        }" << std::endl;
    }
    if (body.has_security()) {
        std::cout << "        Security {" << std::endl;
        outputSecurity(body.security());
        std::cout << "        }" << std::endl;
    }
    if (body.has_pinop()) {
        std::cout << "        PIN Op {" << std::endl;
        outputPinOp(body.pinop());
        std::cout << "        }" << std::endl;
    }
    if (body.has_batch()) {
        std::cout << "        Batch {" << std::endl;
        outputBatch(body.batch());
        std::cout << "        }" << std::endl;
    }
}

/**
 * Outputs the contents of the Kinetic Command_Status field.
 *
 * @param   status  The protocol buffer status message
 */
void MessageTrace::outputStatus(const com::seagate::kinetic::proto::Command_Status& status) {

    if (status.has_code())
        std::cout << "        Code: " << Translator::toString(status.code()) << std::endl;
    if (status.has_statusmessage())
        std::cout << "        Status Message: " << status.statusmessage() << std::endl;
    if (status.has_detailedmessage())
        std::cout << "        Detailed Message: " << status.detailedmessage() << std::endl;
}

/**
 * Outputs the specified data in hexadecimal.
 *
 * @param   data        The data to output in hex
 * @param   newLine     True if a newline is to be output at the end
 */
void MessageTrace::outputHexBytes(const std::string& data, bool newLine) {

    const uint32_t BYTE_MASK(0xff);
    if (data.size() > 0)
        std::cout << "0x";

    for (uint32_t index = 0; index < data.size(); index++) {
        uint32_t value = ((uint32_t)data[index]) & BYTE_MASK;
        std::cout << std::setw(2) << std::setfill('0') << std::hex << value;
    }
    std::cout << std::dec;
    if (newLine)
        std::cout << std::endl;
}

/**
 * Outputs the specified string.  If the string contains non-ASCII alpha-numeric values (or dashes
 * or underscores),  then output the contents of the string in hex.
 *
 * @param   data        The string data to output
 * @param   newLine     True if a newline is to be output after the string
 */
void MessageTrace::outputString(const std::string& data, bool newLine) {

    bool ascii = true;
    for (uint32_t index = 0; index < data.size(); index++) {
        if (!isalnum(data[index]) && (data[index] != '_') && (data[index] != '-')) {
            ascii = false;
            break;
        }
    }
    if (ascii) {
        std::cout << data;
        if (newLine)
            std::cout << std::endl;
    }
    else
        outputHexBytes(data, newLine);
}

