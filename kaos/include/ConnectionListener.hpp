/*
 * Copyright (c) [2016] Western Digital Technologies, Inc. All rights reserved.
 */
#pragma once
#ifndef CONNECTION_LISTENER_HPP
#define CONNECTION_LISTENER_HPP

/*
 * Include Files
 */
#include <stdint.h>
#include <thread>
#include "Common.hpp"
#include "SystemConfig.hpp"
#include "TcpTransport.hpp"
#include "ListenerInterface.hpp"
#include "CommunicationsManager.hpp"

/**
 * Connection Listener
 */
template <class StreamType> class ConnectionListener : public ListenerInterface {

public:

    /**
     * ConnectionListener Constructor
     *
     * @param  port     The port to listen on for new connections
     */
    explicit ConnectionListener(uint32_t port)
        : m_port(port), m_terminated(false), m_thread(nullptr) {
    }

    inline bool started() {return (m_thread != nullptr);}

    /**
     * Start
     *
     * @return true if the thread was successfully created
     */
    bool start() {

        try {
            if (!started() && !m_terminated) {
                m_listeningSocket = TcpTransport::serverSetup(m_port);
                m_thread = new std::thread(&ConnectionListener::listenerThread, this);
                return true;
            }
        }
        catch (std::exception& e) {
            LOG(ERROR) << "Failed to create TCP Transport thread: description=" << e.what();
            m_thread = nullptr;
        }
        return false;
    }

    /**
     * Stop
     *
     * @return true if the thread was successfully created
     */
    void stop() {
        if (started() && !m_terminated) {
            m_terminated = true;
            TcpTransport::serverShutdown(m_listeningSocket);
        }
    }

private:

    /**
     * Listener Thread
     */
    void listenerThread() {

        while (!m_terminated) {
            try {
                ClientServerConnectionInfo clientServerConnectionInfo = TcpTransport::serverConnect(m_port, m_listeningSocket);
                StreamInterface* stream = static_cast<StreamInterface*>(new StreamType(clientServerConnectionInfo.socketDescriptor()));
                communicationsManager.addConnection(new Connection(stream, clientServerConnectionInfo));
            }
            catch (std::exception& ex) {
                LOG(ERROR) << "Exception encounter: " << ex.what();
                // maybe sleep for a short time
            }
            catch (...) {
                LOG(ERROR) << "Unexpected exception encounter";
                // maybe sleep for a short time
            }
        }
    }

    uint32_t        m_port;             //!< Listening port
    bool            m_terminated;       //!< Indicates listener is terminated
    int32_t         m_listeningSocket;  //!< File descriptor of socket listening on
    std::thread*    m_thread;           //!< Listening thread

    DISALLOW_COPY_AND_ASSIGN(ConnectionListener);
};

#endif
