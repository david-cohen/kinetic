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
#include <time.h>
#include <stdint.h>
#include <unistd.h>
#include <getopt.h>
#include <libgen.h>
#include <sys/time.h>
#include <string>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iostream>
#include "ObjectStore.hpp"
#include "GlobalConfig.hpp"

/*
 * Used Namespaces
 */
using std::string;

/*
 * Global Variable
 */
GlobalConfig globalConfig;
ObjectStorePtr objectStore;
bool debug = false;

const uint32_t LARGE_VALUE_SIZE = 1048576;
const uint32_t NUMBER_OF_LARGE_WRITES = 6000;

string value_4kib(4096, 'X');
string value_64kib(65536, 'X');
string value_1mib(1048576, 'X');

uint64_t
getTimestamp(void) {
    struct timespec time;
    memset(&time, 0, sizeof(time));
    if (clock_gettime(CLOCK_REALTIME, &time) != 0)
        return 0;

    return time.tv_sec * 1000000 + time.tv_nsec / 1000;
}

bool
repeatedPut(const string& value, uint32_t numberOfPuts) {
    string version;
    string tag;
    Algorithm algorithm(Algorithm::Command_Algorithm_SHA1);
    PersistOption persistOption = PersistOption::Command_Synchronization_WRITEBACK;

    for (uint32_t count = 0; count < numberOfPuts; count++) {
        std::count << "count " << count << std::end;
        std::stringstream stream;
        stream << count;
        string number = stream.str();
        string key = "key_" + number;
        if (objectStore->putForced(key, value, version, tag, algorithm, persistOption) != ReturnStatus::SUCCESS) {
            std::cerr << "put failed " << std::endl;
            return false;
        }
    }

    return true;
}

/**
 * Main
 *
 * @param    argc  number of command line arguments
 * @param    argv  array of command line arguments
 *
 * @return   EXIT_SUCCESS if successful, EXIT_FAILURE otherwise
 */
int32_t
main(int argc, char** argv) {
    string databaseDirectory("/tmp/objectStore");
    struct option longopts[] = {
        { "dir",        required_argument, nullptr, 'x' },
        { "debug",      no_argument,       nullptr, 'd' },
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
    while ((opt = getopt_long(argc, argv, "x:dh", longopts, &longindex)) != ALL_ARGS_PROCESSED) {
        if (opt == 'd') {
            debug = true;
            std::cout << "debug" << std::endl;
        }
        else if (opt == 'x')
            databaseDirectory = string(optarg);
        else if (opt == 'h') {
            std::cout << "Usage: " << string(basename(argv[0])) << " [--debug|-d]|[--foreground|-f]|[--background|-b]|[--help|-h]" << std::endl;
            return (opt == 'h' ? EXIT_SUCCESS : EXIT_FAILURE);
        }
    }

    {
        objectStore.reset(new ObjectStore(databaseDirectory + "1"));
        ReturnStatus status = objectStore->open();
        if (status != ReturnStatus::SUCCESS) {
            return EXIT_FAILURE;
        }


        std::cout << "1 MiB put forced test (writes 1 GiB)" << std::endl;
        uint64_t start = getTimestamp();
        std::cout << "start: " << start << std::endl;
        if (!repeatedPut(value_1mib, 1024)) {
            std::cout << "Test failed" << std::endl;
            return EXIT_FAILURE;
        }
        uint64_t end = getTimestamp();
        std::cout << "end: " << end << std::endl;
        std::cout << "diff(us): " << (end - start) << std::endl;
        std::cout << "diff(s): " << ((end - start) / 1000000) << std::endl;
    }

    {
        objectStore.reset(new ObjectStore(databaseDirectory + "2"));
        ReturnStatus status = objectStore->open();
        if (status != ReturnStatus::SUCCESS) {
            return EXIT_FAILURE;
        }

        std::cout << "64 KiB put forced test (writes 1 GiB)" << std::endl;
        uint64_t start = getTimestamp();
        std::cout << "start: " << start << std::endl;
        if (!repeatedPut(value_64kib, 16384)) {
            std::cout << "Test failed" << std::endl;
            return EXIT_FAILURE;
        }
        uint64_t end = getTimestamp();
        std::cout << "end: " << end << std::endl;
        std::cout << "diff(us): " << (end - start) << std::endl;
        std::cout << "diff(s): " << ((end - start) / 1000000) << std::endl;
    }

    {
        objectStore.reset(new ObjectStore(databaseDirectory + "3"));
        ReturnStatus status = objectStore->open();
        if (status != ReturnStatus::SUCCESS) {
            return EXIT_FAILURE;
        }

        std::cout << "4 KiB put forced test (writes 1 GiB)" << std::endl;
        uint64_t start = getTimestamp();
        std::cout << "start: " << start << std::endl;
        if (!repeatedPut(value_4kib, 262144)) {
            std::cout << "Test failed" << std::endl;
            return EXIT_FAILURE;
        }
        uint64_t end = getTimestamp();
        std::cout << "end: " << end << std::endl;
        std::cout << "diff(us): " << (end - start) << std::endl;
        std::cout << "diff(s): " << ((end - start) / 1000000) << std::endl;
    }

    return EXIT_SUCCESS;
}
