/*
    Copyright (c) [2014 - 2015] Western Digital Technologies, Inc. All rights reserved.
*/

/*
    Include Files
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
#include "Logger.hpp"
#include "Translator.hpp"
#include "KineticLog.hpp"
#include "ObjectStore.hpp"
#include "SystemConfig.hpp"
#include "SystemControl.hpp"
#include "AccessControl.hpp"
#include "ServerSettings.hpp"
#include "KineticMessage.hpp"
#include "MessageHandler.hpp"
#include "MessageException.hpp"
#include "ConnectionHandler.hpp"
#include "MessageStatistics.hpp"
#include "TransportInterface.hpp"

/*
    Used Namespaces
*/

using std::set;
using std::map;
using std::list;
using std::string;
using std::unordered_set;
using std::unordered_map;

/*
    Message Types
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
using com::seagate::kinetic::proto::Command_Header;
using com::seagate::kinetic::proto::Command_KeyValue;
using com::seagate::kinetic::proto::Command_Status;
using com::seagate::kinetic::proto::Command_GetLog;
using com::seagate::kinetic::proto::Message_AuthType;

/*
    Private Data Objects
*/

static const int DISPATCH_TABLE_SIZE = 24;
static OperationInfo dispatchTable[DISPATCH_TABLE_SIZE] = {
    { Command_MessageType_INVALID_MESSAGE_TYPE, Command_MessageType_INVALID_MESSAGE_TYPE,   Operation::INVALID,    Message_AuthType::Message_AuthType_INVALID_AUTH_TYPE, false, MessageHandler::processInvalidRequest   },
    { Command_MessageType_GET,                  Command_MessageType_GET_RESPONSE,           Operation::READ,     Message_AuthType::Message_AuthType_HMACAUTH, true,  MessageHandler::processGetRequest                  },
    { Command_MessageType_PUT,                  Command_MessageType_PUT_RESPONSE,           Operation::WRITE,    Message_AuthType::Message_AuthType_HMACAUTH, true,  MessageHandler::processPutRequest                  },
    { Command_MessageType_DELETE,               Command_MessageType_DELETE_RESPONSE,        Operation::DELETE,   Message_AuthType::Message_AuthType_HMACAUTH, true,  MessageHandler::processDeleteRequest               },
    { Command_MessageType_GETNEXT,              Command_MessageType_GETNEXT_RESPONSE,       Operation::READ,     Message_AuthType::Message_AuthType_HMACAUTH, false, MessageHandler::processGetNextRequest              },
    { Command_MessageType_GETPREVIOUS,          Command_MessageType_GETPREVIOUS_RESPONSE,   Operation::READ,     Message_AuthType::Message_AuthType_HMACAUTH, false, MessageHandler::processGetPreviousRequest          },
    { Command_MessageType_GETKEYRANGE,          Command_MessageType_GETKEYRANGE_RESPONSE,   Operation::RANGE,    Message_AuthType::Message_AuthType_HMACAUTH, false, MessageHandler::processGetKeyRangeRequest          },
    { Command_MessageType_INVALID_MESSAGE_TYPE, Command_MessageType_INVALID_MESSAGE_TYPE,   Operation::INVALID,    Message_AuthType::Message_AuthType_INVALID_AUTH_TYPE, false, MessageHandler::processInvalidRequest   },
    { Command_MessageType_GETVERSION,           Command_MessageType_GETVERSION_RESPONSE,    Operation::READ,     Message_AuthType::Message_AuthType_HMACAUTH, true,  MessageHandler::processGetVersionRequest           },
    { Command_MessageType_INVALID_MESSAGE_TYPE, Command_MessageType_INVALID_MESSAGE_TYPE,   Operation::INVALID,    Message_AuthType::Message_AuthType_INVALID_AUTH_TYPE, false, MessageHandler::processInvalidRequest   },
    { Command_MessageType_INVALID_MESSAGE_TYPE, Command_MessageType_INVALID_MESSAGE_TYPE,   Operation::INVALID,    Message_AuthType::Message_AuthType_INVALID_AUTH_TYPE, false, MessageHandler::processInvalidRequest   },
    { Command_MessageType_SETUP,                Command_MessageType_SETUP_RESPONSE,         Operation::SETUP,    Message_AuthType::Message_AuthType_HMACAUTH, false, MessageHandler::processSetupRequest                },
    { Command_MessageType_GETLOG,               Command_MessageType_GETLOG_RESPONSE,        Operation::GETLOG,   Message_AuthType::Message_AuthType_HMACAUTH, false, MessageHandler::processGetLogRequest               },
    { Command_MessageType_SECURITY,             Command_MessageType_SECURITY_RESPONSE,      Operation::SECURITY, Message_AuthType::Message_AuthType_HMACAUTH, false, MessageHandler::processSecurityRequest             },
    { Command_MessageType_PEER2PEERPUSH,        Command_MessageType_PEER2PEERPUSH_RESPONSE, Operation::P2POP,    Message_AuthType::Message_AuthType_HMACAUTH, false, MessageHandler::processP2pPushRequest              },
    { Command_MessageType_NOOP,                 Command_MessageType_NOOP_RESPONSE,          Operation::INVALID,  Message_AuthType::Message_AuthType_HMACAUTH, false, MessageHandler::processNoopRequest                 },
    { Command_MessageType_FLUSHALLDATA,         Command_MessageType_FLUSHALLDATA_RESPONSE,  Operation::INVALID,  Message_AuthType::Message_AuthType_HMACAUTH, false, MessageHandler::processFlushRequest                },
    { Command_MessageType_INVALID_MESSAGE_TYPE, Command_MessageType_INVALID_MESSAGE_TYPE,   Operation::INVALID,    Message_AuthType::Message_AuthType_INVALID_AUTH_TYPE, false, MessageHandler::processInvalidRequest   },
    { Command_MessageType_PINOP,                Command_MessageType_PINOP_RESPONSE,         Operation::INVALID,  Message_AuthType::Message_AuthType_PINAUTH,  false, MessageHandler::processPinOpRequest                },
    { Command_MessageType_INVALID_MESSAGE_TYPE, Command_MessageType_INVALID_MESSAGE_TYPE,   Operation::INVALID,    Message_AuthType::Message_AuthType_INVALID_AUTH_TYPE, false, MessageHandler::processInvalidRequest   },
    { Command_MessageType_INVALID_MESSAGE_TYPE, Command_MessageType_INVALID_MESSAGE_TYPE,   Operation::INVALID,    Message_AuthType::Message_AuthType_INVALID_AUTH_TYPE, false, MessageHandler::processInvalidRequest   },
    { Command_MessageType_INVALID_MESSAGE_TYPE, Command_MessageType_INVALID_MESSAGE_TYPE,   Operation::INVALID,    Message_AuthType::Message_AuthType_INVALID_AUTH_TYPE, false, MessageHandler::processInvalidRequest   },
    { Command_MessageType_INVALID_MESSAGE_TYPE, Command_MessageType_INVALID_MESSAGE_TYPE,   Operation::INVALID,    Message_AuthType::Message_AuthType_INVALID_AUTH_TYPE, false, MessageHandler::processInvalidRequest   },
    { Command_MessageType_INVALID_MESSAGE_TYPE, Command_MessageType_INVALID_MESSAGE_TYPE,   Operation::INVALID,    Message_AuthType::Message_AuthType_INVALID_AUTH_TYPE, false, MessageHandler::processInvalidRequest   },
};

/**
    MessageHandler Constructor

    @param connectionHandler

    NOTE: WE DON'T WANT THIS CREATED EACH TIME A MESSAGE IS RECEIVED.
*/

MessageHandler::MessageHandler(ConnectionHandler* connectionHandler)
    : m_connectionHandler(connectionHandler) {
}

/**
    Initial Message Processing

    @param requestMessage   the request message to be processed
    @param responseMessage  the response message to be returned
    @param accessControl    access control for this message, which will be set by the function
*/

OperationInfo&
MessageHandler::initialMessageProcessing(KineticMessagePtr& requestMessage, KineticMessagePtr& responseMessage, AccessControlPtr& accessControl) {

    /*
        Verify that the request contains all the required header fields (if not, the verify
        function will throw an exception).
    */

    if (!requestMessage->command()->has_header())
        throw MessageException(com::seagate::kinetic::proto::Command_Status_StatusCode_HEADER_REQUIRED, "Command missing Header");

    const Command_Header& requestHeader = requestMessage->command()->header();

    if (!requestHeader.has_sequence())
        throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Header missing Sequence");

    Command_Header* responseHeader = responseMessage->mutable_command()->mutable_header();
    responseHeader->set_acksequence(requestHeader.sequence());

    if (!requestHeader.has_messagetype())
        throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Header missing Message Type");

    uint32_t dispatchTableIndex = messageTypeToIndex(requestHeader.messagetype());

    if (dispatchTableIndex >= DISPATCH_TABLE_SIZE)
        throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Unsupported message type");

    OperationInfo& operationInfo = dispatchTable[dispatchTableIndex];
    responseHeader->set_messagetype(operationInfo.responseType);

    if (requestMessage->authtype() != operationInfo.requiredAuthenticationType())
        throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Incorrect authentication type");

    if ((requestMessage->authtype() == Message_AuthType::Message_AuthType_HMACAUTH) && !requestMessage->hmacauth().has_identity())
        throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Header missing Identity");

    if (requestHeader.messagetype() != Command_MessageType_PINOP)
        accessControl = serverSettings.accessControl(requestMessage->hmacauth().identity());

    /*
        Verify that the cluster version is set and correct (for non-pinauth requests, which doesn't
        require the cluster version).
    */

#ifdef WORK_WITH_JAVA_SMOKE_TEST
    if (requestMessage->authtype() != Message_AuthType::Message_AuthType_PINAUTH) {
#else
    {
#endif
        if (!requestHeader.has_clusterversion()) {
            throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Header missing Cluster Version");
        }
        else if (requestHeader.clusterversion() != serverSettings.clusterVersion()) {
#ifdef WORK_WITH_JAVA_SMOKE_TEST
            throw MessageException(Command_Status_StatusCode_VERSION_FAILURE, "CLUSTER_VERSION_FAILURE");
#else
            throw MessageException(Command_Status_StatusCode_VERSION_FAILURE, "Incorrect Cluster Version");
#endif
        }
    }

    if (!requestHeader.has_connectionid())
        throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Header missing Connection ID");

    /*
        Next, validate the contents of the header.
    */

    ConnectionContext& connectionInfo = m_connectionHandler->getContext();

    if (connectionInfo.processedFirstRequest()) {
        if (requestHeader.connectionid() != connectionInfo.connectionId())
            throw MessageException(Command_Status_StatusCode_VERSION_FAILURE, "Incorrect Connection ID");

        if (requestHeader.sequence() <= connectionInfo.previousSequence())
            throw MessageException(Command_Status_StatusCode_VERSION_FAILURE, "Invalid Sequence Number");
    }
    else {
        connectionInfo.setProcessedFirstRequest(true);
    }

    connectionInfo.setPreviousSequence(requestHeader.sequence());

    // PIN operations don't require specified access control, they just need to specify the PIN.

    if (requestMessage->authtype() == Message_AuthType::Message_AuthType_HMACAUTH) {

        if (accessControl == nullptr) {
            throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Identity does not have access");
        }

        string hmacKey = accessControl->hmacKey();
        if (!requestMessage->validateHmac(hmacKey, accessControl->hmacAlgorithm())) {
            throw MessageException(com::seagate::kinetic::proto::Command_Status_StatusCode_HMAC_FAILURE, "Incorrect HMAC");
        }

        /*
            Access check
        */

        if (accessControl->tlsRequired(operationInfo.operation()) && (m_connectionHandler->transport()->security() != Security::SSL))
            throw MessageException(Command_Status_StatusCode_NOT_AUTHORIZED, "Requires TLS connection for request");

        /*
            No permission needed for NOOP
        */

        if (requestHeader.messagetype() != Command_MessageType_NOOP) {
            if (!accessControl->operationPermitted(operationInfo.operation(), operationInfo.operationInvolvesKey(), requestMessage->command()->body()))
#ifdef WORK_WITH_JAVA_SMOKE_TEST
                throw MessageException(Command_Status_StatusCode_NOT_AUTHORIZED, "permission denied");
#else
                throw MessageException(Command_Status_StatusCode_NOT_AUTHORIZED, "The user does not have permission");
#endif
        }
    }

    if (systemControl.locked() && !((requestHeader.messagetype() == Command_MessageType_PINOP)
                                    && ((requestMessage->command()->body().pinop().pinoptype() == com::seagate::kinetic::proto::Command_PinOperation_PinOpType_UNLOCK_PINOP)
                                        || (requestMessage->command()->body().pinop().pinoptype() == com::seagate::kinetic::proto::Command_PinOperation_PinOpType_LOCK_PINOP)))) {

        throw MessageException(com::seagate::kinetic::proto::Command_Status_StatusCode_DEVICE_LOCKED);
    }
    return operationInfo;
}

/**
    Process Request

    @param requestMessage   the request message to be processed

    @return the response message

    This function is called by the thread that will perform the operation.
*/

KineticMessagePtr
MessageHandler::processRequest(KineticMessagePtr& requestMessage) {

    KineticMessagePtr responseMessage(new KineticMessage());
    AccessControlPtr accessControl;

    try {
        OperationInfo& operationInfo = initialMessageProcessing(requestMessage, responseMessage, accessControl);
        operationInfo.perform(requestMessage, responseMessage);
    }
    catch (MessageException& messageException) {
        Command_Status* status = responseMessage->mutable_command()->mutable_status();
        status->set_code(messageException.statusCode());
        status->set_statusmessage(messageException.statusMessage());
    }
    catch (std::exception& ex) {
        LOG(ERROR) << "MessageHandler::processRequest exception: " << ex.what();
        Command_Status* status = responseMessage->mutable_command()->mutable_status();
        status->set_code(Command_Status_StatusCode_INTERNAL_ERROR);
        status->set_statusmessage(string(ex.what()));
    }

    if (accessControl != nullptr) {
        requestMessage->set_authtype(Message_AuthType::Message_AuthType_HMACAUTH);
        responseMessage->mutable_hmacauth()->set_identity(accessControl->identity());
    }

    responseMessage->build_commandbytes();

    if (accessControl != nullptr) {
        responseMessage->generateHmac(accessControl->hmacKey(), accessControl->hmacAlgorithm());
    }

    messageStatistics.update(requestMessage, responseMessage);

    return responseMessage;
}

/**
    Process Error

    @param requestMessage   the request message to be processed
    @param error            the error that was encountered
    @param errorMessage     text that describes the error

    @return the response message
*/

KineticMessagePtr
MessageHandler::processError(KineticMessagePtr& requestMessage, ConnectionError error, const std::string& errorMessage) {


    KineticMessagePtr responseMessage(new KineticMessage());
    AccessControlPtr accessControl;

    try {
        initialMessageProcessing(requestMessage, responseMessage, accessControl);
        Command_Status* status = responseMessage->mutable_command()->mutable_status();
        Command_Header* responseHeader = responseMessage->mutable_command()->mutable_header();

        if (requestMessage->command()->has_header()) {
            const Command_Header& requestHeader = requestMessage->command()->header();

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

        if ((requestMessage->authtype() == Message_AuthType::Message_AuthType_HMACAUTH) && requestMessage->hmacauth().has_identity())
            accessControl = serverSettings.accessControl(requestMessage->hmacauth().identity());

        if (error == ConnectionError::VALUE_TOO_BIG) {
            status->set_code(Command_Status_StatusCode_INVALID_REQUEST);
            status->set_statusmessage(errorMessage);
        }
        else {
            status->set_code(Command_Status_StatusCode_INTERNAL_ERROR);
            status->set_statusmessage("Unknown connection error");
        }
    }
    catch (MessageException& messageException) {
        Command_Status* status = responseMessage->mutable_command()->mutable_status();
        status->set_code(messageException.statusCode());
        status->set_statusmessage(messageException.statusMessage());
    }
    if (accessControl != nullptr) {
        requestMessage->set_authtype(Message_AuthType::Message_AuthType_HMACAUTH);
        responseMessage->mutable_hmacauth()->set_identity(accessControl->identity());
    }
    responseMessage->build_commandbytes();

    if (accessControl != nullptr) {
        responseMessage->generateHmac(accessControl->hmacKey(), accessControl->hmacAlgorithm());
    }

    messageStatistics.update(requestMessage, responseMessage);

    return responseMessage;
}

/**
    Process Setup Request

    @param requestMessage   the request message to be processed
    @param responseMessage  the response message to be returned

    A setup request is used perform a secure erase, download a new firmware image, or update setup
    parameters (cluster version and/or personal ID number). Although syntactically more than one of
    these operations can be requested at once, only one is permitted per request.  All operations
    require the device's PIN to be specified in order to perform operation.  Currently, if no
    operations are requested, the request will complete successfully (that may change since the
    Kinetic documentation doesn't cover that scenario).
*/

void
MessageHandler::processSetupRequest(KineticMessagePtr& requestMessage, KineticMessagePtr& responseMessage) {

    /*
        Ensure that the message contains the setup parameters, the correctly PIN was specified, and
        that only one operation is being request.  If any of those conditions are not true, fail the
        request.
    */

    if (!requestMessage->command()->body().has_setup())
        throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Setup parameters not specified");

    const com::seagate::kinetic::proto::Command_Setup& setupRequest(requestMessage->command()->body().setup());

    uint32_t operationCount(0);
    if (setupRequest.firmwaredownload())
        operationCount++;
    if (setupRequest.has_newclusterversion())
        operationCount++;

    if (operationCount > 1)
        throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "More than one setup operation requested at once");

    /*
        If a firmware image was to be downloaded, verify that a valid image was provided.  If not,
        fail the request.  If so, record that a firmware image is to be saved.
    */

    if (setupRequest.firmwaredownload()) {
        if (requestMessage->value().empty())  // or not valid
            throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Invalid firmware image (empty)");
    }

    /*
        If the cluster version and/or personal ID number are to be set, validate the specified
        values, and if valid, perform the update.  Otherwise, fail the request.
    */


    /*
        If the cluster version was specified, verify that its a legal value (not zero).  If not,
        fail the request.  If so, record that the cluster version is to be set after all the
        setup parameters have been validated.
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
        serverSettings.setClusterVersion(setupRequest.newclusterversion());
        serverSettings.save();
    }

    responseMessage->mutable_command()->mutable_status()->set_code(Command_Status_StatusCode_SUCCESS);
}

/**
    Process Set Security Request

    @param requestMessage   the request message to be processed
    @param responseMessage  the response message to be returned

    The security message is used to change one of the following settings:
          The erase PIN
          The lock PIN
          The Acces control lists (ACLs)

    Only one of those settings change be changed per message.  The Kinetic Protocol supports
    restricting the operations a requester (identity) can perform using ACLs.  Below is a list of
    their values.

    ACL(s)
        Identity:         The ID of the requester that the access control is for
        Key:              The shared secret between the client and the device that is used to sign requests (using HMAC)
        HMAC Algorithm    The algorithm used to generate the HMAC for the requester's messages
        Scope(s)          An ACL can have multiple scopes
            Permissions   Scopes grant a set of permissions to the identity associated with the ACL
                          The permissions are: READ, WRITE, DELETE, RANGE, SETUP, P2POP, GETLOG, SECURITY
            TLS Required  Indicates if TLS must be used for the associated permissions
            Offset        Offset and Value are optional and are used to further restrict which keys the Scope applies to.
            Value         When specified, the permission will only apply to keys that match the value at the given offset.
*/

void
MessageHandler::processSecurityRequest(KineticMessagePtr& requestMessage, KineticMessagePtr& responseMessage) {

    try {

        /*
            Verify that the message contains security parameters and does not contain new values for
            more that one setting (the erase PIN, the lock PIN, or the ACLs), which is not
            permitted.
        */

        if (!requestMessage->command()->body().has_security()) {
            throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Missing security parameters");
        }
        const com::seagate::kinetic::proto::Command_Security& security = requestMessage->command()->body().security();

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
            If the erase PIN is specified, set the erase PIN to its new value.
        */

        if (security.has_newerasepin() || security.has_olderasepin()) {

            if (!serverSettings.erasePin().empty() && (serverSettings.erasePin().compare(security.olderasepin()) != 0))
                throw MessageException(Command_Status_StatusCode_NOT_AUTHORIZED, "Invalid old lock pin");

            if (security.newerasepin().length() > systemConfig.maxPinSize())
                throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "New PIN exceeds the maximum size");

            serverSettings.setErasePin(security.newerasepin());
        }

        /*
            If the lock PIN is specified, set the lock PIN to its new value/
        */

        else if (security.has_newlockpin() || security.has_oldlockpin()) {

            if (!serverSettings.lockPin().empty() && ((serverSettings.lockPin().compare(security.oldlockpin()) != 0)))
                throw MessageException(Command_Status_StatusCode_NOT_AUTHORIZED, "Invalid old erase pin");

            if (security.newlockpin().length() > systemConfig.maxPinSize())
                throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "New PIN exceeds the maximum size");

            serverSettings.setLockPin(security.newlockpin());
        }

        else if (security.acl_size() > 0) {

            /*
                Verify that the maximum number of indentities has not been exceeeded.  If it has,
                fail the message.
            */

            std::set<int64_t> identitySet;
            for (auto aclIndex = 0; aclIndex < security.acl_size(); aclIndex++) {
                const com::seagate::kinetic::proto::Command_Security_ACL& acl = security.acl(aclIndex);
                if (acl.has_identity() && (acl.identity() < 0))
                    identitySet.insert(acl.identity());
            }

            if (identitySet.size() > systemConfig.maxIdentityCount())
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
            serverSettings.updateAccessControl(accessControlList);
        }

        /*
            Save the new setting and indicate that the operation was performed successfully.
        */

        serverSettings.save();
        responseMessage->mutable_command()->mutable_status()->set_code(Command_Status_StatusCode_SUCCESS);
    }
    catch (MessageException& messageException) {
#if 0
        std::cerr << "Exception processing message " << messageException.statusMessage() << std::endl;
#endif
        Command_Status* status = responseMessage->mutable_command()->mutable_status();
        status->set_code(messageException.statusCode());
        status->set_statusmessage(messageException.statusMessage());
    }
}

/**
    Process Get Log Request

    @param requestMessage   the request message to be processed
    @param responseMessage  the response message to be returned
*/

void
MessageHandler::processGetLogRequest(KineticMessagePtr& requestMessage, KineticMessagePtr& responseMessage) {

    const Command_GetLog& getLogRequest = requestMessage->command()->body().getlog();
    Command_GetLog* getLogResponse = responseMessage->mutable_command()->mutable_body()->mutable_getlog();

    /*
        If no log types were specified, then send all types.
    */

    std::set<com::seagate::kinetic::proto::Command_GetLog_Type> logTypeSet;
    if (getLogRequest.types_size() == 0)
        logTypeSet = systemConfig.defaultLogTypes();

    /*
        Remove any duplicate log types by copying them to a set (which doesn't permit duplicates).
        Then, get the information for each requested log type.
    */

    else {
        for (int32_t index = 0; index < getLogRequest.types_size(); index++)
            logTypeSet.insert(getLogRequest.types(index));
    }

    for (auto logType : logTypeSet) {
        getLogResponse->add_types(logType);
        switch (logType) {
            case com::seagate::kinetic::proto::Command_GetLog_Type_STATISTICS:
                KineticLog::getStatistics(getLogResponse);
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
                KineticLog::getDevice(getLogRequest, responseMessage->value());
                break;
            default:
                throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Unsupported log type specified");
        }
    }
    responseMessage->mutable_command()->mutable_status()->set_code(Command_Status_StatusCode_SUCCESS);
}

/**
    Process Put Request

    @param serializedMessage    the request message in its serialized form
    @param response             the response message data to be populated

    Put the entry with the attributes.  The entry will only be put if the specified version
    matches the entry's current version unless the force option is specified (in which case a
    version is not given) or the entry isn't already in the database and no existing version is
    given. The put request may specify an optional persistence option (indicating write-back or
    write-through).
*/

void
MessageHandler::processPutRequest(KineticMessagePtr& requestMessage, KineticMessagePtr& responseMessage) {

    /*
        If the put is to be forced, it doesn't require the entry version.
    */

    const Command_KeyValue& params = requestMessage->command()->body().keyvalue();
    ReturnStatus returnStatus;

    if (params.force())
        returnStatus = objectStore->putForced(params.key(), requestMessage->value(), params.newversion(),
                                              params.tag(), params.algorithm(), params.synchronization());
    else
        returnStatus = objectStore->put(params.key(), requestMessage->value(), params.newversion(),
                                        params.dbversion(), params.tag(), params.algorithm(), params.synchronization());

    Translator::setMessageStatus(responseMessage->mutable_command()->mutable_status(), returnStatus);
}

/**
    Process Get Request

    @param requestMessage   the request message to be processed
    @param responseMessage  the response message to be returned
*/

void
MessageHandler::processGetRequest(KineticMessagePtr& requestMessage, KineticMessagePtr& responseMessage) {

    /*
        Ensure that the message contains the get (key/value) parameters.  If not, fail the request.
    */

    Command_Status* status = responseMessage->mutable_command()->mutable_status();

    if (!requestMessage->command()->body().has_keyvalue())
        throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Get parameters not specified");

    const Command_KeyValue& request = requestMessage->command()->body().keyvalue();
    const string& key = request.key();
    bool metadataOnly = request.metadataonly();

    string version;
    string tag;
    Algorithm algorithm;

    ReturnStatus returnStatus;
    if (!metadataOnly)
        returnStatus = objectStore->get(key, responseMessage->value(), version, tag, algorithm);
    else
        returnStatus = objectStore->getMetadata(key, version, tag, algorithm);

    Translator::setMessageStatus(status, returnStatus);
    responseMessage->mutable_command()->mutable_body()->mutable_keyvalue();

    if (returnStatus == ReturnStatus::SUCCESS) {

        Command_KeyValue* response = responseMessage->mutable_command()->mutable_body()->mutable_keyvalue();
        response->set_key(key);
        response->set_dbversion(version);
        response->set_tag(tag);
        response->set_algorithm(algorithm);
    }

#if 0
    Command_KeyValue* response = responseMessage->mutable_command()->mutable_body()->mutable_keyvalue();

    string algorithm;
    ReturnStatus returnStatus;
    if (!request.metadataonly())
        returnStatus = objectStore->get(request.key(), responseMessage->value(), *response->mutable_dbversion(), *response->mutable_tag(), algorithm);
    else
        returnStatus = objectStore->getMetadata(request.key(), *response->mutable_dbversion(), *response->mutable_tag(), algorithm);

    if (returnStatus == ReturnStatus::SUCCESS)
        response->set_algorithm(Translator::toMessageFormat(algorithm));

    Translator::setMessageStatus(status, returnStatus);
#endif
}

/**
    Process Get Next Request

    @param requestMessage   the request message to be processed
    @param responseMessage  the response message to be returned
*/

void
MessageHandler::processGetNextRequest(KineticMessagePtr& requestMessage, KineticMessagePtr& responseMessage) {

    /*
        Ensure that the message contains the get (key/value) parameters.  If not, fail the request.
    */

    Command_Status* status = responseMessage->mutable_command()->mutable_status();

    if (!requestMessage->command()->body().has_keyvalue())
        throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Get Next parameters not specified");

    const Command_KeyValue& request = requestMessage->command()->body().keyvalue();
    const string& key = request.key();

    string nextKey;
    string nextVersion;
    string nextTag;
    Algorithm nextAlgorithm;

    ReturnStatus returnStatus = objectStore->getNext(key, nextKey, responseMessage->value(), nextVersion, nextTag, nextAlgorithm);

    Translator::setMessageStatus(status, returnStatus);
    responseMessage->mutable_command()->mutable_body()->mutable_keyvalue();

    if (returnStatus == ReturnStatus::SUCCESS) {

        if (requestMessage->authtype() != Message_AuthType::Message_AuthType_HMACAUTH)
            throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Requires HMAC authentication");

        AccessControlPtr accessControl = serverSettings.accessControl(requestMessage->hmacauth().identity());

        if (accessControl != nullptr) {
            if (!accessControl->permissionToRead(nextKey)) {
#ifdef WORK_WITH_JAVA_SMOKE_TEST
                throw MessageException(Command_Status_StatusCode_NOT_AUTHORIZED, "permission denied");
#else
                throw MessageException(Command_Status_StatusCode_NOT_AUTHORIZED, "The user does not have permission");
#endif
            }
        }

        Command_KeyValue* response = responseMessage->mutable_command()->mutable_body()->mutable_keyvalue();
        response->set_key(nextKey);
        response->set_dbversion(nextVersion);
        response->set_tag(nextTag);
        response->set_algorithm(nextAlgorithm);
    }
}

/**
    Process Get Previous Request

    @param requestMessage   the request message to be processed
    @param responseMessage  the response message to be returned
*/

void
MessageHandler::processGetPreviousRequest(KineticMessagePtr& requestMessage, KineticMessagePtr& responseMessage) {

    /*
        Ensure that the message contains the get (key/value) parameters.  If not, fail the request.
    */

    Command_Status* status = responseMessage->mutable_command()->mutable_status();

    if (!requestMessage->command()->body().has_keyvalue())
        throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Get Previous parameters not specified");

    const Command_KeyValue& request = requestMessage->command()->body().keyvalue();
    const string& key = request.key();

    string previousKey;
    string previousVersion;
    string previousTag;
    Algorithm previousAlgorithm;

    ReturnStatus returnStatus = objectStore->getPrevious(key, previousKey, responseMessage->value(), previousVersion, previousTag, previousAlgorithm);

    Translator::setMessageStatus(status, returnStatus);
    responseMessage->mutable_command()->mutable_body()->mutable_keyvalue();

    if (returnStatus == ReturnStatus::SUCCESS) {

        if (requestMessage->authtype() != Message_AuthType::Message_AuthType_HMACAUTH)
            throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Requires HMAC authentication");

        AccessControlPtr accessControl = serverSettings.accessControl(requestMessage->hmacauth().identity());

        if (accessControl != nullptr) {
            if (!accessControl->permissionToRead(previousKey)) {
#ifdef WORK_WITH_JAVA_SMOKE_TEST
                throw MessageException(Command_Status_StatusCode_NOT_AUTHORIZED, "permission denied");
#else
                throw MessageException(Command_Status_StatusCode_NOT_AUTHORIZED, "The user does not have permission");
#endif
            }
        }

        Command_KeyValue* response = responseMessage->mutable_command()->mutable_body()->mutable_keyvalue();
        response->set_key(previousKey);
        response->set_dbversion(previousVersion);
        response->set_tag(previousTag);
        response->set_algorithm(previousAlgorithm);
    }
}

/**
    Process Get Version Request

    @param requestMessage   the request message to be processed
    @param responseMessage  the response message to be returned
*/

void
MessageHandler::processGetVersionRequest(KineticMessagePtr& requestMessage, KineticMessagePtr& responseMessage) {

    /*
        Ensure that the message contains the get (key/value) parameters.  If not, fail the request.
    */

    Command_Status* status = responseMessage->mutable_command()->mutable_status();

    if (!requestMessage->command()->body().has_keyvalue())
        throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Get version parameters not specified");

    const Command_KeyValue& request = requestMessage->command()->body().keyvalue();
    const string& key = request.key();

    string version;
    string tag;
    Algorithm algorithm;

    ReturnStatus returnStatus = objectStore->getMetadata(key, version, tag, algorithm);

    Translator::setMessageStatus(status, returnStatus);
    responseMessage->mutable_command()->mutable_body()->mutable_keyvalue();

    if (returnStatus == ReturnStatus::SUCCESS) {
        Command_KeyValue* response = responseMessage->mutable_command()->mutable_body()->mutable_keyvalue();
        response->set_dbversion(version);
    }
}

/**
    Process Get Key Range Request

    @param requestMessage   the request message to be processed
    @param responseMessage  the response message to be returned
*/

void
MessageHandler::processGetKeyRangeRequest(KineticMessagePtr& requestMessage, KineticMessagePtr& responseMessage) {

    const com::seagate::kinetic::proto::Command_Range& params(requestMessage->command()->body().range());
    ReturnStatus returnStatus;
    list<string> keyList;

#if 0
    int32_t maxReturned = params.maxreturned() > systemConfig.maxKeyRangeCount() ? systemConfig.maxKeyRangeCount() : params.maxreturned();
#endif

    // TODO(gballance) - maybe have this checked in initialMessageProcessing
    if (requestMessage->authtype() != Message_AuthType::Message_AuthType_HMACAUTH)
        throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Requires HMAC authentication");

    AccessControlPtr accessControl = serverSettings.accessControl(requestMessage->hmacauth().identity());

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

    if (!params.reverse())
        returnStatus = objectStore->getKeyRange(params.startkey(), params.startkeyinclusive(), params.endkey(),
                                                params.endkeyinclusive(), params.maxreturned(), keyList, accessControl);
    else
        returnStatus = objectStore->getKeyRangeReversed(params.startkey(), params.startkeyinclusive(), params.endkey(),
                       params.endkeyinclusive(), params.maxreturned(), keyList, accessControl);

    Translator::setMessageStatus(responseMessage->mutable_command()->mutable_status(), returnStatus);

    if ((returnStatus == ReturnStatus::SUCCESS) && (keyList.size() > 0)) {
        com::seagate::kinetic::proto::Command_Range* response(responseMessage->mutable_command()->mutable_body()->mutable_range());

        for (auto& key : keyList)
            response->add_keys(key);
    }
}

/**
    Process Delete Request

    @param requestMessage   the request message to be processed
    @param responseMessage  the response message to be returned

    Delete the entry with the specified key.  The entry will only be deleted if the specified
    version matches the entry's current version unless the force option is specified (in which case
    a version is not given).  The delete request may specify an optional persistence option
    (indicating write-back or write-through).
*/

void
MessageHandler::processDeleteRequest(KineticMessagePtr& requestMessage, KineticMessagePtr& responseMessage) {

    /*
        If the delete is to be forced, it doesn't require the entry version.
    */

    const Command_KeyValue& params = requestMessage->command()->body().keyvalue();
    ReturnStatus returnStatus;

    if (params.force())
        returnStatus = objectStore->de1eteForced(params.key(), params.synchronization());
    else
        returnStatus = objectStore->de1ete(params.key(), params.dbversion(), params.synchronization());

    Translator::setMessageStatus(responseMessage->mutable_command()->mutable_status(), returnStatus);
}

/**
    Process Flush Request

    @param requestMessage   the request message to be processed
    @param responseMessage  the response message to be returned
*/

void
MessageHandler::processFlushRequest(KineticMessagePtr& requestMessage, KineticMessagePtr& responseMessage) {

    /*
        Eliminate the unused args warning and set the status to success.
    */

    static_cast<void>(requestMessage);
    Translator::setMessageStatus(responseMessage->mutable_command()->mutable_status(), objectStore->flush());
}

/**
    Process Noop Request

    @param requestMessage   the request message to be processed
    @param responseMessage  the response message to be returned
*/

void
MessageHandler::processNoopRequest(KineticMessagePtr& requestMessage, KineticMessagePtr& responseMessage) {

    /*
        Eliminate the unused args warning and set the status to success.
    */

    static_cast<void>(requestMessage);
    responseMessage->mutable_command()->mutable_status()->set_code(Command_Status_StatusCode_SUCCESS);
}

/**
    Process PIN Operation Request

    @param requestMessage   the request message to be processed
    @param responseMessage  the response message to be returned
*/

void
MessageHandler::processPinOpRequest(KineticMessagePtr& requestMessage, KineticMessagePtr& responseMessage) {

    try {

        if (!requestMessage->command()->body().has_pinop())
            throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Missing PIN operation parameters");

        // check if met TLS requirement
//            checkSecureChannel(request);

//        responseMessage ... setAuthType(AuthType.PINAUTH);

        switch (requestMessage->command()->body().pinop().pinoptype()) {
            case com::seagate::kinetic::proto::Command_PinOperation_PinOpType_LOCK_PINOP:
                // check if not empty
//                checkRequestPin(requestPin);
                // check if has permission
//                comparePin(requestPin, engine.getSecurityPin().getLockPin());
                // lock device
//                engine.setDeviceLocked(true);

//                std::cout << "LOCK_PINOP" << std::endl;

                if (!serverSettings.lockPin().empty()) {

                    if (serverSettings.lockPin().empty())
                        std::cout << "Current lock PIN is empty" << std::endl;
                    else
                        std::cout << "Current lock PIN: " << serverSettings.lockPin() << std::endl;

                    if (requestMessage->pinauth().pin().empty())
                        std::cout << "Specified PIN is empty" << std::endl;
                    else
                        std::cout << "Specified PIN: " << requestMessage->pinauth().pin() << std::endl;

                    if (requestMessage->pinauth().pin().empty() && serverSettings.lockPin().empty())
                        std::cout << "both empty" << std::endl;

                    else if (requestMessage->pinauth().pin().compare(serverSettings.lockPin()) != 0)
                        throw MessageException(Command_Status_StatusCode_NOT_AUTHORIZED, "Incorrect PIN 1");
                }

                systemControl.setLocked(true);
                break;

            case com::seagate::kinetic::proto::Command_PinOperation_PinOpType_UNLOCK_PINOP:
                // check if not empty
//                checkRequestPin(requestPin);
                // check if has permission
//                comparePin(requestPin, engine.getSecurityPin().getLockPin());
                // unlock device
//                engine.setDeviceLocked(false);
//                std::cout << "UNLOCK_PINOP" << std::endl;

                if (!serverSettings.lockPin().empty()) {
#if 0
                    if (serverSettings.lockPin().empty())
                        std::cout << "Current lock PIN is empty" << std::endl;
                    else
                        std::cout << "Current lock PIN: " << serverSettings.lockPin() << std::endl;

                    if (requestMessage->pinauth().pin().empty())
                        std::cout << "Specified PIN is empty" << std::endl;
                    else
                        std::cout << "Specified PIN: " << requestMessage->pinauth().pin() << std::endl;
#endif
                    if (requestMessage->pinauth().pin().empty() && serverSettings.lockPin().empty())
                        std::cout << "both empty" << std::endl;

                    else if (requestMessage->pinauth().pin().compare(serverSettings.lockPin()) != 0)
                        throw MessageException(Command_Status_StatusCode_NOT_AUTHORIZED, "Incorrect PIN 2");
                }

                systemControl.setLocked(false);
                break;

            case com::seagate::kinetic::proto::Command_PinOperation_PinOpType_ERASE_PINOP:
                // Both erase operations will return
                // the device to an as manufactured state removing all
                // user data and configuration settings.
                // Erase the device. This may be secure
                // or not. The implication is that it may be faster
                // than the secure operation.

//                std::cout << "ERASE_PINOP" << std::endl;

                if (!serverSettings.erasePin().empty()) {
#if 0
                    if (serverSettings.erasePin().empty())
                        std::cout << "Current erase PIN is empty" << std::endl;
                    else
                        std::cout << "Current erase PIN: " << serverSettings.erasePin() << std::endl;

                    if (requestMessage->pinauth().pin().empty())
                        std::cout << "Specified PIN is empty" << std::endl;
                    else
                        std::cout << "Specified PIN: " << requestMessage->pinauth().pin() << std::endl;
#endif
                    if (requestMessage->pinauth().pin().empty() && serverSettings.erasePin().empty())
                        std::cout << "both empty" << std::endl;

                    else if (requestMessage->pinauth().pin().compare(serverSettings.erasePin()) != 0)
                        throw MessageException(Command_Status_StatusCode_NOT_AUTHORIZED, "Incorrect PIN 3");

                }
                objectStore->erase();
                serverSettings.setDefaults();
                break;

            case com::seagate::kinetic::proto::Command_PinOperation_PinOpType_SECURE_ERASE_PINOP:
                // Erase the device in a way that will
                // physical access and disassembly of the device - not supported yet

//                std::cout << "SECURE_ERASE_PINOP" << std::endl;

                if (!serverSettings.erasePin().empty()) {
#if 0
                    if (serverSettings.erasePin().empty())
                        std::cout << "Current erase PIN is empty" << std::endl;
                    else
                        std::cout << "Current erase PIN: " << serverSettings.erasePin() << std::endl;

                    if (requestMessage->pinauth().pin().empty())
                        std::cout << "Specified PIN is empty" << std::endl;
                    else
                        std::cout << "Specified PIN: " << requestMessage->pinauth().pin() << std::endl;
#endif
                    if (requestMessage->pinauth().pin().empty() && serverSettings.erasePin().empty())
                        std::cout << "both empty" << std::endl;

                    else if (requestMessage->pinauth().pin().compare(serverSettings.erasePin()) != 0)
                        throw MessageException(Command_Status_StatusCode_NOT_AUTHORIZED, "Incorrect PIN 4");
                }

                objectStore->erase();
                serverSettings.setDefaults();
                break;

            default:
                throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Unsupported PIN Op Type");  // need to add type info
        }
    }
    catch (MessageException& messageException) {
        throw messageException;
    }
    catch (std::exception& e) {
        std::cerr << "expection thown " << e.what() << std::endl;
        throw MessageException(Command_Status_StatusCode_INTERNAL_ERROR, "Exception thrown");
    }
    catch (...) {
        throw MessageException(Command_Status_StatusCode_INTERNAL_ERROR, "Exception thrown");
    }
    /*
            } catch (KVSecurityException se) {
                commandBuilder.getStatusBuilder()
                        .setCode(StatusCode.NOT_AUTHORIZED);
                commandBuilder.getStatusBuilder().setStatusMessage(se.getMessage());
                logger.warning("unauthorized pin opeartion request");
            } catch (InvalidRequestException ire) {
                commandBuilder.getStatusBuilder().setCode(
                        StatusCode.INVALID_REQUEST);
                commandBuilder.getStatusBuilder()
                        .setStatusMessage(ire.getMessage());
            }
    */

    responseMessage->mutable_command()->mutable_status()->set_code(Command_Status_StatusCode_SUCCESS);
}


/**
    Process P2P Push Request

    @param requestMessage   the request message to be processed
    @param responseMessage  the response message to be returned
*/

void
MessageHandler::processP2pPushRequest(KineticMessagePtr& requestMessage, KineticMessagePtr& responseMessage) {

    /*
        Eliminate the unused args warning and set the status to unsupported message.
    */

    static_cast<void>(requestMessage);
    static_cast<void>(responseMessage);
    throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Request not yet supported");

#ifdef SUPPORT_P2P
    /*
        Ensure that the message contains the peer-to-peer push parameters.  If not, fail the
        request.
    */

    if (!requestMessage->command()->body().has_p2poperation())
        throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Peer-to-peer operation parameters not specified");

    const com::seagate::kinetic::proto::Command_P2POperation& p2pOperation = requestMessage->command()->body().p2poperation();

    const com::seagate::kinetic::proto::Command_P2POperation::Peer& peer = p2pOperation.peer();
    std::cout << peer.hostname() << std::endl;
    std::cout << peer.port() << std::endl;
    std::cout << peer.tls() << std::endl;

    for (uint32_t index = 0; p2pOperation.operation_size(); index++) {
        const com::seagate::kinetic::proto::Command_P2POperation::Operation& operation = p2pOperation.operation(index);

        const string& key = operation.key();
        const string& newKey = operation.newkey();
        const string& version = operation.version();
        const bool force = operation.force();

        string push_key;
        string push_value;
        string push_old_version;
        string push_tag;
        Algorithm push_algorithm;

        ReturnStatus returnStatus = objectStore->get(key, push_value, push_old_version, push_tag, push_algorithm);
        if (returnStatus == ReturnStatus::SUCCESS) {
            string push_key = newKey.empty() ? key : newKey;
            string push_new_version = !version.empty() ? version : push_old_version;
#if 0
            removePut(push_key, push_value, push_new_version, push_old_version, push_tag, push_algorithm);
            push_entry key, value, version, tag, algorithm
#endif
        }
    }
#endif
}

/**
    Open

    @return true if the socket was successfully open, false otherwise
*/

/*
    bool
    open(string ipAddress, uint32_t port, int32_t &socketFd) {

    const int USE_DEFAULT_PROTOCOL(0);
    socketFd = socket(AF_INET, SOCK_STREAM, USE_DEFAULT_PROTOCOL);

    if (socketFd == STATUS_FAILURE) {
        std::cerr << "failed to create socket" << std::endl;
        return false;
    }

    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(ipAddress.c_str());
    server.sin_port = htons(port);

    if (connect(socketFd, (struct sockaddr *) &server, sizeof(server)) < 0) {
        std::cout << "failed to connect" << std::endl;
        return false;
    }

    return true;
    }
*/

/**
    Process Invalid Request

    @param requestMessage   the request message to be processed
    @param responseMessage  the response message to be returned
*/

void
MessageHandler::processInvalidRequest(KineticMessagePtr& requestMessage, KineticMessagePtr& responseMessage) {

    /*
        Eliminate the unused args warning.
    */

    static_cast<void>(requestMessage);
    static_cast<void>(responseMessage);

    throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, "Unsupported message type");
}

