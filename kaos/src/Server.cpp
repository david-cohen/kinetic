/*
 * Copyright (c) [2014 - 2016] Western Digital Technologies, Inc.
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
#include "ObjectStore.hpp"
#include "SystemConfig.hpp"
#include "ServerSettings.hpp"
#include "MessageStatistics.hpp"
#include "CommunicationsManager.hpp"

/*
 * Global Variable
 *
 * The System Configuration class must be declared first because other classes depend on using its
 * values.
 */
LogControl logControl;
SystemConfig systemConfig;

/*
 * Private Variables
 */
static std::mutex daemonMutex;
static std::unique_lock<std::mutex> daemonLock(daemonMutex);
static std::condition_variable daemonTerminated;

/**
 * Terminates the program due to being signalled to exit (using SIGTERM).
 *
 * @param   signum  Signal number sent to process
 */
void terminateProgram(int signum) {

    /*
     * Signal the daemon to terminate (and eliminate the unused args warning for signum).
     */
    daemonTerminated.notify_one();
    static_cast<void>(signum);
}

Server::Server(std::string pidFileName, bool foreground)
    : m_pidFileName(!pidFileName.empty() ? pidFileName : systemConfig.defaultPidFileName()), m_foreground(foreground),
      m_communicationsManager(this), m_settings(), m_messageStatistics(), m_objectStore() {
}

/**
 *
 * @return  EXIT_SUCCESS if successful, EXIT_FAILURE otherwise
 */
int32_t Server::run() {

    if (m_foreground)
        logControl.setStandardOutEnabled(true);

    LOG(INFO) << "Starting application";

    /*
     * If the daemon is to run in the background, daemonize the process. That causes the process to
     * detach from it parent, detach from its controlling terminal, close all associated file
     * descriptors except stdin, stdout, and stderr which will be connected to dev/null, and change
     * to the root directory so that the daemon can't prevent the root file system from being
     * unmounted.
     */
    if ((!m_foreground) && (daemon(0, 0) != STATUS_SUCCESS)) {
        LOG(ERROR) << "Failed to become daemon: Error Code=" << errno << ", Description=" << strerror(errno);
        return EXIT_FAILURE;
    }

    /*
     * Setup the object store.
     */
    if (!m_objectStore.open()) {
        LOG(ERROR) << "Failed to open object store";
        return EXIT_FAILURE;
    }

    FILE* file = fopen(m_pidFileName.c_str(), "w");
    if (file == nullptr)
        LOG(ERROR) << "Failed to create PID file: Error Code=" << errno << ", Description=" << strerror(errno);
    else {
        if (fprintf(file, "%i\n", getpid()) < 0)
            LOG(ERROR) << "Failed to write PID file: Error Code=" << errno << ", Description=" << strerror(errno);
        if (fclose(file) != STATUS_SUCCESS)
            LOG(ERROR) << "Failed to close PID file: Error Code=" << errno << ", Description=" << strerror(errno);
    }
    signal(SIGTERM, terminateProgram);

    /*
     * Start the communications and then wait for the application to be signaled to terminate.
     */
    m_communicationsManager.start();

    daemonTerminated.wait(daemonLock);
    LOG(INFO) << "Stopping application";

    if (remove(m_pidFileName.c_str()) != STATUS_SUCCESS)
        LOG(ERROR) << "Failed to remove PID file: Error Code=" << errno << ", Description=" << strerror(errno);

    return EXIT_SUCCESS;
}

