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
#include <atomic>
#include <bitset>
#include <memory>
#include <string>
#include <thread>
#include "Server.hpp"
#include "MessageQueue.hpp"
#include "KineticMessage.hpp"
#include "StreamInterface.hpp"
#include "ClientServerConnectionInfo.hpp"

/*
 * Incomplete Class Definition
 */
class Server;
class Transaction;
class MessageHandler;

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
     * Public Accessors
     */
    inline Server* server() const {return m_server;}
    inline int64_t connectionId() const {return m_connectionId;}
    inline int64_t previousSequence() const {return m_previousSequence;}
    inline bool processedFirstRequest() const {return m_processedFirstRequest;}
    inline uint32_t activeBatchCommands() {return m_batchListMap.size();}
    inline Security security() {return m_stream->security();}
    inline void setPreviousSequence(int64_t previousSequence) {m_previousSequence = previousSequence;}
    inline void setProcessedFirstRequest(int64_t processedFirstRequest) {m_processedFirstRequest = processedFirstRequest;}

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
    void receiver();
    void scheduler();
    void transmitter();
    void tearDownThread(uint32_t threadIdBitMask);

    /*
     * Private Data Member
     */
    Server* const                   m_server;                   //!< Manager of the connection
    MessageHandler* const           m_messageHandler;           //!< Message handler for the connection
    StreamInterface* const          m_stream;                   //!< Connection's I/O Stream (encrypted or clear text)
    MessageQueue<Transaction*>      m_schedulerQueue;           //!< Queue containing requests to be scheduled
    MessageQueue<Transaction*>      m_transmitterQueue;         //!< Queue containing responses to be transmitted
    const uint32_t                  m_serverPort;               //!< Server's TCP port number
    const std::string               m_serverIpAddress;          //!< Server's IP address
    const uint32_t                  m_clientPort;               //!< Client's TCP port number
    const std::string               m_clientIpAddress;          //!< Client's IP address
    const int64_t                   m_connectionId;             //!< Identification number for connection
    std::atomic<int64_t>            m_previousSequence;         //!< Last request message sequence number
    std::atomic_bool                m_processedFirstRequest;    //!< Indicates if the first request has been processed yet
    std::atomic_bool                m_terminated;               //!< True if the connection is to be closed
    KineticMessageListMap           m_batchListMap;             //!< Lists of batch commands indexed by batch ID
    std::mutex                      m_mutex;                    //!< Mutex used to make class thread safe
    std::bitset<3>                  m_activeThreads;            //!< Indicates which threads are running
    std::thread* const              m_receiverThread;           //!< Thread that receives messages
    std::thread* const              m_transmitterThread;        //!< Thread that receives messages
    std::thread* const              m_schedulerThread;          //!< Thread that schedules when messages are to be processed
};

#endif
