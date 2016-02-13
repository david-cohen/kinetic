/*
 * Copyright (c) [2014 - 2015] Western Digital Technologies, Inc. All rights reserved.
 */

/*
 * Include Files
 */
#include <string>
#include <sstream>
#include "Hmac.hpp"
#include "Common.hpp"
#include "Translator.hpp"
#include "Kinetic.pb.hpp"
#include "ObjectStore.hpp"
#include "Settings.pb.hpp"
#include "AccessScope.hpp"

/**
 * Translates HMAC algorithm from settings format.
 *
 * @param   hmacAlgorithm   The algorithm in the persisted settings format
 *
 * @return  The algorithm in the internal format
 */
HmacAlgorithm Translator::fromSettingsFormat(kaos::Settings_ACL_HmacAlgorithm hmacAlgorithmSetting) {
    return hmacAlgorithmSetting == kaos::Settings_ACL_HmacAlgorithm::Settings_ACL_HmacAlgorithm_HMAC_SHA1 ? HmacAlgorithm::SHA1 : HmacAlgorithm::UNKNOWN;
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
HmacAlgorithm Translator::fromMessageFormat(com::seagate::kinetic::proto::Command_Security_ACL_HMACAlgorithm hmacAlgorithm) {
    if (hmacAlgorithm == com::seagate::kinetic::proto::Command_Security_ACL_HMACAlgorithm::Command_Security_ACL_HMACAlgorithm_HmacSHA1)
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
Operation Translator::fromMessageFormat(com::seagate::kinetic::proto::Command_Security_ACL_Permission permission) {
    switch (permission) {
        case com::seagate::kinetic::proto::Command_Security_ACL_Permission::Command_Security_ACL_Permission_READ:
            return Operation::READ;
        case com::seagate::kinetic::proto::Command_Security_ACL_Permission::Command_Security_ACL_Permission_WRITE:
            return Operation::WRITE;
        case com::seagate::kinetic::proto::Command_Security_ACL_Permission::Command_Security_ACL_Permission_DELETE:
            return Operation::DELETE;
        case com::seagate::kinetic::proto::Command_Security_ACL_Permission::Command_Security_ACL_Permission_RANGE:
            return Operation::RANGE;
        case com::seagate::kinetic::proto::Command_Security_ACL_Permission::Command_Security_ACL_Permission_SETUP:
            return Operation::SETUP;
        case com::seagate::kinetic::proto::Command_Security_ACL_Permission::Command_Security_ACL_Permission_P2POP:
            return Operation::P2POP;
        case com::seagate::kinetic::proto::Command_Security_ACL_Permission::Command_Security_ACL_Permission_GETLOG:
            return Operation::GETLOG;
        case com::seagate::kinetic::proto::Command_Security_ACL_Permission::Command_Security_ACL_Permission_SECURITY:
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
std::string Translator::toString(Algorithm algorithm) {

    switch (algorithm) {
        case Algorithm::Command_Algorithm_INVALID_ALGORITHM:
            return "Invalid";
        case Algorithm::Command_Algorithm_SHA1:
            return "SHA1";
        case Algorithm::Command_Algorithm_SHA2:
            return "SHA2";
        case Algorithm::Command_Algorithm_SHA3:
            return "SHA3";
        case Algorithm::Command_Algorithm_CRC32:
            return "CRC32";
        case Algorithm::Command_Algorithm_CRC64:
            return "CRC64";
        default:
            return "Unsupported Algorithm (" + ::toString<uint32_t>(algorithm) + ")";
    }
}

/**
 * Converts a PIN operation enum to a string.
 *
 * @param  pinop  the protocol buffer PIN operation type enum to be converted to a string
 *
 * @return the PIN operation type in string form
 */
std::string Translator::toString(com::seagate::kinetic::proto::Command_PinOperation_PinOpType pinop) {

    switch (pinop) {
        case com::seagate::kinetic::proto::Command_PinOperation_PinOpType_UNLOCK_PINOP:
            return "Unlock";
        case com::seagate::kinetic::proto::Command_PinOperation_PinOpType_LOCK_PINOP:
            return "Lock";
        case com::seagate::kinetic::proto::Command_PinOperation_PinOpType_ERASE_PINOP:
            return "Erase";
        case com::seagate::kinetic::proto::Command_PinOperation_PinOpType_SECURE_ERASE_PINOP:
            return "Secure Erase";
        case com::seagate::kinetic::proto::Command_PinOperation_PinOpType_INVALID_PINOP:
            return "Invalid PIN Operation";
        default:
            return "Unsupported PIN Operation (" + ::toString<uint32_t>(pinop) + ")";
    }
}

/**
 * Converts an HMAC Algorithm enum to a string.
 *
 * @param  algorithm  the protocol buffer HMAC algorithm enum to be converted to a string
 *
 * @return the HMAC algorithm in string form
 */
std::string Translator::toString(com::seagate::kinetic::proto::Command_Security_ACL_HMACAlgorithm algorithm) {

    switch (algorithm) {
        case com::seagate::kinetic::proto::Command_Security_ACL_HMACAlgorithm::Command_Security_ACL_HMACAlgorithm_INVALID_HMAC_ALGORITHM:
            return "Invalid";
        case com::seagate::kinetic::proto::Command_Security_ACL_HMACAlgorithm::Command_Security_ACL_HMACAlgorithm_HmacSHA1:
            return "HMAC-SHA1";
        default:
            return "Unsupported HMAC Algorithm (" + ::toString<uint32_t>(algorithm) + ")";
    }
}

/**
 * Converts an authentication type enum to a string.
 *
 * @param  authType  the protocol buffer authentication type enum to be converted to a string
 *
 * @return the authentication type in string form
 */
std::string Translator::toString(com::seagate::kinetic::proto::Message_AuthType authType) {

    switch (authType) {
        case com::seagate::kinetic::proto::Message_AuthType::Message_AuthType_INVALID_AUTH_TYPE:
            return "Invalid";
        case com::seagate::kinetic::proto::Message_AuthType::Message_AuthType_HMACAUTH:
            return "HMAC Authentication";
        case com::seagate::kinetic::proto::Message_AuthType::Message_AuthType_PINAUTH:
            return "PIN Authentication";
        case com::seagate::kinetic::proto::Message_AuthType::Message_AuthType_UNSOLICITEDSTATUS:
            return "Unsolicited Status";
        default:
            return "Unsupported Authentication Type (" + ::toString<uint32_t>(authType) + ")";
    }
}

/**
 * Converts a message type enum to a string.
 *
 * @param  messageType  the protocol buffer message type enum to be converted to a string
 *
 * @return the message type in string form
 */
std::string Translator::toString(com::seagate::kinetic::proto::Command_MessageType messageType) {

    switch (messageType) {
        case com::seagate::kinetic::proto::Command_MessageType::Command_MessageType_GET:
            return "Get";
        case com::seagate::kinetic::proto::Command_MessageType::Command_MessageType_GET_RESPONSE:
            return "Get Response";
        case com::seagate::kinetic::proto::Command_MessageType::Command_MessageType_PUT:
            return "Put";
        case com::seagate::kinetic::proto::Command_MessageType::Command_MessageType_PUT_RESPONSE:
            return "Put Response";
        case com::seagate::kinetic::proto::Command_MessageType::Command_MessageType_DELETE:
            return "Delete";
        case com::seagate::kinetic::proto::Command_MessageType::Command_MessageType_DELETE_RESPONSE:
            return "Delete Response";
        case com::seagate::kinetic::proto::Command_MessageType::Command_MessageType_GETNEXT:
            return "Get Next";
        case com::seagate::kinetic::proto::Command_MessageType::Command_MessageType_GETNEXT_RESPONSE:
            return "Get Next Response";
        case com::seagate::kinetic::proto::Command_MessageType::Command_MessageType_GETPREVIOUS:
            return "Get Previous";
        case com::seagate::kinetic::proto::Command_MessageType::Command_MessageType_GETPREVIOUS_RESPONSE:
            return "Get Previous Response";
        case com::seagate::kinetic::proto::Command_MessageType::Command_MessageType_GETKEYRANGE:
            return "Get Key Range";
        case com::seagate::kinetic::proto::Command_MessageType::Command_MessageType_GETKEYRANGE_RESPONSE:
            return "Get Key Range Response";
        case com::seagate::kinetic::proto::Command_MessageType::Command_MessageType_GETVERSION:
            return "Get Version";
        case com::seagate::kinetic::proto::Command_MessageType::Command_MessageType_GETVERSION_RESPONSE:
            return "Get Version Response";
        case com::seagate::kinetic::proto::Command_MessageType::Command_MessageType_SETUP:
            return "Setup";
        case com::seagate::kinetic::proto::Command_MessageType::Command_MessageType_SETUP_RESPONSE:
            return "Setup Response";
        case com::seagate::kinetic::proto::Command_MessageType::Command_MessageType_GETLOG:
            return "Get Log";
        case com::seagate::kinetic::proto::Command_MessageType::Command_MessageType_GETLOG_RESPONSE:
            return "Get Log Response";
        case com::seagate::kinetic::proto::Command_MessageType::Command_MessageType_SECURITY:
            return "Security";
        case com::seagate::kinetic::proto::Command_MessageType::Command_MessageType_SECURITY_RESPONSE:
            return "Security Response";
        case com::seagate::kinetic::proto::Command_MessageType::Command_MessageType_PEER2PEERPUSH:
            return "Peer-to-Peer Push";
        case com::seagate::kinetic::proto::Command_MessageType::Command_MessageType_PEER2PEERPUSH_RESPONSE:
            return "Peer-to-Peer Push Response";
        case com::seagate::kinetic::proto::Command_MessageType::Command_MessageType_NOOP:
            return "No-Op";
        case com::seagate::kinetic::proto::Command_MessageType::Command_MessageType_NOOP_RESPONSE:
            return "No-Op Response";
        case com::seagate::kinetic::proto::Command_MessageType::Command_MessageType_FLUSHALLDATA:
            return "Flush All Data";
        case com::seagate::kinetic::proto::Command_MessageType::Command_MessageType_FLUSHALLDATA_RESPONSE:
            return "Flush All Data Response";
        case com::seagate::kinetic::proto::Command_MessageType::Command_MessageType_PINOP:
            return "PIN-Op";
        case com::seagate::kinetic::proto::Command_MessageType::Command_MessageType_PINOP_RESPONSE:
            return "PIN-Op Response";
        case com::seagate::kinetic::proto::Command_MessageType::Command_MessageType_MEDIASCAN:
            return "Media Scan";
        case com::seagate::kinetic::proto::Command_MessageType::Command_MessageType_MEDIASCAN_RESPONSE:
            return "Media Scan Response";
        case com::seagate::kinetic::proto::Command_MessageType::Command_MessageType_MEDIAOPTIMIZE:
            return "Media Optimize";
        case com::seagate::kinetic::proto::Command_MessageType::Command_MessageType_MEDIAOPTIMIZE_RESPONSE:
            return "Media Optimize Response";
        case com::seagate::kinetic::proto::Command_MessageType::Command_MessageType_START_BATCH:
            return "Start Batch";
        case com::seagate::kinetic::proto::Command_MessageType::Command_MessageType_START_BATCH_RESPONSE:
            return "Start Batch Response";
        case com::seagate::kinetic::proto::Command_MessageType::Command_MessageType_END_BATCH:
            return "End Batch";
        case com::seagate::kinetic::proto::Command_MessageType::Command_MessageType_END_BATCH_RESPONSE:
            return "End Batch Response";
        case com::seagate::kinetic::proto::Command_MessageType::Command_MessageType_ABORT_BATCH:
            return "Abort Batch";
        case com::seagate::kinetic::proto::Command_MessageType::Command_MessageType_ABORT_BATCH_RESPONSE:
            return "Abort Batch Response";
        default:
            return "Unsupported Message Type (" + ::toString<uint32_t>(messageType) + ")";
    }
}

/**
 * Converts a log type enum to a string.
 *
 * @param  synchronization  the protocol buffer type enum to be converted to a string
 *
 * @return the type in string form
 */
std::string Translator::toString(com::seagate::kinetic::proto::Command_GetLog_Type type) {

    switch (type) {
        case com::seagate::kinetic::proto::Command_GetLog_Type::Command_GetLog_Type_UTILIZATIONS:
            return "Utilizations";
        case com::seagate::kinetic::proto::Command_GetLog_Type::Command_GetLog_Type_TEMPERATURES:
            return "Temperatures";
        case com::seagate::kinetic::proto::Command_GetLog_Type::Command_GetLog_Type_CAPACITIES:
            return "Capacities";
        case com::seagate::kinetic::proto::Command_GetLog_Type::Command_GetLog_Type_CONFIGURATION:
            return "Configuration";
        case com::seagate::kinetic::proto::Command_GetLog_Type::Command_GetLog_Type_STATISTICS:
            return "Statistics";
        case com::seagate::kinetic::proto::Command_GetLog_Type::Command_GetLog_Type_MESSAGES:
            return "Messages";
        case com::seagate::kinetic::proto::Command_GetLog_Type::Command_GetLog_Type_LIMITS:
            return "Limits";
        case com::seagate::kinetic::proto::Command_GetLog_Type::Command_GetLog_Type_DEVICE:
            return "Device";
        default:
            return "Unknown Type (" + ::toString<uint32_t>(type) + ")";
    }
}

/**
 * Converts a permission enum to a string.
 *
 * @param  synchronization  the protocol buffer permission enum to be converted to a string
 *
 * @return the permission in string form
 */
std::string Translator::toString(com::seagate::kinetic::proto::Command_Security_ACL_Permission permission) {

    switch (permission) {
        case com::seagate::kinetic::proto::Command_Security_ACL_Permission::Command_Security_ACL_Permission_READ:
            return "Read";
        case com::seagate::kinetic::proto::Command_Security_ACL_Permission::Command_Security_ACL_Permission_WRITE:
            return "Write";
        case com::seagate::kinetic::proto::Command_Security_ACL_Permission::Command_Security_ACL_Permission_DELETE:
            return "Delete";
        case com::seagate::kinetic::proto::Command_Security_ACL_Permission::Command_Security_ACL_Permission_RANGE:
            return "Range";
        case com::seagate::kinetic::proto::Command_Security_ACL_Permission::Command_Security_ACL_Permission_SETUP:
            return "Setup";
        case com::seagate::kinetic::proto::Command_Security_ACL_Permission::Command_Security_ACL_Permission_P2POP:
            return "Peer-to-Peer Operation";
        case com::seagate::kinetic::proto::Command_Security_ACL_Permission::Command_Security_ACL_Permission_GETLOG:
            return "Get Log";
        case com::seagate::kinetic::proto::Command_Security_ACL_Permission::Command_Security_ACL_Permission_SECURITY:
            return "Security";
        case com::seagate::kinetic::proto::Command_Security_ACL_Permission::Command_Security_ACL_Permission_INVALID_PERMISSION:
            return "Invalid";
        default:
            return "Unknown Permission (" + ::toString<uint32_t>(permission) + ")";
    }
}

/**
 * Converts a synchronization enum to a string.
 *
 * @param  synchronization  the protocol buffer synchronization enum to be converted to a string
 *
 * @return the synchronization in string form
 */
std::string Translator::toString(com::seagate::kinetic::proto::Command_Synchronization synchronization) {

    if (synchronization == com::seagate::kinetic::proto::Command_Synchronization::Command_Synchronization_WRITETHROUGH)
        return "Write-Through";
    else if (synchronization == com::seagate::kinetic::proto::Command_Synchronization::Command_Synchronization_WRITEBACK)
        return "Write-Back";
    else if (synchronization == com::seagate::kinetic::proto::Command_Synchronization::Command_Synchronization_FLUSH)
        return "Flush";

    return "Unsupported Synchronization Value (" + ::toString<uint32_t>(synchronization) + ")";
}

/**
 * Converts a status code enum to a string.
 *
 * @param  statusCode  the protocol buffer statusCode enum to be converted to a string
 *
 * @return the statusCode in string form
 */
std::string Translator::toString(com::seagate::kinetic::proto::Command_Status_StatusCode statusCode) {

    switch (statusCode) {
        case com::seagate::kinetic::proto::Command_Status_StatusCode::Command_Status_StatusCode_NOT_ATTEMPTED:
            return "Not Attempted";
        case com::seagate::kinetic::proto::Command_Status_StatusCode::Command_Status_StatusCode_SUCCESS:
            return "Success";
        case com::seagate::kinetic::proto::Command_Status_StatusCode::Command_Status_StatusCode_HMAC_FAILURE:
            return "HMAC Failure";
        case com::seagate::kinetic::proto::Command_Status_StatusCode::Command_Status_StatusCode_NOT_AUTHORIZED:
            return "Not Authorized";
        case com::seagate::kinetic::proto::Command_Status_StatusCode::Command_Status_StatusCode_VERSION_FAILURE:
            return "Version Failure";
        case com::seagate::kinetic::proto::Command_Status_StatusCode::Command_Status_StatusCode_INTERNAL_ERROR:
            return "Internal Error";
        case com::seagate::kinetic::proto::Command_Status_StatusCode::Command_Status_StatusCode_HEADER_REQUIRED:
            return "Header Required";
        case com::seagate::kinetic::proto::Command_Status_StatusCode::Command_Status_StatusCode_NOT_FOUND:
            return "Not Found";
        case com::seagate::kinetic::proto::Command_Status_StatusCode::Command_Status_StatusCode_VERSION_MISMATCH:
            return "Version Mismatch";
        case com::seagate::kinetic::proto::Command_Status_StatusCode::Command_Status_StatusCode_SERVICE_BUSY:
            return "service Busy";
        case com::seagate::kinetic::proto::Command_Status_StatusCode::Command_Status_StatusCode_EXPIRED:
            return "Expired";
        case com::seagate::kinetic::proto::Command_Status_StatusCode::Command_Status_StatusCode_DATA_ERROR:
            return "Data Error";
        case com::seagate::kinetic::proto::Command_Status_StatusCode::Command_Status_StatusCode_PERM_DATA_ERROR:
            return "Perm Data Error";
        case com::seagate::kinetic::proto::Command_Status_StatusCode::Command_Status_StatusCode_REMOTE_CONNECTION_ERROR:
            return "Remote Connection Error";
        case com::seagate::kinetic::proto::Command_Status_StatusCode::Command_Status_StatusCode_NO_SPACE:
            return "No Space";
        case com::seagate::kinetic::proto::Command_Status_StatusCode::Command_Status_StatusCode_NO_SUCH_HMAC_ALGORITHM:
            return "No_Such_HMAC Algorithm";
        case com::seagate::kinetic::proto::Command_Status_StatusCode::Command_Status_StatusCode_INVALID_REQUEST:
            return "Invalid Request";
        case com::seagate::kinetic::proto::Command_Status_StatusCode::Command_Status_StatusCode_NESTED_OPERATION_ERRORS:
            return "Nested Operation Errors";
        case com::seagate::kinetic::proto::Command_Status_StatusCode::Command_Status_StatusCode_DEVICE_LOCKED:
            return "Device Locked";
        case com::seagate::kinetic::proto::Command_Status_StatusCode::Command_Status_StatusCode_DEVICE_ALREADY_UNLOCKED:
            return "Device Already Unlocked";
        case com::seagate::kinetic::proto::Command_Status_StatusCode::Command_Status_StatusCode_CONNECTION_TERMINATED:
            return "Connection Terminated";
        case com::seagate::kinetic::proto::Command_Status_StatusCode::Command_Status_StatusCode_INVALID_BATCH:
            return "Invalid Batch";
        default:
            return "Unknown Status Code (" + ::toString<uint32_t>(statusCode) + ")";
    }
}

