/*
    Copyright (c) [2014 - 2015] Western Digital Technologies, Inc. All rights reserved.
*/

#pragma once
#ifndef CONNECTION_HANDLER_HPP
#define CONNECTION_HANDLER_HPP

/*
    Include Files
*/

#include <stdint.h>
#include <list>
#include <thread>
#include <string>
#include <memory>
#include "Common.hpp"
#include "KineticMessage.hpp"
#include "StreamInterface.hpp"

enum class ConnectionError {
    NONE          = 0,
    VALUE_TOO_BIG = 1,
    IO_ERROR      = 2,
};


class ConnectionContext {
public:
    explicit ConnectionContext(int64_t connectionId) : m_connectionId(connectionId), m_previousSequence(0), m_processedFirstRequest(false) {}

    inline int64_t connectionId() {return m_connectionId;}
    inline int64_t previousSequence() {return m_previousSequence;}
    inline bool processedFirstRequest() {return m_processedFirstRequest;}

    inline void setPreviousSequence(int64_t previousSequence) {m_previousSequence = previousSequence;}
    inline void setProcessedFirstRequest(int64_t processedFirstRequest) {m_processedFirstRequest = processedFirstRequest;}

private:

    int64_t     m_connectionId;
    int64_t     m_previousSequence;
    bool        m_processedFirstRequest;

    DISALLOW_COPY_AND_ASSIGN(ConnectionContext);
};

/*
    Incomplete Class Definitions (to avoid cirular dependancies)
*/

class TransportInterface;
class MessageHandler;

/*
    Connection Handler

    Responsible for handling a single connection.
*/

class ConnectionHandler {
public:

    /*
        Constructor/Destructor
    */

    ConnectionHandler(TransportInterface* transport, StreamInterface* stream, uint32_t serverPort,
                      std::string serverIpAddress, uint32_t clientPort, std::string clientIpAddress);
    ~ConnectionHandler();

    /*
        Public Member Functions
    */

    bool sendResponse(KineticMessagePtr& responseMessage);
    ConnectionContext& getContext() { return m_context;}
    TransportInterface* transport() {return m_transport;}

private:

    void receiveRequest(KineticMessagePtr& requestMessage, ConnectionError& error, std::string& errorMessage);
    void sendUnsolicitedStatusMessage();
    void run();

    /*
        Private Data Member
    */

    TransportInterface* const  m_transport;             //!< Transport assoicated with the connection
    MessageHandler* const      m_messageHandler;        //!< Handler for all messages received
    StreamInterface* const     m_stream;                //!< I/O Stream
    const uint32_t              m_serverPort;           //!< Server's TCP port number
    const std::string           m_serverIpAddress;      //!< Server's IP address
    const uint32_t              m_clientPort;           //!< Client's TCP port number
    const std::string           m_clientIpAddress;      //!< Client's IP address
    std::thread* const         m_thread;                //!< Thread that receives messages
    ConnectionContext           m_context;              //!< Context information for connection

    DISALLOW_COPY_AND_ASSIGN(ConnectionHandler);
};

#endif
