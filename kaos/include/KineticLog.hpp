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
