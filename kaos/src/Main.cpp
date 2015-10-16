/*
    Copyright (c) [2014 - 2015] Western Digital Technologies, Inc. All rights reserved.
*/

/*
    Include Files
*/

#include <limits.h>
#include <stdint.h>
#include <unistd.h>
#include <getopt.h>
#include <list>
#include <string>
#include <iostream>
#include "Logger.hpp"
#include "SslControl.hpp"
#include "ObjectStore.hpp"
#include "SystemConfig.hpp"
#include "TcpTransport.hpp"
#include "SystemControl.hpp"
#include "ServerSettings.hpp"
#include "TransportManager.hpp"
#include "MessageStatistics.hpp"
#include "HeartbeatProvider.hpp"
#include "ConnectionFactory.hpp"

/*
    Used Namespaces
*/

using std::string;

/*
    Global Variable
*/

SystemConfig systemConfig;
SystemControl systemControl;
ServerSettings serverSettings(systemConfig.serverSettingsFile());
MessageStatistics messageStatistics;
ObjectStorePtr objectStore;
TransportManager transportManager;
HeartbeatProvider heartbeatProvider;
ConnectionFactory connectionFactory;
static string programName;

/**
    Create PID File

    This function creates the process pid file. Should be called if process has been daemonized.
*/

void
createPidFile() {

    string pidFilePath = systemConfig.pidFileDir() + "/" + programName + systemConfig.pidFileExtension();
    FILE* file = fopen(pidFilePath.c_str(), "w");
    if (file == nullptr)
        LOG(ERROR) << "Failed to create PID file: error_code=" << errno << ", error_description=" << strerror(errno);
    else {
        int32_t returnCode = fprintf(file, "%i\n", getpid());
        fclose(file);
        if (returnCode != STATUS_SUCCESS)
            LOG(ERROR) << "Failed to write PID file: error_code=" << errno << ", error_description=" << strerror(errno);
    }
}

/**
    Delete PID File

    This function deletes the process pid file. Should be called prior to exitting the program.
*/

void
deletePidFile() {

    string pidFilePath = systemConfig.pidFileDir() + "/" + programName + systemConfig.pidFileExtension();
    if (remove(pidFilePath.c_str()) != STATUS_SUCCESS)
        LOG(ERROR) << "Failed to remove PID file: error_code=" << errno << ", error_description=" << strerror(errno);
}

/**
    Main

    @param    argc  number of command line arguments
    @param    argv  array of command line arguments

    @return   EXIT_SUCCESS if successful, EXIT_FAILURE otherwise
*/

int32_t
main(int argc, char** argv) {

    programName = string(basename(argv[0]));
    bool foreground(true);
    string databaseDirectory(systemConfig.databaseDirectory());
    struct option longopts[] = {
        { "dir",        required_argument, nullptr, 'x' },
        { "debug",      no_argument,       nullptr, 'd' },
        { "background", no_argument,       nullptr, 'b' },
        { "foreground", no_argument,       nullptr, 'f' },
        { "help",       no_argument,       nullptr, 'h' },
        { 0, 0, 0, 0 }
    };

    /*
        Process any command line arguments.  Arguments can be used to cause the program to run in
        the foreground or in debug mode (which causes additional information to be logged).
    */

    int32_t opt(0);
    int32_t longindex(0);
    const int32_t ALL_ARGS_PROCESSED(-1);
    while ((opt = getopt_long(argc, argv, "x:bdfh", longopts, &longindex)) != ALL_ARGS_PROCESSED) {
        if (opt == 'd') {
            systemControl.setDebugEnabled(true);
        }
        if (opt == 'x')
            databaseDirectory = string(optarg);
        else if (opt == 'f') {
            foreground = true;
        }
        else if (opt == 'b') {
            foreground = false;
        }
        else if (opt == 'h') {
            std::cout << "Usage: " << programName << " [--dir|-x]|[--debug|-d]|[--background|-b]|[--foreground|-f]|[--help|-h]" << std::endl;
            return (opt == 'h' ? EXIT_SUCCESS : EXIT_FAILURE);
        }
    }

    LOG_INIT(nullptr, systemConfig.kaosLogFacility(), systemControl.debugEnabled());

    /*
        If the daemon is not to run in the foreground, daemonize the process. That causes the
        process to detach from it parent (so it can run in the background), detach from its
        controlling terminal, close all associated file descriptors except stdin, stdout, and stderr
        which will be connected to dev/null, and change to the root directory so that the daemon
        can't prevent the root file system from being unmounted.
    */

    if ((!foreground) && (daemon(0, 0) != STATUS_SUCCESS)) {
        LOG(ERROR) << "Failed to become daemon: error_code=" << errno << ", error_description=" << strerror(errno);
        return EXIT_FAILURE;
    }

    if (!SslControl::instance().operational()) {
        LOG(ERROR) << "Failed to configure SSL component";
        return EXIT_FAILURE;
    }

    /*
        Setup the object store.
    */

    objectStore.reset(new ObjectStore(databaseDirectory));
    ReturnStatus status = objectStore->open();
    if (status != ReturnStatus::SUCCESS) {
        LOG(ERROR) << "Failed to open object store";
        return EXIT_FAILURE;
    }

    if (!foreground)
        createPidFile();

    /*
        Start the transports.
    */

    std::list<TransportInterface*> transportList;
    transportList.push_back(new TcpTransport(systemConfig.tcpPort(), Security::NONE));
    transportList.push_back(new TcpTransport(systemConfig.sslPort(), Security::SSL));

    transportManager.start(transportList);
    heartbeatProvider.start();

    transportManager.wait();


    if (!foreground)
        deletePidFile();

    return EXIT_SUCCESS;
}

