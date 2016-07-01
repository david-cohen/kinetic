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
#include <atomic>
#include <string>
#include <exception>
#include <sstream>
#include "Logger.hpp"
#include "Server.hpp"
#include "Connection.hpp"
#include "Transaction.hpp"
#include "MessageTrace.hpp"
#include "GlobalConfig.hpp"
#include "KineticMessage.hpp"
#include "MessageHandler.hpp"

/*
 * Private Constants
 */
static const uint32_t RECEIVER_THREAD_ID(0);
static const uint32_t SCHEDULER_THREAD_ID(1);
static const uint32_t TRANSMITTER_THREAD_ID(2);

/*
 * Private Data Objects
 */
static std::atomic<int64_t> nextConnectionId(1);

/**
 * Initializes the Connection object.
 *
 * @param   server                      Manager of the connection
 * @param   stream                      Data stream to be used for this connection
 * @param   clientServerConnectionInfo  Information about the client and server in the connection
 */
Connection::Connection(Server* server, StreamInterface* stream, ClientServerConnectionInfo clientServerConnectionInfo)
    : m_server(server), m_messageHandler(new MessageHandler(this)), m_stream(stream), m_schedulerQueue(), m_transmitterQueue(),
      m_serverPort(clientServerConnectionInfo.serverPort()), m_serverIpAddress(clientServerConnectionInfo.serverIpAddress()),
      m_clientPort(clientServerConnectionInfo.clientPort()), m_clientIpAddress(clientServerConnectionInfo.clientIpAddress()),
      m_connectionId(nextConnectionId++), m_previousSequence(0), m_processedFirstRequest(false), m_terminated(false),
      m_activeThreads((1 << RECEIVER_THREAD_ID) | (1 << SCHEDULER_THREAD_ID) | (1 << TRANSMITTER_THREAD_ID)),
      m_receiverThread(new std::thread(&Connection::receiver, this)),
      m_transmitterThread(new std::thread(&Connection::scheduler, this)),
      m_schedulerThread(new std::thread(&Connection::transmitter, this)) {

    m_receiverThread->detach();
    m_transmitterThread->detach();
    m_schedulerThread->detach();

    LOG(INFO) << "Connection opened, server=" << m_serverIpAddress << ":" << m_serverPort
              << ", client=" << m_clientIpAddress << ":" << m_clientPort;

    /*
     * When a new connection is established, the Kinetic device sends an unsolicited status
     * message that describes some of the device's capabilities.
     */
    Transaction* transaction = new Transaction();
    m_messageHandler->buildUnsolicitedStatusMessage(this, transaction->response());
    m_transmitterQueue.add(transaction);
}

/*
 * Frees the allocated resources from the Connection object.
 */
Connection::~Connection() {
    LOG(INFO) << "Connection closed, server=" << m_serverIpAddress << ":" << m_serverPort
              << ", client=" << m_clientIpAddress << ":" << m_clientPort;

    delete m_stream;
    delete m_receiverThread;
    delete m_transmitterThread;
    delete m_schedulerThread;
}

/**
 * Receives and deserializes a Kinetic Requests.  It performs a blocking read from the stream and
 * returns when a complete message has been received (or an error is encountered).  It's
 * understanding of the Kinetic protocol is limited to the framing of the message.  The following
 * framing errors will result in a response with an "invalid request" status code:
 *     The value size is too large
 * The following framing errors will result in the connection being terminated:
 *     Incorrect PDU magic number
 *     Total message size is too small
 *     Total message size is too large
 *     Invalid message format (failed protocol buffer deserialization)
 */
void Connection::receiver() {
    Transaction* transaction(nullptr);
    try {
        /*
         * Receive requests until terminated.
         */
        while (!m_terminated) {
            transaction = new Transaction();
            /*
             * First, read in the framing data, which consists of a magic number, the size of the
             * protocol buffer message and the size of the (optional) value.  Then, validate the framing
             * data.  If the magic number is not correct or the sizes specified are invalid, throw an
             * exception, which will cause the connection to closed.
             */
            KineticMessageFraming messageFraming;
            m_stream->read(reinterpret_cast<char*>(&messageFraming), sizeof(messageFraming));

            if (messageFraming.magicNumber() != KINETIC_MESSAGE_FRAMING_MAGIC_NUMBER)
                throw std::runtime_error("Invalid PDU magic number");

            uint32_t messageSize = messageFraming.messageSize();
            uint32_t valueSize = messageFraming.valueSize();

            if (messageSize == 0)
                throw std::runtime_error("Message size too small");

            KineticMessage& request = transaction->request();
            /*
             * If the size of the message exceeds the support maximum value, read and save as much as
             * possible so that the response will contain the correct header information.  Then,
             * read and dispose of the remaining data (which should be the value, not the command).
             */
            if (messageSize > globalConfig.maxMessageSize()) {
                std::unique_ptr<char> messageBuffer(new char[globalConfig.maxMessageSize()]);
                m_stream->read(messageBuffer.get(), messageSize);
                try {
                    m_stream->blackHoleRead(messageSize - globalConfig.maxMessageSize());
                    request.deserializeData(messageBuffer.get(), messageSize);
                }
                catch (std::exception& ex) {
                    LOG(ERROR) << "Exception while receiving request: " << ex.what();
                }

                if (globalConfig.debugEnabled())
                    MessageTrace::outputContents(messageFraming, &request);

                throw std::runtime_error("Message size too large");
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
                if (!request.deserializeData(messageBuffer.get(), messageSize))
                    throw std::runtime_error("Invalid message format");

                if (globalConfig.debugEnabled())
                    MessageTrace::outputContents(messageFraming, &request);

                std::stringstream errorStream;
                errorStream << "Value size (" << valueSize << " bytes) exceeded maximum supported size";
                m_messageHandler->buildResponseWithError(transaction, com::seagate::kinetic::proto::Command_Status_StatusCode_INVALID_REQUEST,
                        errorStream.str());
                m_transmitterQueue.add(transaction);
                continue;
            }

            if (valueSize > 0) {
                std::unique_ptr<char> valueBuffer(new char[valueSize]);
                m_stream->read(valueBuffer.get(), valueSize);
                request.setValue(valueBuffer.get(), valueSize);
            }

            if (!request.deserializeData(messageBuffer.get(), messageSize))
                throw std::runtime_error("Invalid message format");

            if (globalConfig.debugEnabled())
                MessageTrace::outputContents(messageFraming, &request);
            m_schedulerQueue.add(transaction);
        }
    }
    catch (std::exception& ex) {
        if (std::string(ex.what()) != "Socket closed")
            LOG(ERROR) << "Exception encounter: " << ex.what();

        delete transaction;
    }

    tearDownThread(RECEIVER_THREAD_ID);
}

/**
 * Sends Kinetic responses (serializing and framing the message before sending).
 */
void Connection::transmitter() {
    try {
        for (;;) {
            std::unique_ptr<Transaction> transaction(m_transmitterQueue.remove());

            if (m_terminated)
                break;


            if (transaction->hasResponse()) {
                KineticMessage& response = transaction->response();
                /*
                 * Convert the message into its serialized proto-buffer format.
                 */
                uint32_t messageSize = response.serializedSize();
                std::unique_ptr<char> messageBuffer(new char[messageSize]);
                response.serializeData(messageBuffer.get(), messageSize);

                /*
                 * Create the framing for the message and sent it (it precedes the message).
                 */
                KineticMessageFraming messageFraming(KINETIC_MESSAGE_FRAMING_MAGIC_NUMBER, messageSize, response.value().size());
                m_stream->write((const char*) &messageFraming, sizeof(messageFraming));

                /*
                 * Send the message and its optional value (which is not serialized).
                 */
                m_stream->write(messageBuffer.get(), messageSize);
                if (!response.value().empty())
                    m_stream->write(response.value().c_str(), response.value().size());

                if (globalConfig.debugEnabled())
                    MessageTrace::outputContents(messageFraming, &response);
            }
        }
    }
    catch (std::exception& ex) {
        if (std::string(ex.what()) != "Socket closed")
            LOG(ERROR) << "Exception encounter: " << ex.what();
    }

    tearDownThread(TRANSMITTER_THREAD_ID);
}

/**
 * Process the request.  In the future this is where the requests will be scheduled for processing.
 */
void Connection::scheduler() {
    while (!m_terminated) {
        Transaction* transaction(m_schedulerQueue.remove());
        m_messageHandler->processRequest(transaction);
        m_transmitterQueue.add(transaction);
    }
    tearDownThread(SCHEDULER_THREAD_ID);
}

/**
 * Terminates the specified thread and free the resources used by all the threads when the last
 * thread has been torn down.
 *
 * @param threadId  Identifies the thread being torn down.
 */
void Connection::tearDownThread(uint32_t threadId) {
    /*
     * Mark the connection as terminated and update the active threads indicator to show this thread
     * no longer as active.
     */
    m_terminated = true;
    std::unique_lock<std::mutex> m_scopedLock(m_mutex);
    m_activeThreads.reset(threadId);

    /*
     * If the other threads are still active, send them a message to wake them up and see that they
     * have been terminated.
     */
    if (m_activeThreads.test(SCHEDULER_THREAD_ID))
        m_schedulerQueue.add(new Transaction());

    if (m_activeThreads.test(TRANSMITTER_THREAD_ID))
        m_transmitterQueue.add(new Transaction());

    /*
     * When the last thread is torn down, free any resources still in the scheduler and transmitter
     * queue and remove the connection from the server's connection list.
     */
    if (m_activeThreads.none()) {
        while (!m_schedulerQueue.empty())
            delete m_schedulerQueue.remove();

        while (!m_transmitterQueue.empty())
            delete m_transmitterQueue.remove();

        m_server->removeConnection(this);
    }
}

