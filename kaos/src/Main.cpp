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

