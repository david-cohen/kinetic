/*
    Copyright (c) [2014 - 2015] Western Digital Technologies, Inc. All rights reserved.
*/

/*
    Include Files
*/

#include <stdint.h>
#include <unistd.h>
#include <sys/statvfs.h>
#include <string>
#include "Kinetic.pb.hpp"
#include "KineticLog.hpp"
#include "ObjectStore.hpp"
#include "SystemConfig.hpp"
#include "MessageStatistics.hpp"

/**
    Get Configuration

    @param response     pointer to the get log response to be populated
*/

void
KineticLog::getConfiguration(com::seagate::kinetic::proto::Command_GetLog* response) {

    com::seagate::kinetic::proto::Command_GetLog_Configuration* configuration(response->mutable_configuration());
    configuration->set_vendor(systemConfig.vendor());
    configuration->set_model(systemConfig.model());
    configuration->set_version(systemConfig.version());
    configuration->set_serialnumber(systemConfig.serialNumber());
    configuration->set_compilationdate(systemConfig.compilationDate());
    configuration->set_sourcehash(systemConfig.sourceHash());
    configuration->set_port(systemConfig.tcpPort());
    configuration->set_tlsport(systemConfig.sslPort());
    configuration->set_worldwidename(systemConfig.worldWideName());

    for (auto networkInterfaceSet : systemConfig.networkInterfaceMap()) {
        auto networkInterfaceConfig = networkInterfaceSet.second;
        ::com::seagate::kinetic::proto::Command_GetLog_Configuration_Interface* networkInterface = configuration->add_interface();
        networkInterface->set_name(networkInterfaceConfig->name());
        networkInterface->set_mac(networkInterfaceConfig->macAddress());
        networkInterface->set_ipv4address(networkInterfaceConfig->ipv4());
        networkInterface->set_ipv6address(networkInterfaceConfig->ipv6());
    }
}

/**
    Get Temperatures

    @param response     pointer to the get log response to be populated
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
    Get Statistics

    @param response     pointer to the get log response to be populated
*/

void
KineticLog::getStatistics(com::seagate::kinetic::proto::Command_GetLog* response) {
    messageStatistics.get(response);
}

/**
    Get Limits

    @param response     pointer to the get log response to be populated
*/

void
KineticLog::getLimits(com::seagate::kinetic::proto::Command_GetLog* response) {

    com::seagate::kinetic::proto::Command_GetLog_Limits* limits(response->mutable_limits());

    limits->set_maxkeysize(systemConfig.maxKeySize());
    limits->set_maxvaluesize(systemConfig.maxValueSize());
    limits->set_maxversionsize(systemConfig.maxVersionSize());
    limits->set_maxtagsize(systemConfig.maxTagSize());
    limits->set_maxconnections(systemConfig.maxConnections());
    limits->set_maxoutstandingreadrequests(systemConfig.maxOutstandingReadRequests());
    limits->set_maxoutstandingwriterequests(systemConfig.maxOutstandingWriteRequests());
    limits->set_maxmessagesize(systemConfig.maxMessageSize());
    limits->set_maxkeyrangecount(systemConfig.maxKeyRangeCount());
    limits->set_maxidentitycount(systemConfig.maxIdentityCount());
    limits->set_maxpinsize(systemConfig.maxPinSize());
    limits->set_maxoperationcountperbatch(systemConfig.maxOperationCountPerBatch());
    limits->set_maxbatchcountperdevice(systemConfig.maxBatchCountPerDevice());
}

/**
    Get Message

    @param response     pointer to the get log response to be populated
*/

void
KineticLog::getMessage(com::seagate::kinetic::proto::Command_GetLog* response) {

    std::string* message = response->mutable_messages();
    message->assign("System started");
    // todo - make real
}

/**
    Get Device

    @param response     pointer to the get log response to be populated
*/

void
KineticLog::getDevice(const com::seagate::kinetic::proto::Command_GetLog& request, std::string& responseValue) {

    if (!request.has_device() || !request.device().has_name())
        throw MessageException(com::seagate::kinetic::proto::Command_Status_StatusCode_NOT_FOUND, "Missing device log name.");

#ifdef WORK_WITH_JAVA_SMOKE_TEST
    if (request.device().name() == "com.seagate.simulator:dummy")
        responseValue = "this is a sample log";
    else
#endif
        throw MessageException(com::seagate::kinetic::proto::Command_Status_StatusCode_NOT_FOUND,
                               "No device log for the specified name: " + request.device().name());
}

/**
    Get Capacities

    @param response     pointer to the get log response to be populated
*/

void
KineticLog::getCapacities(com::seagate::kinetic::proto::Command_GetLog* response) {

    struct statvfs fiData;
    memset(&fiData, 0, sizeof(fiData));

    std::string mountPoint = objectStore->getDatabaseDirectory();

    float totalCapacity(0);
    float remainingCapacity(0);

    if ((statvfs(mountPoint.c_str(), &fiData)) == STATUS_SUCCESS) {
        totalCapacity = static_cast<float>(fiData.f_bsize) * static_cast<float>(fiData.f_blocks);
        remainingCapacity = static_cast<float>(fiData.f_bsize) * static_cast<float>(fiData.f_bfree);
        /*
                std::cout << "mountPoint " << mountPoint << std::endl;
                std::cout << "fiData.f_bsize " << fiData.f_bsize << std::endl;
                std::cout << "fiData.f_blocks " << fiData.f_blocks << std::endl;
                std::cout << "fiData.f_bfree " << fiData.f_bfree << std::endl;
                std::cout << "totalCapacity " << (uint64_t)totalCapacity << std::endl;
                std::cout << "remainingCapacity " << (uint64_t)remainingCapacity << std::endl;
        */
    }
//    else
//        logEvent(ERROR_EVENT, "Failed to get file system information: mount_point=\"" + mountPoint + "\"");

    com::seagate::kinetic::proto::Command_GetLog_Capacity* capacity(response->mutable_capacity());
    capacity->set_nominalcapacityinbytes(totalCapacity);
    capacity->set_portionfull((totalCapacity - remainingCapacity) / totalCapacity);
}

/**
    Get Utilizations

    @param response     pointer to the get log response to be populated
*/

void
KineticLog::getUtilizations(com::seagate::kinetic::proto::Command_GetLog* response) {

    com::seagate::kinetic::proto::Command_GetLog_Utilization* utilization(response->add_utilizations());
    utilization->set_name("HDA");
    utilization->set_value(.1);
#ifdef WORK_WITH_JAVA_SMOKE_TEST
    utilization = response->add_utilizations();
    utilization->set_name("EN0");
    utilization->set_value(.25);
    utilization = response->add_utilizations();
    utilization->set_name("EN1");
    utilization->set_value(.25);
    utilization = response->add_utilizations();
    utilization->set_name("CPU");
    utilization->set_value(.05);
#endif
}
