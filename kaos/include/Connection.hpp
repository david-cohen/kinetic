/*
    Copyright (c) [2014 - 2015] Western Digital Technologies, Inc. All rights reserved.
*/

#pragma once
#ifndef CONNECTION_HPP
#define CONNECTION_HPP

/*
    Include Files
*/

#include <stdint.h>
#include <map>
#include <list>
#include <mutex>
#include <thread>
#include <string>
#include <memory>
#include <atomic>
#include "Common.hpp"
#include "AccessControl.hpp"
#include "KineticMessage.hpp"
#include "StreamInterface.hpp"

typedef std::shared_ptr<KineticMessageList> BatchListPtr;
typedef std::map<uint32_t, BatchListPtr> BatchListMap;

enum class ConnectionError {
    NONE          = 0,
    VALUE_TOO_BIG = 1,
    IO_ERROR      = 2,
};

/*
    Incomplete Class Definitions (to avoid cirular dependancies)
*/

class TransportInterface;
class MessageHandler;
class Connection;

class Transaction {
public:
    Connection* const   connection;
    KineticMessagePtr   request;
    KineticMessagePtr   response;
    ConnectionError     error;
    std::string         errorMessage;
    AccessControlPtr    accessControl;

    explicit Transaction(Connection* transactionConnection)
        : connection(transactionConnection), request(new KineticMessage()), response(new KineticMessage()), error(ConnectionError::NONE) {}
};

/*
    Connection

    Used to manage a single connection.
*/

class Connection {
public:

    /*
        Constructor/Destructor
    */

    Connection(TransportInterface* transport, StreamInterface* stream, uint32_t serverPort,
               std::string serverIpAddress, uint32_t clientPort, std::string clientIpAddress);
    ~Connection();

    /*
        Public Member Functions
    */

    bool sendResponse(Transaction& transaction);

    inline TransportInterface* transport() {return m_transport;}
    inline int64_t connectionId() {return m_connectionId;}
    inline int64_t previousSequence() {return m_previousSequence;}
    inline bool processedFirstRequest() {return m_processedFirstRequest;}
    inline void setPreviousSequence(int64_t previousSequence) {m_previousSequence = previousSequence;}
    inline void setProcessedFirstRequest(int64_t processedFirstRequest) {m_processedFirstRequest = processedFirstRequest;}
    inline uint32_t batchCount() {return m_batchListMap.size();}

    inline bool createBatchList(uint32_t batchId) {
        std::unique_lock<std::mutex> m_scopedLock(m_mutex);
        if (m_batchListMap.find(batchId) != m_batchListMap.end())
            return false;
        BatchListPtr batchList(new KineticMessageList());
        m_batchListMap[batchId] = batchList;
        return true;
    }

    inline BatchListPtr getBatchList(uint32_t batchId) {
        std::unique_lock<std::mutex> m_scopedLock(m_mutex);
        if (m_batchListMap.find(batchId) == m_batchListMap.end())  {
            BatchListPtr nullListPtr;
            return nullListPtr;
        }
        return m_batchListMap[batchId];
    }

    inline bool deleteBatchList(uint32_t batchId) {
        std::unique_lock<std::mutex> m_scopedLock(m_mutex);
        return (m_batchListMap.erase(batchId) > 0);
    }

private:

    void receiveRequest(Transaction& transaction);
    void sendUnsolicitedStatusMessage();
    void run();

    /*
        Private Data Member
    */

    TransportInterface* const   m_transport;            //!< Transport assoicated with the connection
    StreamInterface* const      m_stream;               //!< I/O Stream
    const uint32_t              m_serverPort;           //!< Server's TCP port number
    const std::string           m_serverIpAddress;      //!< Server's IP address
    const uint32_t              m_clientPort;           //!< Client's TCP port number
    const std::string           m_clientIpAddress;      //!< Client's IP address
    std::thread* const          m_thread;               //!< Thread that receives messages
    const int64_t               m_connectionId;
    std::atomic<int64_t>        m_previousSequence;
    std::atomic_bool            m_processedFirstRequest;
    BatchListMap                m_batchListMap;
    std::mutex                  m_mutex;

    DISALLOW_COPY_AND_ASSIGN(Connection);
};

#endif
