/*
 * Copyright (c) [2014 - 2016] Western Digital Technologies, Inc. All rights reserved.
 */
#pragma once
#ifndef KINETIC_LOG_HPP
#define KINETIC_LOG_HPP

/*
 * Include Files
 */
#include <string>
#include "Kinetic.pb.hpp"

/*
 * Kinetic Log
 */
class KineticLog {
public:

    /*
     * Public Class Member Functions
     */
    static void getConfiguration(com::seagate::kinetic::proto::Command_GetLog* response);
    static void getStatistics(com::seagate::kinetic::proto::Command_GetLog* response);
    static void getCapacities(com::seagate::kinetic::proto::Command_GetLog* response);
    static void getTemperatures(com::seagate::kinetic::proto::Command_GetLog* response);
    static void getUtilizations(com::seagate::kinetic::proto::Command_GetLog* response);
    static void getMessage(com::seagate::kinetic::proto::Command_GetLog* response);
    static void getLimits(com::seagate::kinetic::proto::Command_GetLog* response);
    static void getDevice(const com::seagate::kinetic::proto::Command_GetLog& request, std::string& responseValue);
};

#endif
