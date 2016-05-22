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
#pragma once
#ifndef KINETIC_LOG_HPP
#define KINETIC_LOG_HPP

/*
 * Include Files
 */
#include <string>
#include "Kinetic.pb.hpp"
#include "MessageStatistics.hpp"

/**
 * Provides the information needed for the various Kinetic get log requests (which includes
 * configuration, statistics, capacities, temperatures, utilizations, system limits, and message
 * logs).
 */
class KineticLog {
public:

    /*
     * Public Class Member Functions
     */
    static void getConfiguration(com::seagate::kinetic::proto::Command_GetLog* response);
    static void getLimits(com::seagate::kinetic::proto::Command_GetLog* response);
    static void getStatistics(com::seagate::kinetic::proto::Command_GetLog* response, MessageStatistics& messageStatistics);
    static void getCapacities(com::seagate::kinetic::proto::Command_GetLog* response);
    static void getMessage(com::seagate::kinetic::proto::Command_GetLog* response);
    static void getDevice(const com::seagate::kinetic::proto::Command_GetLog& request, std::string& responseValue);
    static void getTemperatures(com::seagate::kinetic::proto::Command_GetLog* response);
    static void getUtilizations(com::seagate::kinetic::proto::Command_GetLog* response);
};

#endif
