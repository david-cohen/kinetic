/*
 * Copyright (c) 2016 Western Digital Technologies, Inc.
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

#pragma once
#ifndef MESSAGE_QUEUE_HPP
#define MESSAGE_QUEUE_HPP

/*
 * Include Files
 */
#include <stdint.h>
#include <mutex>
#include <deque>
#include <utility>
#include <condition_variable>

/**
 * A thread-safe message queue that allows message passing between threads.
 */
template <typename MessageType> class MessageQueue {

public:

    /**
     * Sends a message by placing it at the end of a queue.
     *
     * @param   message     The message to be sent
     */
    void send(MessageType const& message) {
        std::lock_guard<std::mutex> scopedLock(m_mutex);
        m_queue.push_back(std::move(message));
        m_accessControl.notify_one();
    }

    /**
     * Receives a message from the head of a queue (blocking until a message is available).
     *
     * @return  the message
     */
    MessageType receive() {
        std::unique_lock<std::mutex> scopedLock(m_mutex);
        m_accessControl.wait(scopedLock, [this] {return !m_queue.empty();});
        MessageType message = std::move(m_queue.front());
        m_queue.pop_front();
        return message;
    }

private:

    std::mutex                      m_mutex;            //!< Ensures exclusive access to the queue
    std::condition_variable         m_accessControl;    //!< Object that coordinates access to the queue
    std::deque<MessageType>         m_queue;            //!< Message queue
};


#endif
