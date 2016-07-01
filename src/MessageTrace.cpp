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
#include <iostream>
#include "MessageTrace.hpp"

/*
 * Used Namespace Members
 */
using com::seagate::kinetic::proto::Command_Header;
using com::seagate::kinetic::proto::Command_KeyValue;
using com::seagate::kinetic::proto::Command_Range;
using com::seagate::kinetic::proto::Command_GetLog_Configuration;
using com::seagate::kinetic::proto::Command_GetLog;
using com::seagate::kinetic::proto::Command_GetLog_Statistics;
using com::seagate::kinetic::proto::Command_GetLog_Capacity;
using com::seagate::kinetic::proto::Command_GetLog_Limits;
using com::seagate::kinetic::proto::Command_GetLog;
using com::seagate::kinetic::proto::Command_Setup;
using com::seagate::kinetic::proto::Command_Security;
using com::seagate::kinetic::proto::Command_Security_ACL;
using com::seagate::kinetic::proto::Command_Security_ACL_Scope;
using com::seagate::kinetic::proto::Command_PinOperation;
using com::seagate::kinetic::proto::Command_Batch;
using com::seagate::kinetic::proto::Command_Body;
using com::seagate::kinetic::proto::Command_Status;
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
using com::seagate::kinetic::proto::Command_Status_StatusCode_NOT_ATTEMPTED;
using com::seagate::kinetic::proto::Command_Status_StatusCode_SUCCESS;
using com::seagate::kinetic::proto::Command_Status_StatusCode_HMAC_FAILURE;
using com::seagate::kinetic::proto::Command_Status_StatusCode_NOT_AUTHORIZED;
using com::seagate::kinetic::proto::Command_Status_StatusCode_VERSION_FAILURE;
using com::seagate::kinetic::proto::Command_Status_StatusCode_INTERNAL_ERROR;
using com::seagate::kinetic::proto::Command_Status_StatusCode_HEADER_REQUIRED;
using com::seagate::kinetic::proto::Command_Status_StatusCode_NOT_FOUND;
using com::seagate::kinetic::proto::Command_Status_StatusCode_VERSION_MISMATCH;
using com::seagate::kinetic::proto::Command_Status_StatusCode_SERVICE_BUSY;
using com::seagate::kinetic::proto::Command_Status_StatusCode_EXPIRED;
using com::seagate::kinetic::proto::Command_Status_StatusCode_DATA_ERROR;
using com::seagate::kinetic::proto::Command_Status_StatusCode_PERM_DATA_ERROR;
using com::seagate::kinetic::proto::Command_Status_StatusCode_REMOTE_CONNECTION_ERROR;
using com::seagate::kinetic::proto::Command_Status_StatusCode_NO_SPACE;
using com::seagate::kinetic::proto::Command_Status_StatusCode_NO_SUCH_HMAC_ALGORITHM;
using com::seagate::kinetic::proto::Command_Status_StatusCode_INVALID_REQUEST;
using com::seagate::kinetic::proto::Command_Status_StatusCode_NESTED_OPERATION_ERRORS;
using com::seagate::kinetic::proto::Command_Status_StatusCode_DEVICE_LOCKED;
using com::seagate::kinetic::proto::Command_Status_StatusCode_DEVICE_ALREADY_UNLOCKED;
using com::seagate::kinetic::proto::Command_Status_StatusCode_CONNECTION_TERMINATED;
using com::seagate::kinetic::proto::Command_Status_StatusCode_INVALID_BATCH;
using com::seagate::kinetic::proto::Command_Synchronization_WRITETHROUGH;
using com::seagate::kinetic::proto::Command_Synchronization_WRITEBACK;
using com::seagate::kinetic::proto::Command_Synchronization_FLUSH;

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
        std::cout << "    Authentication Type: " << toString(message->authtype()) << std::endl;
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
void MessageTrace::outputHeader(const Command_Header& header) {
    if (header.has_messagetype())
        std::cout << "        Message Type: " << toString(header.messagetype()) << std::endl;
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
        std::cout << "        Early Exit: " << toString(header.earlyexit()) << std::endl;
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
void MessageTrace::outputKeyValue(const Command_KeyValue& keyvalue) {
    if (keyvalue.has_key()) {
        std::cout << "          Key: ";
        outputString(keyvalue.key());
    }
    if (keyvalue.has_dbversion()) {
        std::cout << "          DB Version: ";
        outputString(keyvalue.dbversion());
    }
    if (keyvalue.has_algorithm())
        std::cout << "          Algorithm: " << toString(keyvalue.algorithm()) << std::endl;
    if (keyvalue.has_tag()) {
        std::cout << "          Tag: ";
        outputString(keyvalue.tag());
    }
    if (keyvalue.has_force())
        std::cout << "          Force: " << toString(keyvalue.force()) << std::endl;
    if (keyvalue.has_metadataonly())
        std::cout << "          Metadata Only: " << toString(keyvalue.metadataonly()) << std::endl;
    if (keyvalue.has_synchronization())
        std::cout << "          Synchronization: " << toString(keyvalue.synchronization()) << std::endl;
}

/**
 * Outputs the contents of the Kinetic Command_Range field.
 *
 * @param   range   The protocol buffer range message
 */
void MessageTrace::outputRange(const Command_Range& range) {
    if (range.has_startkey()) {
        std::cout << "          Start Key: ";
        outputString(range.startkey());
    }
    if (range.has_startkeyinclusive())
        std::cout << "          Start Key Inclusive: " << toString(range.startkeyinclusive()) << std::endl;
    if (range.has_endkey()) {
        std::cout << "          End Key: ";
        outputString(range.endkey());
    }

    if (range.has_endkeyinclusive())
        std::cout << "          End Key Inclusive: " << toString(range.endkeyinclusive()) << std::endl;
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
void MessageTrace::outputConfiguration(const Command_GetLog_Configuration& configuration) {
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
void MessageTrace::outputStatistics(const Command_GetLog& getLog) {
    for (int32_t index = 0; index < getLog.statistics_size(); index++) {
        const Command_GetLog_Statistics& statistics(getLog.statistics(index));
        std::cout << "            Statistic {" << std::endl;
        std::cout << "              Message Type: " << toString(statistics.messagetype()) << std::endl;
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
void MessageTrace::outputCapacity(const Command_GetLog_Capacity& capacity) {
    std::cout << "            Nominal: " << capacity.nominalcapacityinbytes() << std::endl;
    std::cout << "            Full: " << (100 * capacity.portionfull()) << " %" << std::endl;
}

/**
 * Outputs the contents of the Kinetic Command_GetLog_Limits field.
 *
 * @param   limits  The protocol buffer limits message
 */
void MessageTrace::outputLimits(const Command_GetLog_Limits& limits) {
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
void MessageTrace::outputGetLog(const Command_GetLog& getLog) {
    if (getLog.types_size() > 0) {
        std::cout << "          Types: ";
        for (auto index = 0; index < getLog.types_size(); index++) {
            std::cout << toString(getLog.types(index)) << ", ";
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
void MessageTrace::outputSetup(const Command_Setup& setup) {
    if (setup.has_newclusterversion())
        std::cout << "            New Cluster Version: " << setup.newclusterversion() << std::endl;

    if (setup.has_firmwaredownload())
        std::cout << "            Firmware Download: " << toString(setup.firmwaredownload()) << std::endl;
}

/**
 * Outputs the contents of the Kinetic Command_Security field.
 *
 * @param   security    The protocol buffer security message
 */
void MessageTrace::outputSecurity(const Command_Security& security) {
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
        const Command_Security_ACL& acl(security.acl(aclIndex));
        std::cout << "            Identity: " << acl.identity() << std::endl;
        std::cout << "            Key: ";
        outputString(acl.key());
        std::cout << "            HMAC Algorithm: " << toString(acl.hmacalgorithm()) << std::endl;
        for (auto scopeIndex = 0; scopeIndex < acl.scope_size(); scopeIndex++) {
            std::cout << "            Scope {" << std::endl;
            const Command_Security_ACL_Scope& scope(acl.scope(scopeIndex));
            std::cout << "              Offset: " << scope.offset() << std::endl;
            std::cout << "              Value: ";
            outputString(scope.value());
            std::cout << "              TLS Required: " << toString(scope.tlsrequired()) << std::endl;
            std::cout << "              Permission: ";
            for (auto permissionIndex = 0; permissionIndex < scope.permission_size(); permissionIndex++) {
                std::cout << toString(scope.permission(permissionIndex)) << ", ";
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
void MessageTrace::outputPinOp(const Command_PinOperation& pinop) {
    if (pinop.has_pinoptype())
        std::cout << "            PIN Operation: " << toString(pinop.pinoptype()) << std::endl;
}

/**
 * Outputs the contents of the Kinetic Command_Batch field.
 *
 * @param   security    The protocol buffer PIN operation message
 */
void MessageTrace::outputBatch(const Command_Batch& batch) {
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
void MessageTrace::outputBody(const Command_Body& body) {
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
void MessageTrace::outputStatus(const Command_Status& status) {
    if (status.has_code())
        std::cout << "        Code: " << toString(status.code()) << std::endl;
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

/**
 * Converts a boolean to a string.
 *
 * @param   boolValue  The boolean value (true/false) to be converted to a string
 *
 * @return  The boolean value in string form
 */
std::string MessageTrace::toString(bool boolValue) {
    return boolValue ? "True" : "False";
}

/**
 * Converts an algorithm enum to a string.
 *
 * @param  algorithm  the protocol buffer algorithm enum to be converted to a string
 *
 * @return the algorithm in string form
 */
std::string MessageTrace::toString(Command_Algorithm algorithm) {
    switch (algorithm) {
        case Command_Algorithm_INVALID_ALGORITHM:
            return "Invalid";
        case Command_Algorithm_SHA1:
            return "SHA1";
        case Command_Algorithm_SHA2:
            return "SHA2";
        case Command_Algorithm_SHA3:
            return "SHA3";
        case Command_Algorithm_CRC32:
            return "CRC32";
        case Command_Algorithm_CRC64:
            return "CRC64";
        default:
            return "Unknown (" + std::to_string(algorithm) + ")";
    }
}

/**
 * Converts a PIN operation enum to a string.
 *
 * @param  pinop  the protocol buffer PIN operation type enum to be converted to a string
 *
 * @return the PIN operation type in string form
 */
std::string MessageTrace::toString(Command_PinOperation_PinOpType pinop) {
    switch (pinop) {
        case Command_PinOperation_PinOpType_UNLOCK_PINOP:
            return "Unlock";
        case Command_PinOperation_PinOpType_LOCK_PINOP:
            return "Lock";
        case Command_PinOperation_PinOpType_ERASE_PINOP:
            return "Erase";
        case Command_PinOperation_PinOpType_SECURE_ERASE_PINOP:
            return "Secure Erase";
        case Command_PinOperation_PinOpType_INVALID_PINOP:
            return "Invalid";
        default:
            return "Unknown (" + std::to_string(pinop) + ")";
    }
}

/**
 * Converts an HMAC Algorithm enum to a string.
 *
 * @param  algorithm  the protocol buffer HMAC algorithm enum to be converted to a string
 *
 * @return the HMAC algorithm in string form
 */
std::string MessageTrace::toString(Command_Security_ACL_HMACAlgorithm algorithm) {
    switch (algorithm) {
        case Command_Security_ACL_HMACAlgorithm_INVALID_HMAC_ALGORITHM:
            return "Invalid";
        case Command_Security_ACL_HMACAlgorithm_HmacSHA1:
            return "HMAC-SHA1";
        default:
            return "Unknown (" + std::to_string(algorithm) + ")";
    }
}

/**
 * Converts an authentication type enum to a string.
 *
 * @param  authType  the protocol buffer authentication type enum to be converted to a string
 *
 * @return the authentication type in string form
 */
std::string MessageTrace::toString(Message_AuthType authType) {
    switch (authType) {
        case Message_AuthType_INVALID_AUTH_TYPE:
            return "Invalid";
        case Message_AuthType_HMACAUTH:
            return "HMAC Authentication";
        case Message_AuthType_PINAUTH:
            return "PIN Authentication";
        case Message_AuthType_UNSOLICITEDSTATUS:
            return "Unsolicited Status";
        default:
            return "Unknown (" + std::to_string(authType) + ")";
    }
}

/**
 * Converts a message type enum to a string.
 *
 * @param  messageType  the protocol buffer message type enum to be converted to a string
 *
 * @return the message type in string form
 */
std::string MessageTrace::toString(Command_MessageType messageType) {
    switch (messageType) {
        case Command_MessageType_GET:
            return "Get";
        case Command_MessageType_GET_RESPONSE:
            return "Get Response";
        case Command_MessageType_PUT:
            return "Put";
        case Command_MessageType_PUT_RESPONSE:
            return "Put Response";
        case Command_MessageType_DELETE:
            return "Delete";
        case Command_MessageType_DELETE_RESPONSE:
            return "Delete Response";
        case Command_MessageType_GETNEXT:
            return "Get Next";
        case Command_MessageType_GETNEXT_RESPONSE:
            return "Get Next Response";
        case Command_MessageType_GETPREVIOUS:
            return "Get Previous";
        case Command_MessageType_GETPREVIOUS_RESPONSE:
            return "Get Previous Response";
        case Command_MessageType_GETKEYRANGE:
            return "Get Key Range";
        case Command_MessageType_GETKEYRANGE_RESPONSE:
            return "Get Key Range Response";
        case Command_MessageType_GETVERSION:
            return "Get Version";
        case Command_MessageType_GETVERSION_RESPONSE:
            return "Get Version Response";
        case Command_MessageType_SETUP:
            return "Setup";
        case Command_MessageType_SETUP_RESPONSE:
            return "Setup Response";
        case Command_MessageType_GETLOG:
            return "Get Log";
        case Command_MessageType_GETLOG_RESPONSE:
            return "Get Log Response";
        case Command_MessageType_SECURITY:
            return "Security";
        case Command_MessageType_SECURITY_RESPONSE:
            return "Security Response";
        case Command_MessageType_PEER2PEERPUSH:
            return "Peer-to-Peer Push";
        case Command_MessageType_PEER2PEERPUSH_RESPONSE:
            return "Peer-to-Peer Push Response";
        case Command_MessageType_NOOP:
            return "No-Op";
        case Command_MessageType_NOOP_RESPONSE:
            return "No-Op Response";
        case Command_MessageType_FLUSHALLDATA:
            return "Flush All Data";
        case Command_MessageType_FLUSHALLDATA_RESPONSE:
            return "Flush All Data Response";
        case Command_MessageType_PINOP:
            return "PIN-Op";
        case Command_MessageType_PINOP_RESPONSE:
            return "PIN-Op Response";
        case Command_MessageType_MEDIASCAN:
            return "Media Scan";
        case Command_MessageType_MEDIASCAN_RESPONSE:
            return "Media Scan Response";
        case Command_MessageType_MEDIAOPTIMIZE:
            return "Media Optimize";
        case Command_MessageType_MEDIAOPTIMIZE_RESPONSE:
            return "Media Optimize Response";
        case Command_MessageType_START_BATCH:
            return "Start Batch";
        case Command_MessageType_START_BATCH_RESPONSE:
            return "Start Batch Response";
        case Command_MessageType_END_BATCH:
            return "End Batch";
        case Command_MessageType_END_BATCH_RESPONSE:
            return "End Batch Response";
        case Command_MessageType_ABORT_BATCH:
            return "Abort Batch";
        case Command_MessageType_ABORT_BATCH_RESPONSE:
            return "Abort Batch Response";
        default:
            return "Unknown (" + std::to_string(messageType) + ")";
    }
}

/**
 * Converts a log type enum to a string.
 *
 * @param  synchronization  the protocol buffer type enum to be converted to a string
 *
 * @return the type in string form
 */
std::string MessageTrace::toString(Command_GetLog_Type type) {
    switch (type) {
        case Command_GetLog_Type_UTILIZATIONS:
            return "Utilizations";
        case Command_GetLog_Type_TEMPERATURES:
            return "Temperatures";
        case Command_GetLog_Type_CAPACITIES:
            return "Capacities";
        case Command_GetLog_Type_CONFIGURATION:
            return "Configuration";
        case Command_GetLog_Type_STATISTICS:
            return "Statistics";
        case Command_GetLog_Type_MESSAGES:
            return "Messages";
        case Command_GetLog_Type_LIMITS:
            return "Limits";
        case Command_GetLog_Type_DEVICE:
            return "Device";
        default:
            return "Unknown (" + std::to_string(type) + ")";
    }
}

/**
 * Converts a permission enum to a string.
 *
 * @param  synchronization  the protocol buffer permission enum to be converted to a string
 *
 * @return the permission in string form
 */
std::string MessageTrace::toString(Command_Security_ACL_Permission permission) {
    switch (permission) {
        case Command_Security_ACL_Permission_READ:
            return "Read";
        case Command_Security_ACL_Permission_WRITE:
            return "Write";
        case Command_Security_ACL_Permission_DELETE:
            return "Delete";
        case Command_Security_ACL_Permission_RANGE:
            return "Range";
        case Command_Security_ACL_Permission_SETUP:
            return "Setup";
        case Command_Security_ACL_Permission_P2POP:
            return "Peer-to-Peer Operation";
        case Command_Security_ACL_Permission_GETLOG:
            return "Get Log";
        case Command_Security_ACL_Permission_SECURITY:
            return "Security";
        case Command_Security_ACL_Permission_INVALID_PERMISSION:
            return "Invalid";
        default:
            return "Unknown (" + std::to_string(permission) + ")";
    }
}

/**
 * Converts a synchronization enum to a string.
 *
 * @param  synchronization  the protocol buffer synchronization enum to be converted to a string
 *
 * @return the synchronization in string form
 */
std::string MessageTrace::toString(Command_Synchronization synchronization) {
    if (synchronization == Command_Synchronization_WRITETHROUGH)
        return "Write-Through";
    else if (synchronization == Command_Synchronization_WRITEBACK)
        return "Write-Back";
    else if (synchronization == Command_Synchronization_FLUSH)
        return "Flush";

    return "Unknown (" + std::to_string(synchronization) + ")";
}

/**
 * Converts a status code enum to a string.
 *
 * @param  statusCode  the protocol buffer statusCode enum to be converted to a string
 *
 * @return the statusCode in string form
 */
std::string MessageTrace::toString(Command_Status_StatusCode statusCode) {
    switch (statusCode) {
        case Command_Status_StatusCode_NOT_ATTEMPTED:
            return "Not Attempted";
        case Command_Status_StatusCode_SUCCESS:
            return "Success";
        case Command_Status_StatusCode_HMAC_FAILURE:
            return "HMAC Failure";
        case Command_Status_StatusCode_NOT_AUTHORIZED:
            return "Not Authorized";
        case Command_Status_StatusCode_VERSION_FAILURE:
            return "Version Failure";
        case Command_Status_StatusCode_INTERNAL_ERROR:
            return "Internal Error";
        case Command_Status_StatusCode_HEADER_REQUIRED:
            return "Header Required";
        case Command_Status_StatusCode_NOT_FOUND:
            return "Not Found";
        case Command_Status_StatusCode_VERSION_MISMATCH:
            return "Version Mismatch";
        case Command_Status_StatusCode_SERVICE_BUSY:
            return "service Busy";
        case Command_Status_StatusCode_EXPIRED:
            return "Expired";
        case Command_Status_StatusCode_DATA_ERROR:
            return "Data Error";
        case Command_Status_StatusCode_PERM_DATA_ERROR:
            return "Perm Data Error";
        case Command_Status_StatusCode_REMOTE_CONNECTION_ERROR:
            return "Remote Connection Error";
        case Command_Status_StatusCode_NO_SPACE:
            return "No Space";
        case Command_Status_StatusCode_NO_SUCH_HMAC_ALGORITHM:
            return "No_Such_HMAC Algorithm";
        case Command_Status_StatusCode_INVALID_REQUEST:
            return "Invalid Request";
        case Command_Status_StatusCode_NESTED_OPERATION_ERRORS:
            return "Nested Operation Errors";
        case Command_Status_StatusCode_DEVICE_LOCKED:
            return "Device Locked";
        case Command_Status_StatusCode_DEVICE_ALREADY_UNLOCKED:
            return "Device Already Unlocked";
        case Command_Status_StatusCode_CONNECTION_TERMINATED:
            return "Connection Terminated";
        case Command_Status_StatusCode_INVALID_BATCH:
            return "Invalid Batch";
        default:
            return "Unknown (" + std::to_string(statusCode) + ")";
    }
}
