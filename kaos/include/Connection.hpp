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
#pragma once
#ifndef CONNECTION_HPP
#define CONNECTION_HPP

/*
 * Include Files
 */
#include <stdint.h>
#include <map>
#include <list>
#include <mutex>
#include <thread>
#include <string>
#include <memory>
#include <atomic>
#include "Server.hpp"
#include "KineticMessage.hpp"
#include "StreamInterface.hpp"
#include "ClientServerConnectionInfo.hpp"

/*
 * Incomplete Class Definition
 */
class Server;
class Transaction;

/**
 * Describes a single Kinetic network connection between the server and a client.
 */
class Connection {
public:

    /*
     * Constructor/Destructor
     */
    Connection(Server* server, StreamInterface* stream, ClientServerConnectionInfo clientServerConnectionInfo);
    ~Connection();

    /*
     * Public Member Functions
     */
    bool sendResponse(KineticMessagePtr response);

    /*
     * Public Accessors
     */
    inline Server* server() {return m_server;}
    inline int64_t connectionId() {return m_connectionId;}
    inline int64_t previousSequence() {return m_previousSequence;}
    inline bool processedFirstRequest() {return m_processedFirstRequest;}
    inline void setPreviousSequence(int64_t previousSequence) {m_previousSequence = previousSequence;}
    inline void setProcessedFirstRequest(int64_t processedFirstRequest) {m_processedFirstRequest = processedFirstRequest;}
    inline uint32_t activeBatchCommands() {return m_batchListMap.size();}
    inline Security security() {return m_stream->security();}

    /*
     * Batch Functions
     */
    inline bool createBatchList(uint32_t batchId) {
        std::unique_lock<std::mutex> m_scopedLock(m_mutex);
        if (m_batchListMap.find(batchId) != m_batchListMap.end())
            return false;
        KineticMessageListPtr batchList(new KineticMessageList());
        m_batchListMap[batchId] = batchList;
        return true;
    }

    inline KineticMessageListPtr getBatchList(uint32_t batchId) {
        std::unique_lock<std::mutex> m_scopedLock(m_mutex);
        if (m_batchListMap.find(batchId) == m_batchListMap.end())  {
            KineticMessageListPtr nullListPtr;
            return nullListPtr;
        }
        return m_batchListMap[batchId];
    }

    inline bool deleteBatchList(uint32_t batchId) {
        std::unique_lock<std::mutex> m_scopedLock(m_mutex);
        return (m_batchListMap.erase(batchId) > 0);
    }

private:

    /*
     * Private Member Functions
     */
    void receiveRequest(KineticMessagePtr& request);
    void sendUnsolicitedStatusMessage();
    void run();

    /*
     * Private Data Member
     */
    Server*                 m_server;                   //!< Manager of the connection
    Security                m_security;                 //!< Connection's security (SSL or None)
    StreamInterface* const  m_stream;                   //!< Connection's I/O Stream (encrypted or clear text)
    const uint32_t          m_serverPort;               //!< Server's TCP port number
    const std::string       m_serverIpAddress;          //!< Server's IP address
    const uint32_t          m_clientPort;               //!< Client's TCP port number
    const std::string       m_clientIpAddress;          //!< Client's IP address
    std::thread* const      m_thread;                   //!< Thread that receives messages
    const int64_t           m_connectionId;             //!< Identification number for connection
    std::atomic<int64_t>    m_previousSequence;         //!< Last request message sequence number
    std::atomic_bool        m_processedFirstRequest;    //!< Indicates if the first request has been processed yet
    KineticMessageListMap   m_batchListMap;             //!< Lists of batch commands indexed by batch ID
    std::mutex              m_mutex;                    //!< Mutex used to make class thread safe
};

#endif
