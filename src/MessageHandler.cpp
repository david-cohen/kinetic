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
#include <set>
#include <list>
#include <string>
#include "Server.hpp"
#include "Logger.hpp"
#include "KineticLog.hpp"
#include "Connection.hpp"
#include "Transaction.hpp"
#include "GlobalConfig.hpp"
#include "AccessControl.hpp"
#include "OperationInfo.hpp"
#include "KineticMessage.hpp"
#include "MessageHandler.hpp"
#include "MessageException.hpp"
#include "MessageStatistics.hpp"

/*
 * Used Namespace Members
 */
using com::seagate::kinetic::proto::Command;
using com::seagate::kinetic::proto::Command_Batch;
using com::seagate::kinetic::proto::Command_Header;
using com::seagate::kinetic::proto::Command_GetLog;
using com::seagate::kinetic::proto::Command_GetLog_Type;
using com::seagate::kinetic::proto::Command_KeyValue;
using com::seagate::kinetic::proto::Command_Range;
using com::seagate::kinetic::proto::Command_Setup;
using com::seagate::kinetic::proto::Command_Security;
using com::seagate::kinetic::proto::Command_Security_ACL;
using com::seagate::kinetic::proto::Command_Security_ACL_Scope;
using com::seagate::kinetic::proto::Command_Status;
using com::seagate::kinetic::proto::Command_GetLog_Type_STATISTICS;
using com::seagate::kinetic::proto::Command_GetLog_Type_CONFIGURATION;
using com::seagate::kinetic::proto::Command_GetLog_Type_CAPACITIES;
using com::seagate::kinetic::proto::Command_GetLog_Type_TEMPERATURES;
using com::seagate::kinetic::proto::Command_GetLog_Type_UTILIZATIONS;
using com::seagate::kinetic::proto::Command_GetLog_Type_MESSAGES;
using com::seagate::kinetic::proto::Command_GetLog_Type_LIMITS;
using com::seagate::kinetic::proto::Command_GetLog_Type_DEVICE;
using com::seagate::kinetic::proto::Command_MessageType_PUT;
using com::seagate::kinetic::proto::Command_MessageType_GET;
using com::seagate::kinetic::proto::Command_MessageType_GETNEXT;
using com::seagate::kinetic::proto::Command_MessageType_GETPREVIOUS;
using com::seagate::kinetic::proto::Command_MessageType_GETVERSION;
using com::seagate::kinetic::proto::Command_MessageType_GETKEYRANGE;
using com::seagate::kinetic::proto::Command_MessageType_DELETE;
using com::seagate::kinetic::proto::Command_MessageType_SETUP;
using com::seagate::kinetic::proto::Command_MessageType_GETLOG;
using com::seagate::kinetic::proto::Command_MessageType_SECURITY;
using com::seagate::kinetic::proto::Command_MessageType_PEER2PEERPUSH;
using com::seagate::kinetic::proto::Command_MessageType_NOOP;
using com::seagate::kinetic::proto::Command_MessageType_PINOP;
using com::seagate::kinetic::proto::Command_MessageType_MEDIASCAN;
using com::seagate::kinetic::proto::Command_MessageType_MEDIAOPTIMIZE;
using com::seagate::kinetic::proto::Command_MessageType_START_BATCH;
using com::seagate::kinetic::proto::Command_MessageType_END_BATCH;
using com::seagate::kinetic::proto::Command_MessageType_ABORT_BATCH;
using com::seagate::kinetic::proto::Command_MessageType_PUT_RESPONSE;
using com::seagate::kinetic::proto::Command_MessageType_FLUSHALLDATA;
using com::seagate::kinetic::proto::Command_MessageType_GET_RESPONSE;
using com::seagate::kinetic::proto::Command_MessageType_GETNEXT_RESPONSE;
using com::seagate::kinetic::proto::Command_MessageType_GETPREVIOUS_RESPONSE;
using com::seagate::kinetic::proto::Command_MessageType_GETVERSION_RESPONSE;
using com::seagate::kinetic::proto::Command_MessageType_GETKEYRANGE_RESPONSE;
using com::seagate::kinetic::proto::Command_MessageType_DELETE_RESPONSE;
using com::seagate::kinetic::proto::Command_MessageType_SETUP_RESPONSE;
using com::seagate::kinetic::proto::Command_MessageType_GETLOG_RESPONSE;
using com::seagate::kinetic::proto::Command_MessageType_SECURITY_RESPONSE;
using com::seagate::kinetic::proto::Command_MessageType_PEER2PEERPUSH_RESPONSE;
using com::seagate::kinetic::proto::Command_MessageType_NOOP_RESPONSE;
using com::seagate::kinetic::proto::Command_MessageType_PINOP_RESPONSE;
using com::seagate::kinetic::proto::Command_MessageType_FLUSHALLDATA_RESPONSE;
using com::seagate::kinetic::proto::Command_MessageType_INVALID_MESSAGE_TYPE;
using com::seagate::kinetic::proto::Command_PinOperation_PinOpType_LOCK_PINOP;
using com::seagate::kinetic::proto::Command_PinOperation_PinOpType_UNLOCK_PINOP;
using com::seagate::kinetic::proto::Command_PinOperation_PinOpType_ERASE_PINOP;
using com::seagate::kinetic::proto::Command_PinOperation_PinOpType_SECURE_ERASE_PINOP;
using com::seagate::kinetic::proto::Command_Security_ACL_HMACAlgorithm_HmacSHA1;
using com::seagate::kinetic::proto::Command_Status_StatusCode;
using com::seagate::kinetic::proto::Command_Status_StatusCode_SUCCESS;
using com::seagate::kinetic::proto::Command_Status_StatusCode_NOT_AUTHORIZED;
using com::seagate::kinetic::proto::Command_Status_StatusCode_VERSION_FAILURE;
using com::seagate::kinetic::proto::Command_Status_StatusCode_INTERNAL_ERROR;
using com::seagate::kinetic::proto::Command_Status_StatusCode_INVALID_REQUEST;
using com::seagate::kinetic::proto::Command_Status_StatusCode_INVALID_BATCH;
using com::seagate::kinetic::proto::Command_Status_StatusCode_HEADER_REQUIRED;
using com::seagate::kinetic::proto::Command_Status_StatusCode_HMAC_FAILURE;
using com::seagate::kinetic::proto::Command_Status_StatusCode_DEVICE_LOCKED;
using com::seagate::kinetic::proto::Message_AuthType_HMACAUTH;
using com::seagate::kinetic::proto::Message_AuthType_PINAUTH;
using com::seagate::kinetic::proto::Message_AuthType_UNSOLICITEDSTATUS;

/*
 * Private Data Objects
 */
static const int DISPATCH_TABLE_SIZE = 24;
static OperationInfo dispatchTable[DISPATCH_TABLE_SIZE] = {
//    Request Type                              Operation Type       Function Handler                             Involves Key
    { Command_MessageType_INVALID_MESSAGE_TYPE, Operation::INVALID,  &MessageHandler::processInvalidRequest,       false },
    { Command_MessageType_GET,                  Operation::READ,     &MessageHandler::processGetRequest,           true  },
    { Command_MessageType_PUT,                  Operation::WRITE,    &MessageHandler::processPutRequest,           true  },
    { Command_MessageType_DELETE,               Operation::DELETE,   &MessageHandler::processDeleteRequest,        true  },
    { Command_MessageType_GETNEXT,              Operation::READ,     &MessageHandler::processGetNextRequest,       false },
    { Command_MessageType_GETPREVIOUS,          Operation::READ,     &MessageHandler::processGetPreviousRequest,   false },
    { Command_MessageType_GETKEYRANGE,          Operation::RANGE,    &MessageHandler::processGetKeyRangeRequest,   false },
    { Command_MessageType_INVALID_MESSAGE_TYPE, Operation::INVALID,  &MessageHandler::processInvalidRequest,       false },
    { Command_MessageType_GETVERSION,           Operation::READ,     &MessageHandler::processGetVersionRequest,    true  },
    { Command_MessageType_INVALID_MESSAGE_TYPE, Operation::INVALID,  &MessageHandler::processInvalidRequest,       false },
    { Command_MessageType_INVALID_MESSAGE_TYPE, Operation::INVALID,  &MessageHandler::processInvalidRequest,       false },
    { Command_MessageType_SETUP,                Operation::SETUP,    &MessageHandler::processSetupRequest,         false },
    { Command_MessageType_GETLOG,               Operation::GETLOG,   &MessageHandler::processGetLogRequest,        false },
    { Command_MessageType_SECURITY,             Operation::SECURITY, &MessageHandler::processSecurityRequest,      false },
    { Command_MessageType_PEER2PEERPUSH,        Operation::P2POP,    &MessageHandler::processP2pPushRequest,       false },
    { Command_MessageType_NOOP,                 Operation::INVALID,  &MessageHandler::processNoopRequest,          false },
    { Command_MessageType_FLUSHALLDATA,         Operation::INVALID,  &MessageHandler::processFlushRequest,         false },
    { Command_MessageType_INVALID_MESSAGE_TYPE, Operation::INVALID,  &MessageHandler::processInvalidRequest,       false },
    { Command_MessageType_PINOP,                Operation::INVALID,  &MessageHandler::processPinOpRequest,         false },
    { Command_MessageType_MEDIASCAN,            Operation::RANGE,    &MessageHandler::processInvalidRequest,       false },
    { Command_MessageType_MEDIAOPTIMIZE,        Operation::RANGE,    &MessageHandler::processOptimizeMediaRequest, false },
    { Command_MessageType_START_BATCH,          Operation::INVALID,  &MessageHandler::processStartBatchRequest,    false },
    { Command_MessageType_END_BATCH,            Operation::INVALID,  &MessageHandler::processEndBatchRequest,      false },
    { Command_MessageType_ABORT_BATCH,          Operation::INVALID,  &MessageHandler::processAbortBatchRequest,    false },
};

/**
 * Initializes the message handler with connection specific information.
 */
MessageHandler::MessageHandler(Connection* const connection)
    : m_connection(connection), m_objectStore(connection->server()->objectStore()),
      m_serverSettings(connection->server()->settings()), m_messageStatistics(connection->server()->messageStatistics()) {
}

/**
 * Processes the Kinetic request.
 *
 * @param transaction.request   the request message to be processed
 */
void MessageHandler::processRequest(Transaction* const transaction) {
    try {
        const Command_Header& requestHeader = transaction->request()->command()->header();
        Command_Header* responseHeader = transaction->response().mutable_command()->mutable_header();
        responseHeader->set_acksequence(requestHeader.sequence());

        uint32_t dispatchTableIndex = messageTypeToIndex(requestHeader.messagetype());

        if (dispatchTableIndex >= DISPATCH_TABLE_SIZE)
            throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Unsupported message type");

        OperationInfo& operationInfo = dispatchTable[dispatchTableIndex];
        responseHeader->set_messagetype(operationInfo.responseType());

        if (transaction->request()->authtype() != operationInfo.requiredAuthenticationType())
            throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Incorrect authentication type");

        if (requestHeader.messagetype() != Command_MessageType_PINOP)
            transaction->setAccessControl(m_serverSettings.accessControl(transaction->request()->hmacauth().identity()));

        /*
         * Verify that the cluster version is set and correct (for non-pinauth requests, which
         * doesn't require the cluster version).
         *
         * Note: the smoke test expected the "CLUSTER_VERSION_FAILURE" text.
         */
        if (transaction->request()->authtype() != Message_AuthType_PINAUTH) {
            if (requestHeader.clusterversion() != m_serverSettings.clusterVersion()) {
                throw MessageException(Command_Status_StatusCode_VERSION_FAILURE, "CLUSTER_VERSION_FAILURE");
            }
        }

        if (requestHeader.connectionid() != m_connection->connectionId())
            throw MessageException(Command_Status_StatusCode_VERSION_FAILURE, "Incorrect Connection ID");

        /*
         * Next, validate the contents of the header.
         */
        if (!m_connection->processedFirstRequest())
            m_connection->setProcessedFirstRequest(true);

        else if (requestHeader.sequence() <= m_connection->previousSequence())
            throw MessageException(Command_Status_StatusCode_VERSION_FAILURE, "Invalid Sequence Number");

        m_connection->setPreviousSequence(requestHeader.sequence());

        /*
         * PIN operations don't require specified access control, they just need to specify the PIN.
         */
        if (transaction->request()->authtype() == Message_AuthType_HMACAUTH) {
            if (!transaction->hasAccessControl()) {
                throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Identity does not have access");
            }

            std::string hmacKey = transaction->accessControl()->hmacKey();
            if (!transaction->request()->validateHmac(hmacKey, transaction->accessControl()->hmacAlgorithm())) {
                throw MessageException(Command_Status_StatusCode_HMAC_FAILURE, "Incorrect HMAC");
            }

            /*
             * Access checks
             */
            if (transaction->accessControl()->tlsRequired(operationInfo.operation()) && (m_connection->security() != Security::SSL))
                throw MessageException(Command_Status_StatusCode_NOT_AUTHORIZED, "Requires TLS connection for request");

            /*
             * Note: the smoke test expected the "permission denied" test.
             */
            if (!transaction->accessControl()->operationPermitted(operationInfo.operation(), operationInfo.operationInvolvesKey(),
                    transaction->request()->command()->body())) {
                throw MessageException(Command_Status_StatusCode_NOT_AUTHORIZED, "permission denied");
            }
        }

        if (m_serverSettings.locked()
                && !((requestHeader.messagetype() == Command_MessageType_PINOP)
                     && ((transaction->request()->command()->body().pinop().pinoptype() == Command_PinOperation_PinOpType_UNLOCK_PINOP)
                         || (transaction->request()->command()->body().pinop().pinoptype() == Command_PinOperation_PinOpType_LOCK_PINOP)))) {
            throw MessageException(Command_Status_StatusCode_DEVICE_LOCKED);
        }

        /*
         * Set the status to success, change it to failure if unsuccessful.
         */
        transaction->response().mutable_command()->mutable_status()->set_code(Command_Status_StatusCode_SUCCESS);

        if (!transaction->request()->has_command())
            throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Missing command2");

        if (!transaction->request()->command()->has_header())
            throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Missing header2");

        (this->*operationInfo.processRequest())(transaction);
    }
    catch (MessageException& messageException) {
        Command_Status* status = transaction->response().mutable_command()->mutable_status();
        status->set_code(messageException.statusCode());
        status->set_statusmessage(messageException.statusMessage());
    }
    catch (std::exception& ex) {
        LOG(ERROR) << "MessageHandler::processRequest exception: " << ex.what();
        Command_Status* status = transaction->response().mutable_command()->mutable_status();
        status->set_code(Command_Status_StatusCode_INTERNAL_ERROR);
        status->set_statusmessage(std::string(ex.what()));
    }
    catch (...) {
        LOG(ERROR) << "MessageHandler::processRequest unknown exception";
        Command_Status* status = transaction->response().mutable_command()->mutable_status();
        status->set_code(Command_Status_StatusCode_INTERNAL_ERROR);
        status->set_statusmessage("Unexpected exception");
    }

    if (!transaction->hasResponse())
        return;

    if (transaction->hasAccessControl()) {
        transaction->request()->set_authtype(Message_AuthType_HMACAUTH);
        transaction->response().mutable_hmacauth()->set_identity(transaction->accessControl()->identity());
    }

    transaction->response().build_commandbytes();

    if (transaction->hasAccessControl())
        transaction->response().generateHmac(transaction->accessControl()->hmacKey(), transaction->accessControl()->hmacAlgorithm());

    m_messageStatistics.update(*transaction->request(), transaction->response());
}

/**
 * Processes a setup request.  A setup request is used perform a secure erase, download a new
 * firmware image, or update setup parameters (cluster version and/or personal ID number). Although
 * syntactically more than one of these operations can be requested at once, only one is permitted
 * per request.  All operations require the device's PIN to be specified in order to perform
 * operation. Currently, if no operations are requested, the request will complete successfully
 * (that may change since the Kinetic documentation doesn't cover that scenario).
 *
 * @param   transaction     Contains the request and response message
 */
void MessageHandler::processSetupRequest(Transaction* const transaction) {
    /*
     * Ensure that the message contains the setup parameters, the correctly PIN was specified, and
     * that only one operation is being request.  If any of those conditions are not true, fail the
     * request.
     */
    if (!transaction->request()->command()->body().has_setup())
        throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Setup parameters not specified");

    const Command_Setup& setupRequest(transaction->request()->command()->body().setup());

    uint32_t operationCount(0);
    if (setupRequest.firmwaredownload())
        operationCount++;
    if (setupRequest.has_newclusterversion())
        operationCount++;

    if (operationCount > 1)
        throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "More than one setup operation requested at once");

    /*
     * If a firmware image was to be downloaded, verify that a valid image was provided.  If not,
     * fail the request.  If so, record that a firmware image is to be saved.
     */
    if (setupRequest.firmwaredownload()) {
        if (transaction->request()->value().empty())
            throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Invalid firmware image (empty)");
    }

    /*
     * If the cluster version was specified, verify that its a legal value (not zero).  If not,
     * fail the request.  If so, record that the cluster version is to be set after all the
     * setup parameters have been validated.
     */
    if (setupRequest.has_newclusterversion()) {
        m_serverSettings.setClusterVersion(setupRequest.newclusterversion());
        m_serverSettings.save();
    }
}

/**
 *  Processes a security request.  The security message is used to change one of the following
 *  settings:
 *      The erase PIN
 *      The lock PIN
 *      The Access control lists (ACLs)
 *
 *  Only one of those settings change be changed per message.  The Kinetic Protocol supports
 *  restricting the operations a requester (identity) can perform using ACLs.  Below is a list of
 *  their values.
 *
 *  ACL(s)
 *      Identity:         The ID of the requester that the access control is for
 *      Key:              The shared secret between the client and the device that is used to sign requests (using HMAC)
 *      HMAC Algorithm    The algorithm used to generate the HMAC for the requester's messages
 *      Scope(s)          An ACL can have multiple scopes
 *          Permissions   Scopes grant a set of permissions to the identity associated with the ACL
 *                        The permissions are: READ, WRITE, DELETE, RANGE, SETUP, P2POP, GETLOG, SECURITY
 *          TLS Required  Indicates if TLS must be used for the associated permissions
 *          Offset        Offset and Value are optional and are used to further restrict which keys the Scope applies to.
 *          Value         When specified, the permission will only apply to keys that match the value at the given offset.
 *
 * @param   transaction     Contains the request and response message
 */
void MessageHandler::processSecurityRequest(Transaction* const transaction) {
    try {
        /*
         * Verify that the message contains security parameters and does not contain new values for
         * more that one setting (the erase PIN, the lock PIN, or the ACLs), which is not
         * permitted.
         */
        if (!transaction->request()->command()->body().has_security()) {
            throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Missing security parameters");
        }
        const Command_Security& security = transaction->request()->command()->body().security();

        int32_t operationCount(0);
        if (security.acl_size() > 0)
            operationCount++;

        if (security.has_newerasepin() || security.has_olderasepin())
            operationCount++;

        if (security.has_newlockpin() || security.has_oldlockpin())
            operationCount++;

        if (operationCount > 1)
            throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Contains more than one security component change");

        /*
         * If the erase PIN is specified, set the erase PIN to its new value.
         */
        if (security.has_newerasepin() || security.has_olderasepin()) {
            if (!m_serverSettings.erasePin().empty() && (m_serverSettings.erasePin().compare(security.olderasepin()) != 0))
                throw MessageException(Command_Status_StatusCode_NOT_AUTHORIZED, "Invalid old lock pin");

            if (security.newerasepin().length() > globalConfig.maxPinSize())
                throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "New PIN exceeds the maximum size");

            m_serverSettings.setErasePin(security.newerasepin());
        }

        /*
         * If the lock PIN is specified, set the lock PIN to its new value/
         */
        else if (security.has_newlockpin() || security.has_oldlockpin()) {
            if (!m_serverSettings.lockPin().empty() && ((m_serverSettings.lockPin().compare(security.oldlockpin()) != 0)))
                throw MessageException(Command_Status_StatusCode_NOT_AUTHORIZED, "Invalid old erase pin");

            if (security.newlockpin().length() > globalConfig.maxPinSize())
                throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "New PIN exceeds the maximum size");

            m_serverSettings.setLockPin(security.newlockpin());
        }

        else if (security.acl_size() > 0) {
            /*
             * Verify that the maximum number of identities has not been exceeded.  If it has,
             * fail the message.
             */
            std::set<int64_t> identitySet;
            for (auto aclIndex = 0; aclIndex < security.acl_size(); aclIndex++) {
                const Command_Security_ACL& acl = security.acl(aclIndex);
                if (acl.has_identity() && (acl.identity() < 0))
                    identitySet.insert(acl.identity());
            }

            if (identitySet.size() > globalConfig.maxIdentityCount())
                throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Exceeded maximum number of identities");

            std::list<AccessControlPtr> accessControlList;

            for (auto aclIndex = 0; aclIndex < security.acl_size(); aclIndex++) {
                const Command_Security_ACL& acl = security.acl(aclIndex);

                if (!acl.has_identity()) {
                    throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Missing security identity");
                }
                if (!acl.has_key() || (acl.key().size() == 0)) {
                    throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Missing security key");
                }
                if (!acl.has_hmacalgorithm()) {
                    throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Missing security HMAC algorithm");
                }
                if (acl.hmacalgorithm() != Command_Security_ACL_HMACAlgorithm_HmacSHA1) {
                    throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Invalid security HMAC algorithm");
                }
                if (acl.scope_size() == 0) {
                    throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Missing security scope");
                }
                if (acl.identity() < 0) {
                    throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Identity can not be less than zero");
                }

                int64_t identity(acl.identity());
                std::string hmacKey(acl.key());
                HmacAlgorithm hmacAlgorithm(AccessScope::fromMessageFormat(acl.hmacalgorithm()));
                AccessScopeList scopeList;

                for (auto scopeIndex = 0; scopeIndex < acl.scope_size(); scopeIndex++) {
                    const Command_Security_ACL_Scope& aclScope = acl.scope(scopeIndex);
                    if (aclScope.permission_size() == 0) {
                        throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Missing security scope permission");
                    }

                    if (aclScope.offset() < 0)
                        throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Offset can not be less than zero");

                    bool tlsRequired(false);
                    uint32_t keySubstringOffset(0);
                    std::string keySubString("");
                    if (aclScope.has_tlsrequired())
                        tlsRequired = aclScope.tlsrequired();
                    if (aclScope.has_value()) {
                        keySubString = aclScope.value();
                        if (aclScope.has_offset())
                            keySubstringOffset = aclScope.offset();
                    }

                    OperationSizedBoolArray operationArray;
                    operationArray.fill(false);
                    for (auto permissionIndex = 0; permissionIndex < aclScope.permission_size(); permissionIndex++) {
                        Operation operation = AccessScope::fromMessageFormat(aclScope.permission(permissionIndex));
                        if (OPERATION_TO_UINT32(operation) < operationArray.size())
                            operationArray[OPERATION_TO_UINT32(operation)] = true;
                    }
                    AccessScope accessScope(tlsRequired, keySubString, keySubstringOffset, operationArray);
                    scopeList.push_back(accessScope);
                }
                AccessControlPtr accessControl(new AccessControl(identity, hmacKey, hmacAlgorithm, scopeList));
                accessControlList.push_back(accessControl);
            }
            m_serverSettings.updateAccessControl(accessControlList);
        }

        /*
         * Save the new setting and indicate that the operation was performed successfully.
         */
        m_serverSettings.save();
    }
    catch (MessageException& messageException) {
        Command_Status* status = transaction->response().mutable_command()->mutable_status();
        status->set_code(messageException.statusCode());
        status->set_statusmessage(messageException.statusMessage());
    }
}

/**
 * Processes a get log request.
 *
 * @param   transaction     Contains the request and response message
 */
void MessageHandler::processGetLogRequest(Transaction* const transaction) {
    const Command_GetLog& getLogRequest = transaction->request()->command()->body().getlog();
    Command_GetLog* getLogResponse = transaction->response().mutable_command()->mutable_body()->mutable_getlog();

    /*
     * If no log types were specified, then send all types.
     */
    std::set<Command_GetLog_Type> logTypeSet;
    if (getLogRequest.types_size() == 0)
        logTypeSet = globalConfig.defaultLogTypes();

    /*
     * Remove any duplicate log types by copying them to a set (which doesn't permit duplicates).
     * Then, get the information for each requested log type.
     */
    else {
        for (int32_t index = 0; index < getLogRequest.types_size(); index++)
            logTypeSet.insert(getLogRequest.types(index));
    }

    for (auto logType : logTypeSet) {
        getLogResponse->add_types(logType);
        switch (logType) {
            case Command_GetLog_Type_STATISTICS:
                KineticLog::getStatistics(getLogResponse, m_messageStatistics);
                break;
            case Command_GetLog_Type_CONFIGURATION:
                KineticLog::getConfiguration(getLogResponse);
                break;
            case Command_GetLog_Type_CAPACITIES:
                KineticLog::getCapacities(getLogResponse);
                break;
            case Command_GetLog_Type_TEMPERATURES:
                KineticLog::getTemperatures(getLogResponse);
                break;
            case Command_GetLog_Type_UTILIZATIONS:
                KineticLog::getUtilizations(getLogResponse);
                break;
            case Command_GetLog_Type_MESSAGES:
                KineticLog::getMessage(getLogResponse);
                break;
            case Command_GetLog_Type_LIMITS:
                KineticLog::getLimits(getLogResponse);
                break;
            case Command_GetLog_Type_DEVICE:
                KineticLog::getDevice(getLogRequest, transaction->response().value());
                break;
            default:
                throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Unsupported log type specified");
        }
    }
}

/**
 * Processes a put request.  The specified entry will only be put if the specified version
 * matches the entry's current version unless the force option is specified (in which case a
 * version is not given) or the entry isn't already in the database and no existing version is
 * given. The put request may specify an optional persistence option (indicating write-back or
 * write-through).
 *
 * @param   transaction     Contains the request and response message
 */
void MessageHandler::processPutRequest(Transaction* const transaction) {
    /*
     * If the request is a part of batch, defer processing it until the end batch command has been
     * received.
     */
    KineticMessage* request = transaction->request();
    if (request->command()->header().has_batchid()) {
        KineticMessageListPtr batchList = m_connection->getBatchList(request->command()->header().batchid());

        if (batchList == nullptr)
            throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "No batch with specified Batch ID");

        /*
         * After adding the request to the batch list, detach it from the transaction so it won't be
         * freed.
         */
        batchList->push_back(request);
        transaction->detachRequest();
        transaction->setNoResponse();
        return;
    }

    const Command_KeyValue& params = request->command()->body().keyvalue();

    /*
     * Validate the parameters.
     */
    if (params.key().size() > globalConfig.maxKeySize())
        throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Key size too large");

    if (params.newversion().size() > globalConfig.maxVersionSize())
        throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Version size too large");

    if (params.tag().size() > globalConfig.maxTagSize())
        throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Tag size too large");

    /*
     * Perform the put operation.  If an error is encountered, the function will throw and will be
     * caught by the calling function.
     */
    m_objectStore->putEntry(params, request->value());
}

/**
 * Processes a get request, which can be for the entire contents of the database entry or for just
 * the entry's metadata.
 *
 * @param   transaction     Contains the request and response message
 */
void MessageHandler::processGetRequest(Transaction* const transaction) {
    const Command_KeyValue& keyValue = transaction->request()->command()->body().keyvalue();

    if (!keyValue.metadataonly())
        m_objectStore->getEntry(keyValue.key(), transaction->response().value(),
                                transaction->response().mutable_command()->mutable_body()->mutable_keyvalue());
    else
        m_objectStore->getEntryMetadata(keyValue.key(), false, transaction->response().mutable_command()->mutable_body()->mutable_keyvalue());
}
/**
 * Processes a get version request, which allow obtains the version of the entry.
 *
 * @param   transaction     Contains the request and response message
 */
void MessageHandler::processGetVersionRequest(Transaction* const transaction) {
    m_objectStore->getEntryMetadata(transaction->request()->command()->body().keyvalue().key(), true,
                                    transaction->response().mutable_command()->mutable_body()->mutable_keyvalue());
}

/**
 * Processes a get next request.  The database is sorted in lexicographical order, so an attempt
 * will be made to get the entry whose key following the specified key.
 *
 * @param   transaction     Contains the request and response message
 *
 * @throws  NOT_FOUND if the entry was not found in the database
 * @throws  NOT_AUTHORIZED if the user does not have permission to read the entry based on its key
 */
void MessageHandler::processGetNextRequest(Transaction* const transaction) {
    /*
     * Attempt to get the entry that follows the specified key.  If there is not following entry,
     * the NOT_FOUND exception will be thrown.
     */
    Command_KeyValue* returnMetadata = transaction->response().mutable_command()->mutable_body()->mutable_keyvalue();
    m_objectStore->getNextEntry(transaction->request()->command()->body().keyvalue().key(), transaction->response().value(), returnMetadata);

    /*
     * If the entry was found, a check must be performed to ensure the user has access to the entry
     * based on the key (because a user can be limited to accessing only specified key ranges).
     *
     * Note: the conformance test expects the "permission denied text.
     */
    if ((transaction->hasAccessControl()) && !transaction->accessControl()->permissionToRead(returnMetadata->key())) {
        throw MessageException(Command_Status_StatusCode_NOT_AUTHORIZED, "permission denied");
    }
}

/**
 * Processes a get previous request.  The database is sorted in lexicographical order, so an attempt
 * will be made to get the entry whose key precedes the specified key.
 *
 * @param   transaction     Contains the request and response message
 *
 * @throws  NOT_FOUND if the entry was not found in the database
 * @throws  NOT_AUTHORIZED if the user does not have permission to read the entry based on its key
 */
void MessageHandler::processGetPreviousRequest(Transaction* const transaction) {
    /*
     * Attempt to get the entry that precedes the specified key.  If there is not following entry,
     * the NOT_FOUND exception will be thrown.
     */
    Command_KeyValue* returnMetadata = transaction->response().mutable_command()->mutable_body()->mutable_keyvalue();
    m_objectStore->getPreviousEntry(transaction->request()->command()->body().keyvalue().key(), transaction->response().value(), returnMetadata);

    /*
     * If the entry was found, a check must be performed to ensure the user has access to the entry
     * based on the key (because a user can be limited to accessing only specified key ranges).
     *
     * Note: the conformance test expects the "permission denied text.
     */
    if ((transaction->hasAccessControl()) && !transaction->accessControl()->permissionToRead(returnMetadata->key())) {
        throw MessageException(Command_Status_StatusCode_NOT_AUTHORIZED, "permission denied");
    }
}

/**
 * Processes  a get key range request.
 *
 * @param   transaction     Contains the request and response message
 */
void
MessageHandler::processGetKeyRangeRequest(Transaction* const transaction) {
    const Command_Range& params(transaction->request()->command()->body().range());

    Command_Range* response(transaction->response().mutable_command()->mutable_body()->mutable_range());

    if (!params.reverse())
        m_objectStore->getKeyRange(params, transaction->accessControl(), response);
    else
        m_objectStore->getKeyRangeReversed(params, transaction->accessControl(), response);
}

/**
 * Processes a delete request.  The entry associated with the specified key will only be deleted if
 * the specified version matches the entry's current version unless the force option is specified
 * (in which case a version is not given).  The delete request may specify an optional persistence
 * option (indicating write-back or write-through).
 *
 * @param   transaction     Contains the request and response message
 */
void MessageHandler::processDeleteRequest(Transaction* const transaction) {
    KineticMessage* request = transaction->request();
    if (request->command()->header().has_batchid()) {
        KineticMessageListPtr batchList = m_connection->getBatchList(request->command()->header().batchid());

        if (batchList == nullptr)
            throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "No batch with specified Batch ID");

        /*
         * After adding the request to the batch list, detach it from the transaction so it won't be
         * freed.
         */
        batchList->push_back(request);
        transaction->detachRequest();
        transaction->setNoResponse();
        return;
    }

    m_objectStore->deleteEntry(request->command()->body().keyvalue());
}

/**
 * Processes a flush request.
 *
 * @param   transaction     Contains the request and response message
 */
void MessageHandler::processFlushRequest(Transaction* const transaction) {
    static_cast<void>(transaction);
    m_objectStore->flush();
}

/**
 * Processes a no-op request.
 *
 * @param   transaction     Contains the request and response message
 */
void MessageHandler::processNoopRequest(Transaction* const transaction) {
    static_cast<void>(transaction);
}

/**
 * Processes a PIN operation request.
 *
 * @param   transaction     Contains the request and response message
 */
void MessageHandler::processPinOpRequest(Transaction* const transaction) {
    try {
        if (!transaction->request()->command()->body().has_pinop())
            throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Missing PIN operation parameters");

        switch (transaction->request()->command()->body().pinop().pinoptype()) {
            case Command_PinOperation_PinOpType_LOCK_PINOP:

                if ((!m_serverSettings.lockPin().empty()) && (transaction->request()->pinauth().pin().compare(m_serverSettings.lockPin()) != 0))
                    throw MessageException(Command_Status_StatusCode_NOT_AUTHORIZED, "Incorrect PIN");

                m_serverSettings.setLocked(true);
                break;

            case Command_PinOperation_PinOpType_UNLOCK_PINOP:

                if ((!m_serverSettings.lockPin().empty()) && (transaction->request()->pinauth().pin().compare(m_serverSettings.lockPin()) != 0))
                    throw MessageException(Command_Status_StatusCode_NOT_AUTHORIZED, "Incorrect PIN");

                m_serverSettings.setLocked(false);
                break;

            case Command_PinOperation_PinOpType_ERASE_PINOP:
                if ((!m_serverSettings.erasePin().empty()) && (transaction->request()->pinauth().pin().compare(m_serverSettings.erasePin()) != 0))
                    throw MessageException(Command_Status_StatusCode_NOT_AUTHORIZED, "Incorrect PIN");

                m_objectStore->erase();
                m_serverSettings.setDefaults();
                break;

            case Command_PinOperation_PinOpType_SECURE_ERASE_PINOP:

                if ((!m_serverSettings.erasePin().empty()) && (transaction->request()->pinauth().pin().compare(m_serverSettings.erasePin()) != 0))
                    throw MessageException(Command_Status_StatusCode_NOT_AUTHORIZED, "Incorrect PIN 4");

                m_objectStore->erase();
                m_serverSettings.setDefaults();
                break;

            default:
                throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Unsupported PIN Op Type "
                                       + std::to_string(transaction->request()->command()->body().pinop().pinoptype()));
        }
    }
    catch (MessageException& messageException) {
        throw;
    }
    catch (std::exception& e) {
        throw MessageException(Command_Status_StatusCode_INTERNAL_ERROR, "Exception thrown");
    }
    catch (...) {
        throw MessageException(Command_Status_StatusCode_INTERNAL_ERROR, "Exception thrown");
    }
}

/**
 * Processes an optimize media request.
 *
 * @param   transaction     Contains the request and response message
 */
void MessageHandler::processOptimizeMediaRequest(Transaction* const transaction) {
    static_cast<void>(transaction);
    m_objectStore->optimizeMedia();
}

/**
 * Processes a peer-to-peer request.
 *
 * @param   transaction     Contains the request and response message
 */
void MessageHandler::processP2pPushRequest(Transaction* const transaction) {
    static_cast<void>(transaction);
    throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Request not yet supported");
}

/**
 * Processes an invalid request.
 *
 * @param   transaction     Contains the request and response message
 */
void MessageHandler::processInvalidRequest(Transaction* const transaction) {
    /*
     *  Eliminate the unused args warning.
     */
    static_cast<void>(transaction);

    throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Unsupported message type");
}

/**
 * Processes a start batch request.  The start batch request causes a "batch" with the specified ID
 * to be created.  Then batch commands (put or delete) with the same batch ID will be added to the
 * batch.  When an end batch command with the specified ID is received, all the batched commands
 * will be performed as an atomic operation.  Once the start batch command has reached this point
 * (having gone through header and ACL validation), the only way the request can fail is:
 *     - the maximum number of batches that the device can support have already been reached
 *     - a batch ID was not specified
 *     - the batch ID is already in use
 * If it fails at this point, an unsolicited status and sent and the connection is closed.
 *
 * @param   transaction     Contains the request and response message
 */
void MessageHandler::processStartBatchRequest(Transaction* const transaction) {
    if (m_connection->server()->activeBatchCommands() >= globalConfig.maxBatchCountPerDevice())
        throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Exceeded maximum outstanding batches");

    if (!transaction->request()->command()->header().has_batchid())
        throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Start Batch command missing Batch ID");

    if (!m_connection->createBatchList(transaction->request()->command()->header().batchid()))
        throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Batch ID already in use");
}

/**
 * Processes an end batch request.  Individual batch commands must have their header and access
 * validated when the message is received.  The processing of the put or delete must not be done
 * until the end batch is received.  A failure causes an unsolicited status followed by a
 * connection closure.  Batch jobs support put, put forced, delete, and delete forced.  It looks
 * like there is no persistence option for batch commands, they will always be write-through
 *
 * @param   transaction     Contains the request and response message
 */
void MessageHandler::processEndBatchRequest(Transaction* const transaction) {
    if (!transaction->request()->command()->header().has_batchid())
        throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "End Batch command missing Batch ID");

    /*
     * Handle this differently depending on if it had been aborted (see Kinetic java simulator)
     */
    uint32_t batchId = transaction->request()->command()->header().batchid();
    KineticMessageListPtr batchList = m_connection->getBatchList(batchId);

    if (batchList == nullptr)
        throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "No batch with specified Batch ID");

    Command_Batch* returnBatchInfo(transaction->response().mutable_command()->mutable_body()->mutable_batch());

    returnBatchInfo->set_count(batchList->size());
    for (auto batchRequest : *batchList) {
        if (!transaction->request()->has_command())
            throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Missing command2");

        if (!transaction->request()->command()->has_header())
            throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Missing header2");


        returnBatchInfo->add_sequence(batchRequest->command()->header().sequence());
    }

    BatchInterfacePtr batch(m_objectStore->createBatch());
    for (auto batchRequest : *batchList) {
        try {
            if (batchRequest->command()->header().messagetype() == Command_MessageType_PUT)
                batch->putEntry(batchRequest->command()->body().keyvalue(), batchRequest->value());

            else if (batchRequest->command()->header().messagetype() == Command_MessageType_DELETE)
                batch->deleteEntry(batchRequest->command()->body().keyvalue());
        }
        catch (MessageException& messageException) {
            returnBatchInfo->set_failedsequence(batchRequest->command()->header().sequence());
            Command_Status* status = transaction->response().mutable_command()->mutable_status();
            status->set_code(Command_Status_StatusCode_INVALID_BATCH);
            status->set_statusmessage(messageException.statusMessage());
            m_connection->deleteBatchList(batchId);
            return;
        }
        delete batchRequest;
    }

    batch->commit();
    m_connection->deleteBatchList(batchId);
}

/**
 * Processes an abort batch request.
 *
 * @param   transaction     Contains the request and response message
 */
void MessageHandler::processAbortBatchRequest(Transaction* const transaction) {
    if (!transaction->request()->command()->header().has_batchid())
        throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Abort Batch command missing Batch ID");

    KineticMessageListPtr batchList = m_connection->getBatchList(transaction->request()->command()->header().batchid());
    if (batchList == nullptr) {
        for (auto batchRequest : *batchList)
            delete batchRequest;
    }

    if (!m_connection->deleteBatchList(transaction->request()->command()->header().batchid()))
        throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "No batch with specified Batch ID");
}

/**
 * Build an unsolicited status message (which is sent to the client when a connection is first
 * established.
 *
 * @param connection    Contains connection information needed for the message
 * @param response      The status message to be built
 */
void MessageHandler::buildUnsolicitedStatusMessage(Connection* const connection, KineticMessage& response) {
    response.set_authtype(Message_AuthType_UNSOLICITEDSTATUS);
    Command* const command = response.mutable_command();
    Command_Header* const header = command->mutable_header();
    header->set_connectionid(connection->connectionId());
    header->set_clusterversion(connection->server()->settings().clusterVersion());
    Command_GetLog* getLogResponse = command->mutable_body()->mutable_getlog();
    getLogResponse->add_types(Command_GetLog_Type_CONFIGURATION);
    KineticLog::getConfiguration(getLogResponse);
    getLogResponse->add_types(Command_GetLog_Type_LIMITS);
    KineticLog::getLimits(getLogResponse);
    command->mutable_status()->set_code(Command_Status_StatusCode_SUCCESS);
    response.build_commandbytes();
}

/**
 * Completes the processing of a request that failed due to an error.
 *
 * @param   transaction     Contains the request and response message
 * @param   errorCode       The error code to be set
 * @param   errorMessage    The error message to be set
 */
void MessageHandler::buildResponseWithError(Transaction* const transaction, Command_Status_StatusCode errorCode, const std::string& errorMessage) {
    Command_Status* status = transaction->response().mutable_command()->mutable_status();
    status->set_code(errorCode);
    status->set_statusmessage(errorMessage);

    Command_Header* header = transaction->response().mutable_command()->mutable_header();
    header->set_acksequence(transaction->request()->command()->header().sequence());
    header->set_messagetype(requestToResponseType(transaction->request()->command()->header().messagetype()));

    if ((transaction->request()->authtype() == Message_AuthType_HMACAUTH) && transaction->request()->hmacauth().has_identity()) {
        transaction->setAccessControl(m_serverSettings.accessControl(transaction->request()->hmacauth().identity()));
        if (transaction->hasAccessControl()) {
            transaction->request()->set_authtype(Message_AuthType_HMACAUTH);
            transaction->response().mutable_hmacauth()->set_identity(transaction->accessControl()->identity());
        }
    }
    transaction->response().build_commandbytes();
    if (transaction->hasAccessControl())
        transaction->response().generateHmac(transaction->accessControl()->hmacKey(), transaction->accessControl()->hmacAlgorithm());
    m_messageStatistics.update(*transaction->request(), transaction->response());
}

