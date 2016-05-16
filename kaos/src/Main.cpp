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
#include <getopt.h>
#include <signal.h>
#include <stdint.h>
#include <unistd.h>
#include <mutex>
#include <string>
#include <iostream>
#include <condition_variable>
#include "Logger.hpp"
#include "SslControl.hpp"
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
ServerSettings serverSettings(systemConfig.serverSettingsFile());
SslControl sslControl;
MessageStatistics messageStatistics;
ObjectStore objectStore;
CommunicationsManager communicationsManager;

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

/**
 * Entry point of the Kinetic object store application, which normally runs as a daemon but can be
 * instructed to run in the foreground.  The application will run until receiving a SIGTERM, which
 * is normally sent by the kaos start/stop script when called to stop.
 *
 * @param   argc    Number of command line arguments
 * @param   argv    Array of command line arguments
 *
 * @return  EXIT_SUCCESS if successful, EXIT_FAILURE otherwise
 */
int32_t main(int argc, char** argv) {

    bool foreground(false);
    std::string pidFileName = systemConfig.defaultPidFileName();
    struct option longopts[] = {
        { "pid",        required_argument, nullptr, 'p' },
        { "foreground", no_argument,       nullptr, 'f' },
        { "help",       no_argument,       nullptr, 'h' },
        { 0, 0, 0, 0 }
    };

    /*
     * Process any command line arguments.  Arguments can be used to cause the program to run in
     * the foreground or in debug mode (which causes additional information to be logged).
     */
    int32_t opt(0);
    int32_t longindex(0);
    const int32_t ALL_ARGS_PROCESSED(-1);
    while ((opt = getopt_long(argc, argv, "p:fh", longopts, &longindex)) != ALL_ARGS_PROCESSED) {
        if (opt == 'p') {
            pidFileName.assign(optarg);
        }
        else if (opt == 'f') {
            foreground = true;
        }
        else if (opt == 'h') {
            std::cout << "Usage: " << basename(argv[0]) << " [--pid|-p]|[--foreground|-f]|[--help|-h]" << std::endl;
            return (opt == 'h' ? EXIT_SUCCESS : EXIT_FAILURE);
        }
    }

    if (foreground)
        logControl.setStandardOutEnabled(true);

    LOG(INFO) << "Starting application";

    /*
     * If the daemon is to run in the background, daemonize the process. That causes the process to
     * detach from it parent, detach from its controlling terminal, close all associated file
     * descriptors except stdin, stdout, and stderr which will be connected to dev/null, and change
     * to the root directory so that the daemon can't prevent the root file system from being
     * unmounted.
     */
    if ((!foreground) && (daemon(0, 0) != STATUS_SUCCESS)) {
        LOG(ERROR) << "Failed to become daemon: Error Code=" << errno << ", Description=" << strerror(errno);
        return EXIT_FAILURE;
    }

    if (!sslControl.operational()) {
        LOG(ERROR) << "Failed to configure SSL component";
        return EXIT_FAILURE;
    }

    /*
     * Setup the object store.
     */
    if (!objectStore.open()) {
        LOG(ERROR) << "Failed to open object store";
        return EXIT_FAILURE;
    }

    FILE* file = fopen(pidFileName.c_str(), "w");
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
    communicationsManager.start();

    daemonTerminated.wait(daemonLock);
    LOG(INFO) << "Stopping application";

    if (remove(pidFileName.c_str()) != STATUS_SUCCESS)
        LOG(ERROR) << "Failed to remove PID file: Error Code=" << errno << ", Description=" << strerror(errno);

    return EXIT_SUCCESS;
}

