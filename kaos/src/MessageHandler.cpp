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

/*
 * Include Files
 */
#include <stdint.h>
#include <string.h>
#include <set>
#include <map>
#include <list>
#include <string>
#include <iostream>
#include <stdexcept>
#include <unordered_set>
#include <unordered_map>
#include "Server.hpp"
#include "Logger.hpp"
#include "Connection.hpp"
#include "Translator.hpp"
#include "Transaction.hpp"
#include "KineticLog.hpp"
#include "ObjectStore.hpp"
#include "GlobalConfig.hpp"
#include "AccessControl.hpp"
#include "OperationInfo.hpp"
#include "KineticMessage.hpp"
#include "MessageHandler.hpp"
#include "MessageException.hpp"
#include "MessageStatistics.hpp"

/*
 * Used Namespaces
 */
using std::set;
using std::map;
using std::list;
using std::string;
using std::unordered_set;
using std::unordered_map;

/*
 * Message Types
 */
using com::seagate::kinetic::proto::Command_MessageType;
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
using com::seagate::kinetic::proto::Command_Status_StatusCode_SUCCESS;
using com::seagate::kinetic::proto::Command_Status_StatusCode_NOT_AUTHORIZED;
using com::seagate::kinetic::proto::Command_Status_StatusCode_VERSION_FAILURE;
using com::seagate::kinetic::proto::Command_Status_StatusCode_INTERNAL_ERROR;
using com::seagate::kinetic::proto::Command_Status_StatusCode_INVALID_REQUEST;
using com::seagate::kinetic::proto::Command_Status_StatusCode_INVALID_BATCH;
using com::seagate::kinetic::proto::Command_Header;
using com::seagate::kinetic::proto::Command_KeyValue;
using com::seagate::kinetic::proto::Command_Status;
using com::seagate::kinetic::proto::Command_GetLog;
using com::seagate::kinetic::proto::Message_AuthType;

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

MessageHandler::MessageHandler(Connection* connection)
    : m_connection(connection), m_objectStore(connection->server()->objectStore()),
      m_serverSettings(connection->server()->settings()), m_messageStatistics(connection->server()->messageStatistics()) {
}

/**
 * Processes the Kinetic request.
 *
 * @param transaction.request   the request message to be processed
 */
void
MessageHandler::processRequest(Transaction* transaction) {

    try {
        /*
         * Verify that the request contains all the required header fields (if not, the verify
         */

        if (!transaction->request->command()->has_header())
            throw MessageException(com::seagate::kinetic::proto::Command_Status_StatusCode_HEADER_REQUIRED, "Command missing Header");

        const Command_Header& requestHeader = transaction->request->command()->header();

        if (!requestHeader.has_sequence())
            throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Header missing Sequence");

        Command_Header* responseHeader = transaction->response->mutable_command()->mutable_header();
        responseHeader->set_acksequence(requestHeader.sequence());

        if (!requestHeader.has_messagetype())
            throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Header missing Message Type");

        uint32_t dispatchTableIndex = messageTypeToIndex(requestHeader.messagetype());

        if (dispatchTableIndex >= DISPATCH_TABLE_SIZE)
            throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Unsupported message type");

        OperationInfo& operationInfo = dispatchTable[dispatchTableIndex];
        responseHeader->set_messagetype(operationInfo.responseType);

        if (transaction->request->authtype() != operationInfo.requiredAuthenticationType)
            throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Incorrect authentication type");

        if ((transaction->request->authtype() == Message_AuthType::Message_AuthType_HMACAUTH) && !transaction->request->hmacauth().has_identity())
            throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Header missing Identity");

        if (requestHeader.messagetype() != Command_MessageType_PINOP)
            transaction->accessControl = m_serverSettings.accessControl(transaction->request->hmacauth().identity());

        /*
         * Verify that the cluster version is set and correct (for non-pinauth requests, which
         * doesn't require the cluster version).
         */
        if (transaction->request->authtype() != Message_AuthType::Message_AuthType_PINAUTH) {
            if (!requestHeader.has_clusterversion()) {
                throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Header missing Cluster Version");
            }
            // Note: the smoke test expected the "CLUSTER_VERSION_FAILURE" test.
            else if (requestHeader.clusterversion() != m_serverSettings.clusterVersion()) {
                throw MessageException(Command_Status_StatusCode_VERSION_FAILURE, "CLUSTER_VERSION_FAILURE");
            }
        }

        if (!requestHeader.has_connectionid())
            throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Header missing Connection ID");

        /*
         * Next, validate the contents of the header.
         */
        if (m_connection->processedFirstRequest()) {
            if (requestHeader.connectionid() != m_connection->connectionId())
                throw MessageException(Command_Status_StatusCode_VERSION_FAILURE, "Incorrect Connection ID");

            if (requestHeader.sequence() <= m_connection->previousSequence())
                throw MessageException(Command_Status_StatusCode_VERSION_FAILURE, "Invalid Sequence Number");
        }
        else {
            m_connection->setProcessedFirstRequest(true);
        }

        m_connection->setPreviousSequence(requestHeader.sequence());

        // PIN operations don't require specified access control, they just need to specify the PIN.

        if (transaction->request->authtype() == Message_AuthType::Message_AuthType_HMACAUTH) {

            if (transaction->accessControl == nullptr) {
                throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Identity does not have access");
            }

            string hmacKey = transaction->accessControl->hmacKey();
            if (!transaction->request->validateHmac(hmacKey, transaction->accessControl->hmacAlgorithm())) {
                throw MessageException(com::seagate::kinetic::proto::Command_Status_StatusCode_HMAC_FAILURE, "Incorrect HMAC");
            }

            /*
             * Access checks
             */
            if (transaction->accessControl->tlsRequired(operationInfo.operation) && (m_connection->security() != Security::SSL))
                throw MessageException(Command_Status_StatusCode_NOT_AUTHORIZED, "Requires TLS connection for request");

            // Note: the smoke test expected the "permission denied" test.
            if (!transaction->accessControl->operationPermitted(operationInfo.operation, operationInfo.operationInvolvesKey, transaction->request->command()->body()))
                throw MessageException(Command_Status_StatusCode_NOT_AUTHORIZED, "permission denied");
        }

        if (m_serverSettings.locked() && !((requestHeader.messagetype() == Command_MessageType_PINOP)
                                           && ((transaction->request->command()->body().pinop().pinoptype() == com::seagate::kinetic::proto::Command_PinOperation_PinOpType_UNLOCK_PINOP)
                                               || (transaction->request->command()->body().pinop().pinoptype() == com::seagate::kinetic::proto::Command_PinOperation_PinOpType_LOCK_PINOP)))) {

            throw MessageException(com::seagate::kinetic::proto::Command_Status_StatusCode_DEVICE_LOCKED);
        }

        (this->*operationInfo.processRequest)(transaction);
    }
    catch (MessageException& messageException) {
        Command_Status* status = transaction->response->mutable_command()->mutable_status();
        status->set_code(messageException.statusCode());
        status->set_statusmessage(messageException.statusMessage());
    }
    catch (std::exception& ex) {
        LOG(ERROR) << "MessageHandler::processRequest exception: " << ex.what();
        Command_Status* status = transaction->response->mutable_command()->mutable_status();
        status->set_code(Command_Status_StatusCode_INTERNAL_ERROR);
        status->set_statusmessage(string(ex.what()));
    }
    catch (...) {
        LOG(ERROR) << "MessageHandler::processRequest unknown exception";
        Command_Status* status = transaction->response->mutable_command()->mutable_status();
        status->set_code(Command_Status_StatusCode_INTERNAL_ERROR);
        status->set_statusmessage("Unexpected exception");
    }

    if (transaction->response == nullptr)
        return;

    if (transaction->accessControl != nullptr) {
        transaction->request->set_authtype(Message_AuthType::Message_AuthType_HMACAUTH);
        transaction->response->mutable_hmacauth()->set_identity(transaction->accessControl->identity());
    }

    transaction->response->build_commandbytes();

    if (transaction->accessControl != nullptr)
        transaction->response->generateHmac(transaction->accessControl->hmacKey(), transaction->accessControl->hmacAlgorithm());

    m_messageStatistics.update(transaction->request, transaction->response);
}

/**
 * Completes the processing of a request that failed due to an error.
 *
 * @param   transaction     Contains the request and response message
 */
void
MessageHandler::processError(Transaction* transaction) {


    try {
        Command_Status* status = transaction->response->mutable_command()->mutable_status();
        Command_Header* responseHeader = transaction->response->mutable_command()->mutable_header();

        if (transaction->request->command()->has_header()) {
            const Command_Header& requestHeader = transaction->request->command()->header();

            if (requestHeader.has_sequence())
                responseHeader->set_acksequence(requestHeader.sequence());

            if (requestHeader.has_messagetype()) {
                uint32_t dispatchTableIndex = messageTypeToIndex(requestHeader.messagetype());

                if (dispatchTableIndex < DISPATCH_TABLE_SIZE) {
                    OperationInfo& operationInfo = dispatchTable[dispatchTableIndex];
                    responseHeader->set_messagetype(operationInfo.responseType);
                }
            }
        }

        if ((transaction->request->authtype() == Message_AuthType::Message_AuthType_HMACAUTH) && transaction->request->hmacauth().has_identity())
            transaction->accessControl = m_serverSettings.accessControl(transaction->request->hmacauth().identity());

        status->set_code(transaction->errorCode);
        status->set_statusmessage(transaction->errorMessage);
    }
    catch (MessageException& messageException) {
        Command_Status* status = transaction->response->mutable_command()->mutable_status();
        status->set_code(messageException.statusCode());
        status->set_statusmessage(messageException.statusMessage());
    }
    if (transaction->accessControl != nullptr) {
        transaction->request->set_authtype(Message_AuthType::Message_AuthType_HMACAUTH);
        transaction->response->mutable_hmacauth()->set_identity(transaction->accessControl->identity());
    }
    transaction->response->build_commandbytes();

    if (transaction->accessControl != nullptr) {
        transaction->response->generateHmac(transaction->accessControl->hmacKey(), transaction->accessControl->hmacAlgorithm());
    }

    m_messageStatistics.update(transaction->request, transaction->response);
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
void
MessageHandler::processSetupRequest(Transaction* transaction) {

    /*
     * Ensure that the message contains the setup parameters, the correctly PIN was specified, and
     * that only one operation is being request.  If any of those conditions are not true, fail the
     * request.
     */
    if (!transaction->request->command()->body().has_setup())
        throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Setup parameters not specified");

    const com::seagate::kinetic::proto::Command_Setup& setupRequest(transaction->request->command()->body().setup());

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
        if (transaction->request->value().empty())  // or not valid
            throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Invalid firmware image (empty)");
    }

    /*
     * If the cluster version and/or personal ID number are to be set, validate the specified
     * values, and if valid, perform the update.  Otherwise, fail the request.
     */

    /*
     * If the cluster version was specified, verify that its a legal value (not zero).  If not,
     * fail the request.  If so, record that the cluster version is to be set after all the
     * setup parameters have been validated.
     */
    if (setupRequest.has_newclusterversion()) {
        /*
            const int64_t ILLEGAL_CLUSTER_VERSION(0L);
            if (request.newclusterversion() == ILLEGAL_CLUSTER_VERSION) {
            status->set_code(Command_Status_StatusCode_INVALID_REQUEST);
            status->set_statusmessage("Invalid Cluster version value (0)");
            return;
            }
        */
        m_serverSettings.setClusterVersion(setupRequest.newclusterversion());
        m_serverSettings.save();
    }

    transaction->response->mutable_command()->mutable_status()->set_code(Command_Status_StatusCode_SUCCESS);
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
void
MessageHandler::processSecurityRequest(Transaction* transaction) {

    try {

        /*
         * Verify that the message contains security parameters and does not contain new values for
         * more that one setting (the erase PIN, the lock PIN, or the ACLs), which is not
         * permitted.
         */
        if (!transaction->request->command()->body().has_security()) {
            throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Missing security parameters");
        }
        const com::seagate::kinetic::proto::Command_Security& security = transaction->request->command()->body().security();

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
                const com::seagate::kinetic::proto::Command_Security_ACL& acl = security.acl(aclIndex);
                if (acl.has_identity() && (acl.identity() < 0))
                    identitySet.insert(acl.identity());
            }

            if (identitySet.size() > globalConfig.maxIdentityCount())
                throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Exceeded maximum number of identities");

            list<AccessControlPtr> accessControlList;

            for (auto aclIndex = 0; aclIndex < security.acl_size(); aclIndex++) {
                const com::seagate::kinetic::proto::Command_Security_ACL& acl = security.acl(aclIndex);

                if (!acl.has_identity()) {
                    throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Missing security identity");
                }
                if (!acl.has_key() || (acl.key().size() == 0)) {
                    throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Missing security key");
                }
                if (!acl.has_hmacalgorithm()) {
                    throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Missing security HMAC algorithm");
                }
                if (acl.hmacalgorithm() != com::seagate::kinetic::proto::Command_Security_ACL_HMACAlgorithm::Command_Security_ACL_HMACAlgorithm_HmacSHA1) {
                    throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Invalid security HMAC algorithm");
                }
                // verified though use of simulator

                if (acl.scope_size() == 0) {
                    throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Missing security scope");
                }
                // found though use of simulator

                if (acl.identity() < 0) {
                    throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Identity can not be less than zero");
                }

                int64_t identity(acl.identity());
                std::string hmacKey(acl.key());
                HmacAlgorithm hmacAlgorithm(Translator::fromMessageFormat(acl.hmacalgorithm()));
                AccessScopeList scopeList;

                for (auto scopeIndex = 0; scopeIndex < acl.scope_size(); scopeIndex++) {
                    const com::seagate::kinetic::proto::Command_Security_ACL_Scope& aclScope = acl.scope(scopeIndex);

                    // verified though use of simulator

                    if (aclScope.permission_size() == 0) {
                        throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Missing security scope permission");
                    }

                    if (aclScope.offset() < 0)
                        throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Offset can not be less than zero");

                    bool tlsRequired(false);
                    uint32_t keySubstringOffset(0);
                    string keySubString("");
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
                        Operation operation = Translator::fromMessageFormat(aclScope.permission(permissionIndex));
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
        transaction->response->mutable_command()->mutable_status()->set_code(Command_Status_StatusCode_SUCCESS);
    }
    catch (MessageException& messageException) {
#if 0
        std::cerr << "Exception processing message " << messageException.statusMessage() << std::endl;
#endif
        Command_Status* status = transaction->response->mutable_command()->mutable_status();
        status->set_code(messageException.statusCode());
        status->set_statusmessage(messageException.statusMessage());
    }
}

/**
 * Processes a get log request.
 *
 * @param   transaction     Contains the request and response message
 */
void
MessageHandler::processGetLogRequest(Transaction* transaction) {

    const Command_GetLog& getLogRequest = transaction->request->command()->body().getlog();
    Command_GetLog* getLogResponse = transaction->response->mutable_command()->mutable_body()->mutable_getlog();

    /*
     * If no log types were specified, then send all types.
     */
    std::set<com::seagate::kinetic::proto::Command_GetLog_Type> logTypeSet;
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
            case com::seagate::kinetic::proto::Command_GetLog_Type_STATISTICS:
                KineticLog::getStatistics(getLogResponse, m_messageStatistics);
                break;
            case com::seagate::kinetic::proto::Command_GetLog_Type_CONFIGURATION:
                KineticLog::getConfiguration(getLogResponse);
                break;
            case com::seagate::kinetic::proto::Command_GetLog_Type_CAPACITIES:
                KineticLog::getCapacities(getLogResponse);
                break;
            case com::seagate::kinetic::proto::Command_GetLog_Type_TEMPERATURES:
                KineticLog::getTemperatures(getLogResponse);
                break;
            case com::seagate::kinetic::proto::Command_GetLog_Type_UTILIZATIONS:
                KineticLog::getUtilizations(getLogResponse);
                break;
            case com::seagate::kinetic::proto::Command_GetLog_Type_MESSAGES:
                KineticLog::getMessage(getLogResponse);
                break;
            case com::seagate::kinetic::proto::Command_GetLog_Type_LIMITS:
                KineticLog::getLimits(getLogResponse);
                break;
            case com::seagate::kinetic::proto::Command_GetLog_Type_DEVICE:
                KineticLog::getDevice(getLogRequest, transaction->response->value());
                break;
            default:
                throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Unsupported log type specified");
        }
    }
    transaction->response->mutable_command()->mutable_status()->set_code(Command_Status_StatusCode_SUCCESS);
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
void
MessageHandler::processPutRequest(Transaction* transaction) {

    /*
     * If the request is a part of batch, defer processing it until the end batch command has been
     * received.
     */
    if (transaction->request->command()->header().has_batchid()) {

        BatchListPtr batchList = m_connection->getBatchList(transaction->request->command()->header().batchid());

        if (batchList == nullptr)
            throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "No batch with specified Batch ID");

        batchList->push_back(transaction->request);
        transaction->response.reset();
        return;
    }

    const Command_KeyValue& params = transaction->request->command()->body().keyvalue();

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
    m_objectStore.putEntry(params, transaction->request->value());
    transaction->response->mutable_command()->mutable_status()->set_code(Command_Status_StatusCode_SUCCESS);
}

/**
 * Processes a get request, which can be for the entire database entry or for just the entry's
 * metadata.
 *
 * @param   transaction     Contains the request and response message
 */
void
MessageHandler::processGetRequest(Transaction* transaction) {

    const Command_KeyValue& request = transaction->request->command()->body().keyvalue();

    if (!request.metadataonly())
        m_objectStore.getEntry(request.key(), transaction->response->value(), transaction->response->mutable_command()->mutable_body()->mutable_keyvalue());
    else
        m_objectStore.getEntryMetadata(request.key(), false, transaction->response->mutable_command()->mutable_body()->mutable_keyvalue());

    transaction->response->mutable_command()->mutable_status()->set_code(Command_Status_StatusCode_SUCCESS);
}
/**
 * Processes a get version request.
 *
 * @param   transaction     Contains the request and response message
 */
void
MessageHandler::processGetVersionRequest(Transaction* transaction) {

    m_objectStore.getEntryMetadata(transaction->request->command()->body().keyvalue().key(), true,
                                   transaction->response->mutable_command()->mutable_body()->mutable_keyvalue());

    transaction->response->mutable_command()->mutable_status()->set_code(Command_Status_StatusCode_SUCCESS);
}

/**
 * Processes a get next request.
 *
 * @param   transaction     Contains the request and response message
 */
void
MessageHandler::processGetNextRequest(Transaction* transaction) {

    Command_KeyValue* returnMetadata = transaction->response->mutable_command()->mutable_body()->mutable_keyvalue();

    m_objectStore.getNextEntry(transaction->request->command()->body().keyvalue().key(), transaction->response->value(), returnMetadata);

    // why is this check here?
    if (transaction->request->authtype() != Message_AuthType::Message_AuthType_HMACAUTH)
        throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Requires HMAC authentication");

    AccessControlPtr accessControl = m_serverSettings.accessControl(transaction->request->hmacauth().identity());

    // Note: the conformance test expects the "permission denied text.
    if ((accessControl != nullptr) && !accessControl->permissionToRead(returnMetadata->key())) {
        throw MessageException(Command_Status_StatusCode_NOT_AUTHORIZED, "permission denied");
    }
    transaction->response->mutable_command()->mutable_status()->set_code(Command_Status_StatusCode_SUCCESS);
}

/**
 * Processes a get previous request.
 *
 * @param   transaction     Contains the request and response message
 */
void
MessageHandler::processGetPreviousRequest(Transaction* transaction) {

    Command_KeyValue* returnMetadata = transaction->response->mutable_command()->mutable_body()->mutable_keyvalue();

    m_objectStore.getPreviousEntry(transaction->request->command()->body().keyvalue().key(), transaction->response->value(), returnMetadata);

    // why is this check here?
    if (transaction->request->authtype() != Message_AuthType::Message_AuthType_HMACAUTH)
        throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Requires HMAC authentication");

    AccessControlPtr accessControl = m_serverSettings.accessControl(transaction->request->hmacauth().identity());

    // Note: the conformance test expects the "permission denied text.
    if ((accessControl != nullptr) && !accessControl->permissionToRead(returnMetadata->key())) {
        throw MessageException(Command_Status_StatusCode_NOT_AUTHORIZED, "permission denied");
    }
    transaction->response->mutable_command()->mutable_status()->set_code(Command_Status_StatusCode_SUCCESS);
}

/**
 * Processes  a get key range request.
 *
 * @param   transaction     Contains the request and response message
 */
void
MessageHandler::processGetKeyRangeRequest(Transaction* transaction) {

    const com::seagate::kinetic::proto::Command_Range& params(transaction->request->command()->body().range());

#if 0
    int32_t maxReturned = params.maxreturned() > globalConfig.maxKeyRangeCount() ? globalConfig.maxKeyRangeCount() : params.maxreturned();
#endif

    // TODO(gballance) - maybe have this checked in initialMessageProcessing
    if (transaction->request->authtype() != Message_AuthType::Message_AuthType_HMACAUTH)
        throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Requires HMAC authentication");

    AccessControlPtr accessControl = m_serverSettings.accessControl(transaction->request->hmacauth().identity());

#if 0  // THIS IS NOT HOW THE OPERATION WORKS
    if (accessControl != nullptr) {
        if ((params.startkey().size() > 0) && !accessControl->permissionToRead(params.startkey())) {
            throw MessageException(Command_Status_StatusCode_NOT_AUTHORIZED, "The user does not have permission");
        }
        if ((params.endkey().size() > 0) && !accessControl->permissionToRead(params.endkey())) {
            throw MessageException(Command_Status_StatusCode_NOT_AUTHORIZED, "The user does not have permission");
        }
    }
#endif

    com::seagate::kinetic::proto::Command_Range* response(transaction->response->mutable_command()->mutable_body()->mutable_range());

    if (!params.reverse())
        m_objectStore.getKeyRange(params, accessControl, response);
    else
        m_objectStore.getKeyRangeReversed(params, accessControl, response);

    transaction->response->mutable_command()->mutable_status()->set_code(Command_Status_StatusCode_SUCCESS);
}

/**
 * Processes a delete request.  The entry associated with the specified key will only be deleted if
 * the specified version matches the entry's current version unless the force option is specified
 * (in which case a version is not given).  The delete request may specify an optional persistence
 * option (indicating write-back or write-through).
 *
 * @param   transaction     Contains the request and response message
 */
void
MessageHandler::processDeleteRequest(Transaction* transaction) {

    if (transaction->request->command()->header().has_batchid()) {

        BatchListPtr batchList = m_connection->getBatchList(transaction->request->command()->header().batchid());

        if (batchList == nullptr)
            throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "No batch with specified Batch ID");

        batchList->push_back(transaction->request);
        transaction->response.reset();
        return;
    }

    m_objectStore.deleteEntry(transaction->request->command()->body().keyvalue());
    transaction->response->mutable_command()->mutable_status()->set_code(Command_Status_StatusCode_SUCCESS);
}

/**
 * Processes a flush request.
 *
 * @param   transaction     Contains the request and response message
 */
void
MessageHandler::processFlushRequest(Transaction* transaction) {

    m_objectStore.flush();
    transaction->response->mutable_command()->mutable_status()->set_code(Command_Status_StatusCode_SUCCESS);
}

/**
 * Processes a no-op request.
 *
 * @param   transaction     Contains the request and response message
 */
void
MessageHandler::processNoopRequest(Transaction* transaction) {

    transaction->response->mutable_command()->mutable_status()->set_code(Command_Status_StatusCode_SUCCESS);
}

/**
 * Processes a PIN operation request.
 *
 * @param   transaction     Contains the request and response message
 */
void
MessageHandler::processPinOpRequest(Transaction* transaction) {

    try {

        if (!transaction->request->command()->body().has_pinop())
            throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Missing PIN operation parameters");

        switch (transaction->request->command()->body().pinop().pinoptype()) {
            case com::seagate::kinetic::proto::Command_PinOperation_PinOpType_LOCK_PINOP:

                if ((!m_serverSettings.lockPin().empty()) && (transaction->request->pinauth().pin().compare(m_serverSettings.lockPin()) != 0))
                    throw MessageException(Command_Status_StatusCode_NOT_AUTHORIZED, "Incorrect PIN");

                m_serverSettings.setLocked(true);
                break;

            case com::seagate::kinetic::proto::Command_PinOperation_PinOpType_UNLOCK_PINOP:

                if ((!m_serverSettings.lockPin().empty()) && (transaction->request->pinauth().pin().compare(m_serverSettings.lockPin()) != 0))
                    throw MessageException(Command_Status_StatusCode_NOT_AUTHORIZED, "Incorrect PIN");

                m_serverSettings.setLocked(false);
                break;

            case com::seagate::kinetic::proto::Command_PinOperation_PinOpType_ERASE_PINOP:
                if ((!m_serverSettings.erasePin().empty()) && (transaction->request->pinauth().pin().compare(m_serverSettings.erasePin()) != 0))
                    throw MessageException(Command_Status_StatusCode_NOT_AUTHORIZED, "Incorrect PIN");

                m_objectStore.erase();
                m_serverSettings.setDefaults();
                break;

            case com::seagate::kinetic::proto::Command_PinOperation_PinOpType_SECURE_ERASE_PINOP:

                if ((!m_serverSettings.erasePin().empty()) && (transaction->request->pinauth().pin().compare(m_serverSettings.erasePin()) != 0))
                    throw MessageException(Command_Status_StatusCode_NOT_AUTHORIZED, "Incorrect PIN 4");

                m_objectStore.erase();
                m_serverSettings.setDefaults();
                break;

            default:
                throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Unsupported PIN Op Type " + toString<uint32_t>(transaction->request->command()->body().pinop().pinoptype()));
        }
    }
    catch (MessageException& messageException) {
        throw messageException;
    }
    catch (std::exception& e) {
        throw MessageException(Command_Status_StatusCode_INTERNAL_ERROR, "Exception thrown");
    }
    catch (...) {
        throw MessageException(Command_Status_StatusCode_INTERNAL_ERROR, "Exception thrown");
    }
    transaction->response->mutable_command()->mutable_status()->set_code(Command_Status_StatusCode_SUCCESS);
}

/**
 * Processes an optimize media request.
 *
 * @param   transaction     Contains the request and response message
 */
void
MessageHandler::processOptimizeMediaRequest(Transaction* transaction) {

    m_objectStore.optimizeMedia();
    transaction->response->mutable_command()->mutable_status()->set_code(Command_Status_StatusCode_SUCCESS);
}

/**
 * Processes a peer-to-peer request.
 *
 * @param   transaction     Contains the request and response message
 */
void
MessageHandler::processP2pPushRequest(Transaction* transaction) {

    static_cast<void>(transaction);
    throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Request not yet supported");
}

/**
 * Processes an invalid request.
 *
 * @param   transaction     Contains the request and response message
 */
void
MessageHandler::processInvalidRequest(Transaction* transaction) {


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
void
MessageHandler::processStartBatchRequest(Transaction* transaction) {

    if (m_connection->server()->batchCount() >= globalConfig.maxBatchCountPerDevice())
        throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Exceeded maximum outstanding batches");

    if (!transaction->request->command()->header().has_batchid())
        throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Start Batch command missing Batch ID");

    if (!m_connection->createBatchList(transaction->request->command()->header().batchid()))
        throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Batch ID already in use");

    transaction->response->mutable_command()->mutable_status()->set_code(Command_Status_StatusCode_SUCCESS);
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
void
MessageHandler::processEndBatchRequest(Transaction* transaction) {

    if (!transaction->request->command()->header().has_batchid())
        throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "End Batch command missing Batch ID");

    /*
     * Handle this differently depending on if it had been aborted (see Kinetic java simulator)
     */
    uint32_t batchId = transaction->request->command()->header().batchid();
    BatchListPtr batchList = m_connection->getBatchList(batchId);

    if (batchList == nullptr)
        throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "No batch with specified Batch ID");

    com::seagate::kinetic::proto::Command_Batch* returnBatchInfo(transaction->response->mutable_command()->mutable_body()->mutable_batch());

    returnBatchInfo->set_count(batchList->size());
    for (auto batchRequest : *batchList)
        returnBatchInfo->add_sequence(batchRequest->command()->header().sequence());

    BatchDescriptor batch;
    for (auto batchRequest : *batchList) {

        try {
            if (batchRequest->command()->header().messagetype() == Command_MessageType_PUT)
                m_objectStore.batchedPutEntry(batch, batchRequest->command()->body().keyvalue(), batchRequest->value());

            else if (batchRequest->command()->header().messagetype() == Command_MessageType_DELETE)
                m_objectStore.batchedDeleteEntry(batch, batchRequest->command()->body().keyvalue());
        }
        catch (MessageException& messageException) {
            returnBatchInfo->set_failedsequence(batchRequest->command()->header().sequence());
            Command_Status* status = transaction->response->mutable_command()->mutable_status();
            status->set_code(Command_Status_StatusCode_INVALID_BATCH);
            status->set_statusmessage(messageException.statusMessage());
            m_connection->deleteBatchList(batchId);
            return;
        }
    }

    m_objectStore.batchCommit(batch);
    m_connection->deleteBatchList(batchId);
    transaction->response->mutable_command()->mutable_status()->set_code(Command_Status_StatusCode_SUCCESS);
}

/**
 * Processes an abort batch request.
 *
 * @param   transaction     Contains the request and response message
 */
void
MessageHandler::processAbortBatchRequest(Transaction* transaction) {

    if (!transaction->request->command()->header().has_batchid())
        throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Abort Batch command missing Batch ID");

    if (!m_connection->deleteBatchList(transaction->request->command()->header().batchid()))
        throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "No batch with specified Batch ID");

    transaction->response->mutable_command()->mutable_status()->set_code(Command_Status_StatusCode_SUCCESS);
}

