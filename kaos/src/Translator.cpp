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
#include <string>
#include <sstream>
#include "Hmac.hpp"
#include "Translator.hpp"
#include "Kinetic.pb.hpp"
#include "Settings.pb.hpp"
#include "AccessScope.hpp"

/*
 * Used Namespace Members
 */
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
 * Translates HMAC algorithm from settings format.
 *
 * @param   hmacAlgorithm   The algorithm in the persisted settings format
 *
 * @return  The algorithm in the internal format
 */
HmacAlgorithm Translator::fromSettingsFormat(kaos::Settings_ACL_HmacAlgorithm hmacAlgorithmSetting) {
    return hmacAlgorithmSetting == kaos::Settings_ACL_HmacAlgorithm::Settings_ACL_HmacAlgorithm_HMAC_SHA1
           ? HmacAlgorithm::SHA1 : HmacAlgorithm::UNKNOWN;
}

/**
 * Translates HMAC algorithm to settings format.
 *
 * @param   hmacAlgorithm   The algorithm in the internal format
 *
 * @return  The algorithm in the persisted settings format
 */
kaos::Settings_ACL_HmacAlgorithm Translator::toSettingsFormat(HmacAlgorithm hmacAlgorithm) {
    return hmacAlgorithm == HmacAlgorithm::SHA1 ? kaos::Settings_ACL_HmacAlgorithm::Settings_ACL_HmacAlgorithm_HMAC_SHA1
           : kaos::Settings_ACL_HmacAlgorithm::Settings_ACL_HmacAlgorithm_HMAC_INVALID;
}

/**
 * Translates HMAC algorithm to message format.
 *
 * @param   hmacAlgorithm   The HMAC algorithm in message format
 *
 * @return  The HMAC algorithm in the internal format
 */
HmacAlgorithm Translator::fromMessageFormat(Command_Security_ACL_HMACAlgorithm hmacAlgorithm) {
    if (hmacAlgorithm == Command_Security_ACL_HMACAlgorithm::Command_Security_ACL_HMACAlgorithm_HmacSHA1)
        return HmacAlgorithm::SHA1;
    else
        return HmacAlgorithm::UNKNOWN;
}

/**
 * Translates operation from settings format.
 *
 * @param   operation   The operation in the persisted settings format
 *
 * @return  The operation in the internal format
 */
Operation Translator::fromSettingsFormat(kaos::Settings_ACL_Operation operation) {
    switch (operation) {
        case kaos::Settings_ACL_Operation::Settings_ACL_Operation_READ:
            return Operation::READ;
        case kaos::Settings_ACL_Operation::Settings_ACL_Operation_WRITE:
            return Operation::WRITE;
        case kaos::Settings_ACL_Operation::Settings_ACL_Operation_DELETE:
            return Operation::DELETE;
        case kaos::Settings_ACL_Operation::Settings_ACL_Operation_RANGE:
            return Operation::RANGE;
        case kaos::Settings_ACL_Operation::Settings_ACL_Operation_SETUP:
            return Operation::SETUP;
        case kaos::Settings_ACL_Operation::Settings_ACL_Operation_P2POP:
            return Operation::P2POP;
        case kaos::Settings_ACL_Operation::Settings_ACL_Operation_GETLOG:
            return Operation::GETLOG;
        case kaos::Settings_ACL_Operation::Settings_ACL_Operation_SECURITY:
            return Operation::SECURITY;
        default:
            return Operation::INVALID;
    }
}

/**
 * Translates operation to settings format.
 *
 * @param  operation    The operation in the internal format
 *
 * @return  The operation in the persisted settings format
 */
kaos::Settings_ACL_Operation Translator::toSettingsFormat(Operation operation) {
    switch (operation) {
        case Operation::READ:
            return kaos::Settings_ACL_Operation::Settings_ACL_Operation_READ;
        case Operation::WRITE:
            return kaos::Settings_ACL_Operation::Settings_ACL_Operation_WRITE;
        case Operation::DELETE:
            return kaos::Settings_ACL_Operation::Settings_ACL_Operation_DELETE;
        case Operation::RANGE:
            return kaos::Settings_ACL_Operation::Settings_ACL_Operation_RANGE;
        case Operation::SETUP:
            return kaos::Settings_ACL_Operation::Settings_ACL_Operation_SETUP;
        case Operation::P2POP:
            return kaos::Settings_ACL_Operation::Settings_ACL_Operation_P2POP;
        case Operation::GETLOG:
            return kaos::Settings_ACL_Operation::Settings_ACL_Operation_GETLOG;
        case Operation::SECURITY:
            return kaos::Settings_ACL_Operation::Settings_ACL_Operation_SECURITY;
        default:
            return kaos::Settings_ACL_Operation::Settings_ACL_Operation_GETLOG;
    }
}

/**
 * Translates operation from message format.
 *
 * @param   permission  The operation in message format
 *
 * @return  The operation in the internal format
 */
Operation Translator::fromMessageFormat(Command_Security_ACL_Permission permission) {
    switch (permission) {
        case Command_Security_ACL_Permission_READ:
            return Operation::READ;
        case Command_Security_ACL_Permission_WRITE:
            return Operation::WRITE;
        case Command_Security_ACL_Permission_DELETE:
            return Operation::DELETE;
        case Command_Security_ACL_Permission_RANGE:
            return Operation::RANGE;
        case Command_Security_ACL_Permission_SETUP:
            return Operation::SETUP;
        case Command_Security_ACL_Permission_P2POP:
            return Operation::P2POP;
        case Command_Security_ACL_Permission_GETLOG:
            return Operation::GETLOG;
        case Command_Security_ACL_Permission_SECURITY:
            return Operation::SECURITY;
        default:
            return Operation::INVALID;
    }
}

/**
 * Converts a boolean to a string.
 *
 * @param   boolValue  The boolean value (true/false) to be converted to a string
 *
 * @return  The boolean value in string form
 */
std::string Translator::toString(bool boolValue) {
    return boolValue ? "True" : "False";
}

/**
 * Converts an algorithm enum to a string.
 *
 * @param  algorithm  the protocol buffer algorithm enum to be converted to a string
 *
 * @return the algorithm in string form
 */
std::string Translator::toString(Command_Algorithm algorithm) {
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
std::string Translator::toString(Command_PinOperation_PinOpType pinop) {
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
std::string Translator::toString(Command_Security_ACL_HMACAlgorithm algorithm) {
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
std::string Translator::toString(Message_AuthType authType) {
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
std::string Translator::toString(Command_MessageType messageType) {
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
std::string Translator::toString(Command_GetLog_Type type) {
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
std::string Translator::toString(Command_Security_ACL_Permission permission) {
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
std::string Translator::toString(Command_Synchronization synchronization) {
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
std::string Translator::toString(Command_Status_StatusCode statusCode) {
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

