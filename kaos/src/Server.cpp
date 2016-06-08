/*
 * Copyright (c) 2014-2016 Western Digital Technologies, Inc. <copyrightagent@wdc.com>
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
#include <signal.h>
#include <stdint.h>
#include <unistd.h>
#include <mutex>
#include <string>
#include <iostream>
#include <condition_variable>
#include "Server.hpp"
#include "Logger.hpp"
#include "SslStream.hpp"
#include "Connection.hpp"
#include "GlobalConfig.hpp"
#include "ServerSettings.hpp"
#include "ClearTextStream.hpp"
#include "MessageStatistics.hpp"
#include "ConnectionListener.hpp"

/*
 * Global Variable
 *
 * The log control and global configuration classes must be created first because they are used by
 * almost all the other classes.
 */
LogControl logControl;
GlobalConfig globalConfig;

/*
 * Private Variables
 */
static Server server;
static std::condition_variable serverTerminated;

/**
 * Terminates the program due to being signalled to exit (using SIGTERM).
 *
 * @param   signum  Signal number sent to process
 */
static void terminateProgram(int signum) {
    /*
     * Signal the server to terminate (and eliminate the unused args warning for signum).
     */
    serverTerminated.notify_one();
    static_cast<void>(signum);
}

/**
 * Initialize the server object, which consists of its settings, object store, statistics,
 * connection listeners, and its heartbeat provider
 */
Server::Server()
    : m_settings(), m_objectStore(new RocksDbObjectStore()), m_messageStatistics(),
      m_connectionList(), m_listenerList(), m_heartbeatProvider(), m_mutex() {
    ListenerInterfacePtr sslListener(new ConnectionListener<SslStream>(this, globalConfig.sslPort()));
    ListenerInterfacePtr clearTextListener(new ConnectionListener<ClearTextStream>(this, globalConfig.tcpPort()));
    m_listenerList.push_back(sslListener);
    m_listenerList.push_back(clearTextListener);
}

/**
 * The server's entry point.  It daemonizes the application (unless otherwise directed), starts the
 * TCP connection listeners and heartbeat provider, and then waits to be shutdown.
 *
 * @return  EXIT_SUCCESS if successful, EXIT_FAILURE otherwise
 */
int32_t Server::run() {
    /*
     * If the application is running in the foreground, output logs to stdout.
     */
    if (!globalConfig.runAsDaemon())
        logControl.setStandardOutEnabled(true);

    LOG(INFO) << "Starting Kaos application, version " << globalConfig.version()
              << " (running in " << (globalConfig.runAsDaemon() ? "background)" : "foreground)");

    /*
     * If the daemon is to run in the background, daemonize the process. That causes the process to
     * detach from it parent, detach from its controlling terminal, close all associated file
     * descriptors except stdin, stdout, and stderr which will be connected to dev/null, and change
     * to the root directory so that the daemon can't prevent the root file system from being
     * unmounted.
     */
    if ((globalConfig.runAsDaemon()) && (daemon(0, 0) != STATUS_SUCCESS)) {
        LOG(ERROR) << "Failed to become daemon: Error Code=" << errno << ", Description=" << strerror(errno);
        return EXIT_FAILURE;
    }

    /*
     * Open the object store, create the process ID file (used to get status and shutdown the
     * application), and load the sigterm handler.
     */
    if (!m_objectStore->open()) {
        LOG(ERROR) << "Failed to open object store";
        return EXIT_FAILURE;
    }

    FILE* file = fopen(globalConfig.pidFileName(), "w");
    if (file == nullptr) {
        LOG(ERROR) << "Failed to create PID file: Error Code=" << errno << ", Description=" << strerror(errno);
    }
    else {
        if (fprintf(file, "%i\n", getpid()) < 0) {
            LOG(ERROR) << "Failed to write PID file: Error Code=" << errno << ", Description=" << strerror(errno);
        }
        if (fclose(file) != STATUS_SUCCESS) {
            LOG(ERROR) << "Failed to close PID file: Error Code=" << errno << ", Description=" << strerror(errno);
        }
    }
    signal(SIGTERM, terminateProgram);

    /*
     * Starts the heartbeat message provider, which allows discovery of this Kinetic device.  Also,
     * starts the listener threads, which enables client communications.
     */
    m_heartbeatProvider.start();

    for (auto listener : m_listenerList)
        listener->start();

    /*
     * Block waiting to be shutdown (by the init.d kaos script stop command).
     */
    std::mutex terminationMutex;
    std::unique_lock<std::mutex> terminationLock(terminationMutex);
    serverTerminated.wait(terminationLock);
    LOG(INFO) << "Stopping application";

    /*
     * Stops the heartbeat message provider, which prevents discovery of this Kinetic device.  Also,
     * stops the listener threads, which disables client communications.
     */
    m_heartbeatProvider.stop();

    for (auto listener : m_listenerList)
        listener->stop();

    /*
     * Delete the process ID file and exit.
     */
    if (remove(globalConfig.pidFileName()) != STATUS_SUCCESS)
        LOG(ERROR) << "Failed to remove PID file: Error Code=" << errno << ", Description=" << strerror(errno);

    return EXIT_SUCCESS;
}

/**
 * Adds a connection to the manager's database and permits it to be used if the maximum number of
 * connections hasn't been reached.  Otherwise, it rejects the connection by throwing an exception,
 * which causes the connection to be closed.
 *
 * @param   connection  The connection being added
 *
 * @throws  A runtime error if the maximum number of connections are already open
 */
void Server::addConnection(Connection* connection) {
    std::unique_lock<std::mutex> scopedLock(m_mutex);
    if (m_connectionList.size() >= globalConfig.maxActiveConnections())
        throw std::runtime_error("No connections available");

    m_connectionList.push_back(connection);
}

/**
 * Removes the connection from the manager's database.
 *
 * @param   connection  The connection being removed
 */
void Server::removeConnection(Connection* connection) {
    std::unique_lock<std::mutex> scopedLock(m_mutex);
    m_connectionList.remove(connection);
    delete connection;
}

/**
 * Determines the number of active batch commands across all connections.
 *
 * @return  The number of active batch commands
 */
uint32_t Server::activeBatchCommands() {
    std::unique_lock<std::mutex> scopedLock(m_mutex);
    uint32_t batchCount = 0;
    for (auto connection : m_connectionList)
        batchCount += connection->activeBatchCommands();

    return batchCount;
}

/**
 * Entry point of the Kinetic object store application, which normally runs as a daemon but can be
 * instructed to run in the foreground.  The application will run until receiving a SIGTERM, which
 * is normally sent by the kaos start/stop script when called to stop.
 *
 * @return  EXIT_SUCCESS if successful, EXIT_FAILURE otherwise
 */
int32_t main() {
    return server.run();
}

