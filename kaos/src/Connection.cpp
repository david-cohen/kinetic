/*
 * Copyright (c) 2014-2016 Western Digital Technologies, Inc. <copyrightagent@wdc.com>
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
#include <atomic>
#include <string>
#include <sstream>
#include <iostream>
#include <exception>
#include "Logger.hpp"
#include "Server.hpp"
#include "KineticLog.hpp"
#include "Connection.hpp"
#include "Transaction.hpp"
#include "MessageTrace.hpp"
#include "GlobalConfig.hpp"
#include "KineticMessage.hpp"
#include "MessageHandler.hpp"

/*
 * Used Namespace Members
 */
using com::seagate::kinetic::proto::Command;
using com::seagate::kinetic::proto::Command_Header;
using com::seagate::kinetic::proto::Command_GetLog;
using com::seagate::kinetic::proto::Command_GetLog_Type_LIMITS;
using com::seagate::kinetic::proto::Command_GetLog_Type_CONFIGURATION;
using com::seagate::kinetic::proto::Command_Status_StatusCode_SUCCESS;
using com::seagate::kinetic::proto::Command_Status_StatusCode_INVALID_REQUEST;
using com::seagate::kinetic::proto::Command_Status_StatusCode_CONNECTION_TERMINATED;
using com::seagate::kinetic::proto::Message_AuthType_UNSOLICITEDSTATUS;

/*
 * Private Data Objects
 */
static std::atomic<int64_t> nextConnectionId(1);

/**
 * Initializes the Connection object.
 *
 * @param   server                      Manager of the connection
 * @param   stream                      Data stream to be used for this connection
 * @param   lientServerConnectionInfo   Information about the client and server in the connection
 */
Connection::Connection(Server* server, StreamInterface* stream, ClientServerConnectionInfo clientServerConnectionInfo)
    : m_server(server), m_stream(stream), m_serverPort(clientServerConnectionInfo.serverPort()),
      m_serverIpAddress(clientServerConnectionInfo.serverIpAddress()), m_clientPort(clientServerConnectionInfo.clientPort()),
      m_clientIpAddress(clientServerConnectionInfo.clientIpAddress()), m_thread(new std::thread(&Connection::run, this)),
      m_connectionId(nextConnectionId++), m_previousSequence(0), m_processedFirstRequest(false) {

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
void Connection::run() {

    try {
        LOG(INFO) << "Connection opened, server=" << m_serverIpAddress << ":" << m_serverPort
                  << ", client=" << m_clientIpAddress << ":" << m_clientPort;

        /*
         * When a new connection is established, the Kinetic device sends an unsolicited status
         * message that describes some of the device's capabilities.
         */
        sendUnsolicitedStatusMessage();

        MessageHandler* messageHandler = new MessageHandler(this);
        for (;;) {

            /*
             * Block waiting for a request.  When received, have the message handler process it.
             * Since not all requests get a response (such as a batched put), check if there is a
             * response before attempting to send one.
             */
            Transaction* transaction = new Transaction();

            try {
                receiveRequest(transaction->request);

                // send to message handler thread
                messageHandler->processRequest(transaction);
            }
            catch (MessageException& messageException) {

                if (messageException.statusCode() == Command_Status_StatusCode_CONNECTION_TERMINATED)
                    break;

                messageHandler->processError(transaction, messageException.statusCode(), messageException.statusMessage());
            }

            if (transaction->response != nullptr)
                sendResponse(transaction->response);

            delete transaction;
        }
    }
    catch (std::exception& ex) {
        if (std::string(ex.what()) != "Socket closed")
            LOG(ERROR) << "Exception encounter: " << ex.what();
    }
    catch (...) {
        LOG(ERROR) << "Unexpected exception encounter";
    }

    LOG(INFO) << "Connection closed, server=" << m_serverIpAddress << ":" << m_serverPort
              << ", client=" << m_clientIpAddress << ":" << m_clientPort;

    m_server->removeConnection(this);
}

/**
 * Sends an Unsolicited Status Message when a connection is first established (following the Kinetic
 * protocol).
 */
void Connection::sendUnsolicitedStatusMessage() {

    KineticMessagePtr response(new KineticMessage());
    response->set_authtype(Message_AuthType_UNSOLICITEDSTATUS);
    Command* const command = response->mutable_command();
    Command_Header* const header = command->mutable_header();
    header->set_connectionid(m_connectionId);
    header->set_clusterversion(m_server->settings().clusterVersion());
    Command_GetLog* getLogResponse = command->mutable_body()->mutable_getlog();
    getLogResponse->add_types(Command_GetLog_Type_CONFIGURATION);
    KineticLog::getConfiguration(getLogResponse);
    getLogResponse->add_types(Command_GetLog_Type_LIMITS);
    KineticLog::getLimits(getLogResponse);
    command->mutable_status()->set_code(Command_Status_StatusCode_SUCCESS);
    response->build_commandbytes();
    sendResponse(response);
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
void Connection::receiveRequest(KineticMessagePtr& request) {

    /*
     * First, read in the framing data, which consists of a magic number, the size of the
     * protocol buffer message and the size of the (optional) value.  Then, validate the framing
     * data.  If the magic number is not correct or the sizes specified are invalid, throw an
     * exception, which will cause the connection to be fail.
     */
    KineticMessageFraming messageFraming;
    m_stream->read(reinterpret_cast<char*>(&messageFraming), sizeof(messageFraming));

    if (messageFraming.magicNumber() != KINETIC_MESSAGE_FRAMING_MAGIC_NUMBER)
        throw MessageException(Command_Status_StatusCode_CONNECTION_TERMINATED, "Invalid PDU magic number");

    uint32_t messageSize = messageFraming.messageSize();
    uint32_t valueSize = messageFraming.valueSize();

    if (messageSize == 0)
        throw MessageException(Command_Status_StatusCode_CONNECTION_TERMINATED, "message size too small");

    /*
     * If the size of the message exceeds the support maximum value, read and save as much as
     * possible so that the response will contain the correct header information.  Read and
     * dispose of the remaining data (which should be the value, not the command).
     */
    if (messageSize > globalConfig.maxMessageSize()) {
        std::unique_ptr<char> messageBuffer(new char[globalConfig.maxMessageSize()]);
        m_stream->read(messageBuffer.get(), messageSize);
        try {
            m_stream->blackHoleRead(messageSize - globalConfig.maxMessageSize());
            request->deserializeData(messageBuffer.get(), messageSize);
        }
        catch (std::exception& ex) {
            LOG(ERROR) << "Connection::receiveRequest exception: " << ex.what();
        }

        if (globalConfig.debugEnabled())
            MessageTrace::outputContents(messageFraming, request.get());

        throw MessageException(Command_Status_StatusCode_CONNECTION_TERMINATED, "message size too large");
    }

    /*
     * Read in the protocol buffer message.  If a value is included, also attempt to read in the
     * value. If the value is too large, read and discard the value then fail the request.
     * Otherwise, create a Kinetic Message to hold both the deserialized protocol buffer
     * message and its value.
     */
    std::unique_ptr<char> messageBuffer(new char[messageSize]);
    m_stream->read(messageBuffer.get(), messageSize);

    if (valueSize > globalConfig.maxValueSize()) {
        m_stream->blackHoleRead(valueSize);
        if (!request->deserializeData(messageBuffer.get(), messageSize))
            throw MessageException(Command_Status_StatusCode_CONNECTION_TERMINATED, "invalid message format");

        if (globalConfig.debugEnabled())
            MessageTrace::outputContents(messageFraming, request.get());

        std::stringstream errorStream;
        errorStream << "Value size (" << valueSize << " bytes) exceeded maximum supported size";
        throw MessageException(Command_Status_StatusCode_INVALID_REQUEST, errorStream.str());
    }

    if (valueSize > 0) {
        std::unique_ptr<char> valueBuffer(new char[valueSize]);
        m_stream->read(valueBuffer.get(), valueSize);
        request->setValue(valueBuffer.get(), valueSize);
    }

    if (!request->deserializeData(messageBuffer.get(), messageSize))
        throw MessageException(Command_Status_StatusCode_CONNECTION_TERMINATED, "invalid message format");

    if (globalConfig.debugEnabled())
        MessageTrace::outputContents(messageFraming, request.get());
}

/**
 * Sends a Kinetic response (serializing and framing the message before sending).
 *
 * @param   response    Response message to be sents
 *
 * @return  True if the operation was successful, false otherwise
 *
 * @throws  A runtime error if an error is encountered
 */
bool Connection::sendResponse(KineticMessagePtr response) {

    try {
        uint32_t messageSize = response->serializedSize();
        std::unique_ptr<char> messageBuffer(new char[messageSize]);
        response->serializeData(messageBuffer.get(), messageSize);

        KineticMessageFraming messageFraming(KINETIC_MESSAGE_FRAMING_MAGIC_NUMBER, messageSize, response->value().size());
        m_stream->write((const char*) &messageFraming, sizeof(messageFraming));

        m_stream->write(messageBuffer.get(), messageSize);
        if (!response->value().empty())
            m_stream->write(response->value().c_str(), response->value().size());

        if (globalConfig.debugEnabled())
            MessageTrace::outputContents(messageFraming, response.get());
    }
    catch (std::exception& ex) {
        if (std::string(ex.what()) != "Socket closed")
            LOG(ERROR) << "Connection::sendResponse exception: " << ex.what();
        return false;
    }
    return true;
}

