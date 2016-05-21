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
#include <unistd.h>
#include <thread>
#include "Common.hpp"
#include "Logger.hpp"
#include "SystemConfig.hpp"
#include "TcpTransport.hpp"
#include "ListenerInterface.hpp"
#include "CommunicationsManager.hpp"

/**
 * A stream agnostic connection listener for Kinetic clients.  Kinetic support both encrypted and
 * clear text data streams for its connections.  This listener is used for both.  When a client is
 * discovered through the listening port, a connection is created with the proper data stream.
 */
template <class StreamType> class ConnectionListener : public ListenerInterface {

public:

    /**
     * ConnectionListener Constructor
     *
     * @param   communicationsManager   Manager of the connections to be created
     * @param   port                    The port to listen on for new connections
     */
    explicit ConnectionListener(CommunicationsManager* communicationsManager, uint32_t port)
        : m_communicationsManager(communicationsManager), m_port(port), m_terminated(false), m_thread(nullptr) {
    }

    /**
     * Started
     *
     * @return true if the listener has started, false otherwise
     *
     * Indicates if the listener has started.
     */
    inline bool started() {return (m_thread != nullptr);}

    /**
     * Start
     *
     * @return true if the thread was successfully created
     *
     * Starts the listener.
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
            LOG(ERROR) << "Failed to create TCP Transport thread: Description=" << e.what();
            m_thread = nullptr;
        }
        return false;
    }

    /**
     * Stop
     *
     * Terminates the listener.
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
     *
     * Loops waiting for a client to attempt a connection through the listening port.  When an
     * attempt is make, a connection and stream object are created to service the client.  If a
     * critical error is encountered, wait a period of time before retrying the connection.
     */
    void listenerThread() {

        const uint32_t BACKOFF_PERIOD(60);
        while (!m_terminated) {
            try {
                ClientServerConnectionInfo clientServerConnectionInfo = TcpTransport::serverConnect(m_port, m_listeningSocket);
                StreamInterface* stream = static_cast<StreamInterface*>(new StreamType(clientServerConnectionInfo.socketDescriptor()));
                m_communicationsManager->addConnection(new Connection(m_communicationsManager, stream, clientServerConnectionInfo));
            }
            catch (std::exception& ex) {
                LOG(ERROR) << "Exception encounter: " << ex.what();
                sleep(BACKOFF_PERIOD);
            }
            catch (...) {
                LOG(ERROR) << "Unexpected exception encounter";
                sleep(BACKOFF_PERIOD);
            }
        }
    }

    /*
     * Private Data Members
     */
    CommunicationsManager*  m_communicationsManager;    //!< Manager of the connection
    uint32_t                m_port;                     //!< Listening port
    bool                    m_terminated;               //!< Indicates if listener is terminated
    int32_t                 m_listeningSocket;          //!< File descriptor of socket listening on
    std::thread*            m_thread;                   //!< Listening thread

    DISALLOW_COPY_AND_ASSIGN(ConnectionListener);
};

#endif
