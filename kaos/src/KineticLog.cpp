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
#include <errno.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/statvfs.h>
#include <string>
#include "Logger.hpp"
#include "Server.hpp"
#include "Kinetic.pb.hpp"
#include "KineticLog.hpp"
#include "GlobalConfig.hpp"
#include "MessageStatistics.hpp"

/**
 * Builds the response with the requested configuration information.
 *
 * @param   response    Pointer to the get log response to be populated
 */
void
KineticLog::getConfiguration(com::seagate::kinetic::proto::Command_GetLog* response) {

    com::seagate::kinetic::proto::Command_GetLog_Configuration* configuration(response->mutable_configuration());
    configuration->set_vendor(globalConfig.vendor());
    configuration->set_model(globalConfig.model());
    configuration->set_version(globalConfig.version());
    configuration->set_serialnumber(globalConfig.serialNumber());
    configuration->set_compilationdate(globalConfig.compilationDate());
    configuration->set_sourcehash(globalConfig.sourceHash());
    configuration->set_port(globalConfig.tcpPort());
    configuration->set_tlsport(globalConfig.sslPort());
    configuration->set_worldwidename(globalConfig.worldWideName());

    for (auto networkInterfaceSet : globalConfig.networkInterfaceMap()) {
        auto networkInterfaceConfig = networkInterfaceSet.second;
        ::com::seagate::kinetic::proto::Command_GetLog_Configuration_Interface* networkInterface = configuration->add_interface();
        networkInterface->set_name(networkInterfaceConfig->name());
        networkInterface->set_mac(networkInterfaceConfig->macAddress());
        networkInterface->set_ipv4address(networkInterfaceConfig->ipv4());
        networkInterface->set_ipv6address(networkInterfaceConfig->ipv6());
    }
}

/**
 * Build the response with the requested limit information.
 *
 * @param   response    Pointer to the get log response to be populated
 */
void
KineticLog::getLimits(com::seagate::kinetic::proto::Command_GetLog* response) {

    com::seagate::kinetic::proto::Command_GetLog_Limits* limits(response->mutable_limits());
    limits->set_maxkeysize(globalConfig.maxKeySize());
    limits->set_maxvaluesize(globalConfig.maxValueSize());
    limits->set_maxversionsize(globalConfig.maxVersionSize());
    limits->set_maxtagsize(globalConfig.maxTagSize());
    limits->set_maxconnections(globalConfig.maxConnections());
    limits->set_maxoutstandingreadrequests(globalConfig.maxOutstandingReadRequests());
    limits->set_maxoutstandingwriterequests(globalConfig.maxOutstandingWriteRequests());
    limits->set_maxmessagesize(globalConfig.maxMessageSize());
    limits->set_maxkeyrangecount(globalConfig.maxKeyRangeCount());
    limits->set_maxidentitycount(globalConfig.maxIdentityCount());
    limits->set_maxpinsize(globalConfig.maxPinSize());
    limits->set_maxoperationcountperbatch(globalConfig.maxOperationCountPerBatch());
    limits->set_maxbatchcountperdevice(globalConfig.maxBatchCountPerDevice());
}

/**
 * Builds the response with the requested statistics information.
 *
 * @param   response            Pointer to the get log response to be populated
 * @param   messageStatistics   Object containing the message statistics
 */
void
KineticLog::getStatistics(com::seagate::kinetic::proto::Command_GetLog* response, MessageStatistics& messageStatistics) {
    messageStatistics.get(response);
}

/**
 * Builds the response with the requested capacity information, which is taken from the total and
 * available capacity of the data partition.
 *
 * @param   response    Pointer to the get log response to be populated
 */
void
KineticLog::getCapacities(com::seagate::kinetic::proto::Command_GetLog* response) {

    struct statvfs fiData;
    memset(&fiData, 0, sizeof(fiData));
    std::string mountPoint = globalConfig.databaseDirectory();

    float totalCapacity(0);
    float remainingCapacity(0);

    if ((statvfs(mountPoint.c_str(), &fiData)) != STATUS_SUCCESS) {
        LOG(ERROR) << "Failed to get file system information for mount point " << mountPoint
                   << ", Error Code=" << errno << ", Description=" << strerror(errno);
    }
    else {
        totalCapacity = static_cast<float>(fiData.f_bsize) * static_cast<float>(fiData.f_blocks);
        remainingCapacity = static_cast<float>(fiData.f_bsize) * static_cast<float>(fiData.f_bfree);
    }

    com::seagate::kinetic::proto::Command_GetLog_Capacity* capacity(response->mutable_capacity());
    capacity->set_nominalcapacityinbytes(totalCapacity);
    capacity->set_portionfull((totalCapacity - remainingCapacity) / totalCapacity);
}

/**
 * Builds the response with the requested message information.
 *
 * @param   response    Pointer to the get log response to be populated
 */
void
KineticLog::getMessage(com::seagate::kinetic::proto::Command_GetLog* response) {

    std::string* message = response->mutable_messages();
    message->assign("System started");
}

/**
 * Builds the response with the requested device information.
 *
 * @param   response    Pointer to the get log response to be populated
 */
void
KineticLog::getDevice(const com::seagate::kinetic::proto::Command_GetLog& request, std::string& responseValue) {

    if (!request.has_device() || !request.device().has_name())
        throw MessageException(com::seagate::kinetic::proto::Command_Status_StatusCode_NOT_FOUND, "Missing device log name.");

    if (request.device().name() == "com.seagate.simulator:dummy")
        responseValue = "this is a sample log";
    else
        throw MessageException(com::seagate::kinetic::proto::Command_Status_StatusCode_NOT_FOUND,
                               "No device log for the specified name: " + request.device().name());
}

/**
 * Builds the response with the requested temperature information.
 *
 * @param   response    Pointer to the get log response to be populated
 */
void
KineticLog::getTemperatures(com::seagate::kinetic::proto::Command_GetLog* response) {

    com::seagate::kinetic::proto::Command_GetLog_Temperature* temperature(response->add_temperatures());
    temperature->set_name("HDA");
    temperature->set_current(75);
    temperature->set_target(25);
    temperature->set_minimum(5);
    temperature->set_maximum(100);
}

/**
 * Builds the response with the requested utilization information.
 *
 * @param   response    Pointer to the get log response to be populated
 */
void
KineticLog::getUtilizations(com::seagate::kinetic::proto::Command_GetLog* response) {

    com::seagate::kinetic::proto::Command_GetLog_Utilization* utilization(response->add_utilizations());
    utilization->set_name("HDA");
    utilization->set_value(.1);
    utilization = response->add_utilizations();
    utilization->set_name("EN0");
    utilization->set_value(.25);
    utilization = response->add_utilizations();
    utilization->set_name("EN1");
    utilization->set_value(.25);
    utilization = response->add_utilizations();
    utilization->set_name("CPU");
    utilization->set_value(.05);
}

