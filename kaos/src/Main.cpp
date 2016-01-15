/*
 * Copyright (c) [2014 - 2016] Western Digital Technologies, Inc. All rights reserved.
 */

/*
 * Include Files
 */
#include <signal.h>
#include <stdint.h>
#include <unistd.h>
#include <getopt.h>
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
 */
SystemConfig systemConfig;
ServerSettings serverSettings(systemConfig.serverSettingsFile());
SslControl sslControl;
MessageStatistics messageStatistics;
ObjectStorePtr objectStore;
CommunicationsManager communicationsManager;

/*
 * Privae Variables
 */
static std::mutex daemonMutex;
static std::unique_lock<std::mutex> daemonLock(daemonMutex);
static std::condition_variable daemonTerminated;

/**
 * Terminate Program
 *
 * @param    signum    signal sent to process
 *
 * This function is called when the program has been signalled to exit (using SIGTERM).
 */
void terminateProgram(int signum) {

    /*
     * Eliminate the unused args warning for signum.
     */
    static_cast<void>(signum);
    daemonTerminated.notify_one();
}

/**
 * Main
 *
 * @param    argc  number of command line arguments
 * @param    argv  array of command line arguments
 *
 * @return   EXIT_SUCCESS if successful, EXIT_FAILURE otherwise
 */
int32_t main(int argc, char** argv) {

    bool background(true);
    std::string pidFileName = systemConfig.defaultPidFileName();
    std::string databaseDirectory(systemConfig.databaseDirectory());
    struct option longopts[] = {
        { "dir",        required_argument, nullptr, 'x' },
        { "pid",        required_argument, nullptr, 'p' },
        { "debug",      no_argument,       nullptr, 'd' },
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
    while ((opt = getopt_long(argc, argv, "xp:dfh", longopts, &longindex)) != ALL_ARGS_PROCESSED) {
        if (opt == 'x') {
            databaseDirectory.assign(optarg);
        }
        else if (opt == 'p') {
            pidFileName.assign(optarg);
        }
        else if (opt == 'd') {
            systemConfig.setDebugEnabled(true);
        }
        else if (opt == 'f') {
            background = false;
        }
        else if (opt == 'h') {
            std::cout << "Usage: " << basename(argv[0]) << " [--dir|-x]|[--debug|-d]|[--pid|-p]|[--foreground|-f]|[--help|-h]" << std::endl;
            return (opt == 'h' ? EXIT_SUCCESS : EXIT_FAILURE);
        }
    }

    LOG_INIT(nullptr, systemConfig.kaosLogFacility(), systemConfig.debugEnabled());

    /*
     * If the daemon is to run in the background, daemonize the process. That causes the process to
     * detach from it parent, detach from its controlling terminal, close all associated file
     * descriptors except stdin, stdout, and stderr which will be connected to dev/null, and change
     * to the root directory so that the daemon can't prevent the root file system from being
     * unmounted.
     */
    if ((background) && (daemon(0, 0) != STATUS_SUCCESS)) {
        LOG(ERROR) << "Failed to become daemon: error_code=" << errno << ", error_description=" << strerror(errno);
        return EXIT_FAILURE;
    }

    if (!sslControl.operational()) {
        LOG(ERROR) << "Failed to configure SSL component";
        return EXIT_FAILURE;
    }

    /*
     * Setup the object store.
      */
    objectStore.reset(new ObjectStore(databaseDirectory));
    ReturnStatus status = objectStore->open();
    if (status != ReturnStatus::SUCCESS) {
        LOG(ERROR) << "Failed to open object store";
        return EXIT_FAILURE;
    }

    signal(SIGTERM, terminateProgram);

    if (background) {
        FILE* file = fopen(pidFileName.c_str(), "w");
        if (file == nullptr)
            LOG(ERROR) << "Failed to create PID file: error_code=" << errno << ", error_description=" << strerror(errno);
        else {
            if (fprintf(file, "%i\n", getpid()) < 0)
                LOG(ERROR) << "Failed to write PID file: error_code=" << errno << ", error_description=" << strerror(errno);
            if (fclose(file) != STATUS_SUCCESS)
                LOG(ERROR) << "Failed to close PID file: error_code=" << errno << ", error_description=" << strerror(errno);
        }
    }

    /*
     * Start the communications;
     */
    communicationsManager.start();

    daemonTerminated.wait(daemonLock);

    if (background) {
        if (remove(pidFileName.c_str()) != STATUS_SUCCESS)
            LOG(ERROR) << "Failed to remove PID file: error_code=" << errno << ", error_description=" << strerror(errno);
    }

    return EXIT_SUCCESS;
}

