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
#ifndef MESSAGE_QUEUE_HPP
#define MESSAGE_QUEUE_HPP

/*
 * Include Files
 */
#include <stdint.h>
#include <deque>
#include <mutex>
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
    void send(MessageType& const message) {
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

    /**
     * Indicates if the queue is empty
     *
     * @return  true if there are no messages in the queue, false otherwise
     */
    bool empty() const {
        return m_queue.empty();
    }

private:

    std::mutex                  m_mutex;            //!< Ensures exclusive access to the queue
    std::condition_variable     m_accessControl;    //!< Object that coordinates access to the queue
    std::deque<MessageType>     m_queue;            //!< Message queue
};


#endif
