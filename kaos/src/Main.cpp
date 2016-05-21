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

#include <libgen.h>
#include <getopt.h>
#include <stdint.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include "Server.hpp"

Server* server;
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
    std::string pidFileName = "";
    struct option longopts[] = {
        { "pid",        required_argument, nullptr, 'p' },
        { "foreground", no_argument,       nullptr, 'f' },
        { "help",       no_argument,       nullptr, 'h' },
        { 0, 0, 0, 0 }
    };

    /*
     * Process any command line arguments.  Arguments can specify the process ID filename and if the
     * program is to run in the forground.
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

    server = new Server(pidFileName, foreground);
    return server->run();
}

