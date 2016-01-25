/*
 * Copyright (c) [2014 - 2016] Western Digital Technologies, Inc. All rights reserved.
 */

/*
 * Include Files
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
#include "KineticMessage.hpp"
#include "ServerSettings.hpp"
#include "MessageHandler.hpp"
#include "CommunicationsManager.hpp"

/*
 * Private Data Objects
 */
static std::atomic<int64_t> nextConnectionId(1);

/**
 * Initializes the Connection object.
 *
 * @param   stream                      Data stream to be used for this connection
 * @param   clientServerConnectionInfo  Information about the client and server in the connection
 */
Connection::Connection(StreamInterface* stream, ClientServerConnectionInfo clientServerConnectionInfo)
    : m_stream(stream), m_serverPort(clientServerConnectionInfo.serverPort()), m_serverIpAddress(clientServerConnectionInfo.serverIpAddress()),
      m_clientPort(clientServerConnectionInfo.clientPort()), m_clientIpAddress(clientServerConnectionInfo.clientIpAddress()),
      m_thread(new std::thread(&Connection::run, this)), m_connectionId(nextConnectionId++), m_previousSequence(0), m_processedFirstRequest(false) {

    m_thread->detach();
}

/*
 * Frees the allocated resources from the Connection object.
 */
Connection::~Connection() {
    delete m_stream;
    delete m_thread;
}

/**
 * Performs the work of the Connection handler (with a dedicated thread).  It blocks waiting to
 * receive a message, and when it does, it calls a message handler to process it.
 */
void
Connection::run() {

    try {
        LOG(INFO) << "Connection opened, server=" << m_serverIpAddress << ":" << m_serverPort
                  << ", client=" << m_clientIpAddress << ":" << m_clientPort;

        /*
         * When a new connection is established, the Kinetic device sends an unsolicited status
         * message that describes some of the device's capabilities.
         */
        sendUnsolicitedStatusMessage();

        for (;;) {

            /*
             * Block waiting for a request.  When received, have the message handler process it.
             * Since not all requests get a response (such as a batched put), check if there is a
             * response before attempting to send one.
             */
            Transaction transaction(this);
            receiveRequest(transaction);

            if (transaction.error == ConnectionError::IO_ERROR)
                break;

            MessageHandler::processRequest(transaction);

            if (transaction.response != nullptr)
                sendResponse(transaction);
        }
    }
    catch (std::exception& ex) {
        LOG(ERROR) << "Exception encounter: " << ex.what();
    }
    catch (...) {
        LOG(ERROR) << "Unexpected exception encounter";
    }

    LOG(INFO) << "Connection closed, server=" << m_serverIpAddress << ":" << m_serverPort
              << ", client=" << m_clientIpAddress << ":" << m_clientPort;

    communicationsManager.removeConnection(this);
}

/**
 * Sends an Unsolicited Status Message when a connection is first established (following the Kinetic
 * protocol).
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
 * Receives and deserializes a Kinetic Request.  It performs a blocking read from the stream and
 * returns when a complete message has been received (or an error is encountered).  It's
 * understanding of the Kinetic protocol is limited to the framing of the message.
 *
 * @param   transaction     Object where the received message will be put
 *
 * @throws  A runtime error if an error is encountered
 */
void
Connection::receiveRequest(Transaction& transaction) {

    try {

        /*
         * First, read in the framing data, which consists of a magic number, the size of the
         * protocol buffer message and the size of the (optional) value.  Then, validate the framing
         * data.  If the magic number is not correct or the sizes specified are invalid, throw an
         * exception, which will cause the connection to be fail.
         */
        KineticMessageFraming messageFraming;
        m_stream->read(reinterpret_cast<char*>(&messageFraming), sizeof(messageFraming));

        if (messageFraming.magicNumber() != KINETIC_MESSAGE_FRAMING_MAGIC_NUMBER)
            throw std::runtime_error("Invalid PDU magic number");

        uint32_t messageSize = messageFraming.messageSize();
        uint32_t valueSize = messageFraming.valueSize();

        if (messageSize == 0)
            throw std::runtime_error("message size too small");

        /*
         * If the size of the message exceeds the support maximum value, read and save as much as
         * possible so that the response will contain the correct header information.  Read and
         * dispose of the remaining data (which should be the value, not the command).
         */
        if (messageSize > systemConfig.maxMessageSize()) {
            std::unique_ptr<char> messageBuffer(new char[systemConfig.maxMessageSize()]);
            m_stream->read(messageBuffer.get(), messageSize);
            try {
                m_stream->blackHoleRead(messageSize - systemConfig.maxMessageSize());
                transaction.request->deserializeData(messageBuffer.get(), messageSize);
            }
            catch (std::exception& ex) {
                LOG(ERROR) << "Connection::receiveRequest exception: " << ex.what();
            }

            if (systemConfig.debugEnabled())
                MessageTrace::outputContents(messageFraming, transaction.request.get());

            throw std::runtime_error("message size too large");
        }

        /*
         * Read in the protocol buffer message.  If a value is included, also attempt to read in the
         * value. If the value is too large, read and discard the value then fail the request.
         * Otherwise, create a Kinetic Message to hold both the deserialized protocol buffer
         * message and its value.
         */
        std::unique_ptr<char> messageBuffer(new char[messageSize]);
        m_stream->read(messageBuffer.get(), messageSize);

        if (valueSize > systemConfig.maxValueSize()) {
            m_stream->blackHoleRead(valueSize);
            if (!transaction.request->deserializeData(messageBuffer.get(), messageSize))
                throw std::runtime_error("invalid message format");

            if (systemConfig.debugEnabled())
                MessageTrace::outputContents(messageFraming, transaction.request.get());

            transaction.error = ConnectionError::VALUE_TOO_BIG;
            std::stringstream errorStream;
            errorStream << "Value size (" << valueSize << " bytes) exceeded maximum supported size";
            transaction.errorMessage = errorStream.str();
            return;
        }

        if (valueSize > 0) {
            std::unique_ptr<char> valueBuffer(new char[valueSize]);
            m_stream->read(valueBuffer.get(), valueSize);
            transaction.request->setValue(valueBuffer.get(), valueSize);
        }

        if (!transaction.request->deserializeData(messageBuffer.get(), messageSize))
            throw std::runtime_error("invalid message format");

        if (systemConfig.debugEnabled())
            MessageTrace::outputContents(messageFraming, transaction.request.get());

        transaction.error = ConnectionError::NONE;
        return;
    }
    catch (std::exception& ex) {
        if (std::string(ex.what()) != "socket closed")
            LOG(ERROR) << "Connection::receiveRequest exception: " << ex.what();
    }
    transaction.error = ConnectionError::IO_ERROR;
}

/**
 * Sends a Kinetic response (serializing and framing the message before sending).
 *
 * @param   transaction     Object containing the response to be sent
 *
 * @return  True if the operation was successful, false otherwise
 *
 * @throws  A runtime error if an error is encountered
 */
bool
Connection::sendResponse(Transaction& transaction) {

    try {
        uint32_t messageSize = transaction.response->serializedSize();
        std::unique_ptr<char> messageBuffer(new char[messageSize]);
        transaction.response->serializeData(messageBuffer.get(), messageSize);

        KineticMessageFraming messageFraming(KINETIC_MESSAGE_FRAMING_MAGIC_NUMBER, messageSize, transaction.response->value().size());
        m_stream->write((const char*) &messageFraming, sizeof(messageFraming));

        m_stream->write(messageBuffer.get(), messageSize);
        if (!transaction.response->value().empty())
            m_stream->write(transaction.response->value().c_str(), transaction.response->value().size());

        if (systemConfig.debugEnabled())
            MessageTrace::outputContents(messageFraming, transaction.response.get());
    }
    catch (std::exception& ex) {
        if (std::string(ex.what()) != "socket closed")
            LOG(ERROR) << "Connection::sendResponse exception: " << ex.what();
        return false;
    }
    return true;
}

