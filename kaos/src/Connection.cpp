/*
    Copyright (c) [2014 - 2015] Western Digital Technologies, Inc. All rights reserved.
*/

/*
    Include Files
*/

#include <stdint.h>
#include <atomic>
#include <string>
#include <sstream>
#include <iostream>
#include <exception>
#include "Logger.hpp"
#include "KineticLog.hpp"
#include "Connection.hpp"
#include "MessageTrace.hpp"
#include "SystemConfig.hpp"
#include "SystemControl.hpp"
#include "KineticMessage.hpp"
#include "ServerSettings.hpp"
#include "MessageHandler.hpp"
#include "TransportInterface.hpp"

/*
    Used Namespaces
*/

using std::string;
using std::unique_ptr;
using std::runtime_error;

static std::atomic<int64_t> nextConnectionId(1);

/**
 *  Connection Constructor
 *
 *  @param transport        transport to be used for this connection
 *  @param stream           stream to be used for this connection
 *  @param serverPort       server's TCP port number
 *  @param serverIpAddress  server's IP address
 *  @param clientPort       client's TCP port number
 *  @param clientIpAddress  client's IP address
 */

Connection::Connection(TransportInterface* transport, StreamInterface* stream, uint32_t serverPort,
                       std::string serverIpAddress, uint32_t clientPort, std::string clientIpAddress)
    : m_transport(transport), m_stream(stream), m_serverPort(serverPort), m_serverIpAddress(serverIpAddress),
      m_clientPort(clientPort), m_clientIpAddress(clientIpAddress), m_thread(new std::thread(&Connection::run, this)),
      m_connectionId(nextConnectionId++), m_previousSequence(0), m_processedFirstRequest(false) {

    m_thread->detach();
}

/*
 *  Connection Destructor
 */

Connection::~Connection() {
    delete m_stream;
    delete m_thread;
}

/**
 *  Run
 *
 *  This is function that the Connection Handler's thread executes.  The thread will block waiting
 *  to receive and message.  When one is received, it will call the message handler thread to
 *  process it.
 */

void
Connection::run() {

    try {
        LOG(INFO) << "Connection opened, server=" << m_serverIpAddress << ":" << m_serverPort
                  << ", client=" << m_clientIpAddress << ":" << m_clientPort;

        sendUnsolicitedStatusMessage();

        for (;;) {

            /*
             * Block waiting to receive a request.
             */

            Transaction transaction(this);
            receiveRequest(transaction);

            if (transaction.error == ConnectionError::NONE)
                MessageHandler::processRequest(transaction);
            else if (transaction.error == ConnectionError::VALUE_TOO_BIG)
                MessageHandler::processError(transaction);
            else
                break;

            if (transaction.response != nullptr)
                sendResponse(transaction);
        }
    }
    catch (std::exception& ex) {
        LOG(ERROR) << "Connection::run exception: " << ex.what();
    }
    catch (...) {
        LOG(ERROR) << "Connection::run unknown exception";
    }
    LOG(INFO) << "Connection closed, server=" << m_serverIpAddress << ":" << m_serverPort
              << ", client=" << m_clientIpAddress << ":" << m_clientPort;
    m_transport->removeConnection(this);
}

/**
 *  Send Unsolicited Status Message
 *
 *  When a connection is first established, the Kinetic device is to send an unsolicited status
 *  messages to the client.
 */

void
Connection::sendUnsolicitedStatusMessage() {

    Transaction transaction(this);
    transaction.response.reset(new KineticMessage());
    transaction.response->set_authtype(com::seagate::kinetic::proto::Message_AuthType_UNSOLICITEDSTATUS);
    ::com::seagate::kinetic::proto::Command* command = transaction.response->mutable_command();
    ::com::seagate::kinetic::proto::Command_Header* header = command->mutable_header();
    header->set_connectionid(m_connectionId);
    header->set_clusterversion(serverSettings.clusterVersion());
    ::com::seagate::kinetic::proto::Command_GetLog* getLogResponse = command->mutable_body()->mutable_getlog();
    getLogResponse->add_types(::com::seagate::kinetic::proto::Command_GetLog_Type_CONFIGURATION);
    KineticLog::getConfiguration(getLogResponse);
    getLogResponse->add_types(::com::seagate::kinetic::proto::Command_GetLog_Type_LIMITS);
    KineticLog::getLimits(getLogResponse);
    command->mutable_status()->set_code(::com::seagate::kinetic::proto::Command_Status_StatusCode_SUCCESS);
    transaction.response->build_commandbytes();
    sendResponse(transaction);
}

/**
 *  Receive Request
 *
 *  @param transaction       maintains a request and response message
 *
 *  @return a pointer to the request message received
 *
 *  This function performing blocking reads using the provided transport.  It understands the
 *  framing of the request message.  It uses that knowledge to determine when a complete request
 *  message has been received.
 */

void
Connection::receiveRequest(Transaction& transaction) {

    try {

        /*
         * First, read in the framing data, which consists of a magic number, the size of the
         * protocol buffer message and the size of the (optional) value.  Then, validate the
         * framing data.  If the magic number is not correct or the sizes specified are invalid,
         * throw an exception, which will can the connection to be fail.
         */

        KineticMessageFraming messageFraming;
        m_stream->read(reinterpret_cast<char*>(&messageFraming), sizeof(messageFraming));

        if (messageFraming.magicNumber() != KINETIC_MESSAGE_FRAMING_MAGIC_NUMBER)
            throw runtime_error("Invalid PDU magic number");

        uint32_t messageSize = messageFraming.messageSize();
        uint32_t valueSize = messageFraming.valueSize();

        if (messageSize == 0)
            throw runtime_error("message size too small");

//        if (messageSize > systemConfig.maxMessageSize()) {
//            throw runtime_error("message size too large");
//        }

        /*
         * Read in the protocol buffer message.  If a value is included, also read in the value.
         * Create a Kinetic Message to hold both the protocol buffer message and the value. Set it
         * with the value and with the deserialized protocol buffer message.
         */

        if (messageSize > systemConfig.maxMessageSize()) {
            std::cout << "message to large" << std::endl;
            unique_ptr<char> messageBuffer(new char[systemConfig.maxMessageSize()]);
            m_stream->read(messageBuffer.get(), messageSize);
            try {
                m_stream->blackHoleRead(messageSize - systemConfig.maxMessageSize());
                transaction.request->deserializeData(messageBuffer.get(), messageSize);
            }
            catch (...) {
            }

            if (systemControl.debugEnabled())
                MessageTrace::outputContents(messageFraming, transaction.request.get());

            throw runtime_error("message size too large");
        }

        unique_ptr<char> messageBuffer(new char[messageSize]);
        m_stream->read(messageBuffer.get(), messageSize);

        if (valueSize > systemConfig.maxValueSize()) {
            m_stream->blackHoleRead(valueSize);
            if (!transaction.request->deserializeData(messageBuffer.get(), messageSize))
                throw runtime_error("invalid message format");

            if (systemControl.debugEnabled())
                MessageTrace::outputContents(messageFraming, transaction.request.get());

            transaction.error = ConnectionError::VALUE_TOO_BIG;
            std::stringstream errorStream;
            errorStream << "Value size (" << valueSize << " bytes) exceeded maximum supported size";
            transaction.errorMessage = errorStream.str();
            return;
        }

        if (valueSize > 0) {
            unique_ptr<char> valueBuffer(new char[valueSize]);
            m_stream->read(valueBuffer.get(), valueSize);
            transaction.request->setValue(valueBuffer.get(), valueSize);
        }

        if (!transaction.request->deserializeData(messageBuffer.get(), messageSize))
            throw runtime_error("invalid message format");

        if (systemControl.debugEnabled())
            MessageTrace::outputContents(messageFraming, transaction.request.get());

        transaction.error = ConnectionError::NONE;
        return;
    }
    catch (std::exception& ex) {
        if (string(ex.what()) != "socket closed")
            LOG(ERROR) << "Connection::receiveRequest exception: " << ex.what();
        // This usually happens when a connection is closed
    }
    transaction.error = ConnectionError::IO_ERROR;
}

/**
 *  Send Response
 *
 *  @param transaction       maintains a request and response message
 *
 *  @return true if the operation was successful, false otherwise
 */

bool
Connection::sendResponse(Transaction& transaction) {

    try {
        uint32_t messageSize = transaction.response->serializedSize();
        unique_ptr<char> messageBuffer(new char[messageSize]);
        transaction.response->serializeData(messageBuffer.get(), messageSize);

        KineticMessageFraming messageFraming(KINETIC_MESSAGE_FRAMING_MAGIC_NUMBER, messageSize, transaction.response->value().size());
        m_stream->write((const char*) &messageFraming, sizeof(messageFraming));

        m_stream->write(messageBuffer.get(), messageSize);
        if (!transaction.response->value().empty())
            m_stream->write(transaction.response->value().c_str(), transaction.response->value().size());

        if (systemControl.debugEnabled())
            MessageTrace::outputContents(messageFraming, transaction.response.get());
    }
    catch (std::exception& ex) {
        if (string(ex.what()) != "socket closed")
            LOG(ERROR) << "Connection::sendResponse exception: " << ex.what();
        // if write error, close connection
        // if serializeData error, what?, INTERNAL ERROR
        return false;
    }
    return true;
}

