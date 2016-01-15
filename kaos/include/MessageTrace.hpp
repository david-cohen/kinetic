/*
 * Copyright (c) [2014 - 2016] Western Digital Technologies, Inc. All rights reserved.
 */
#pragma once
#ifndef MESSAGE_TRACE_HPP
#define MESSAGE_TRACE_HPP

/*
 * Include Files
 */
#include <string>
#include "KineticMessage.hpp"
#include "KineticMessageFraming.hpp"

/**
 * Message Trace
 *
 * Allows the contents of a Kinetic message to be output to standard-out for debugging purposes.
*/
class MessageTrace {
public:
    static void outputContents(KineticMessageFraming& messageFraming, KineticMessage* message);
private:
    static void outputHeader(const com::seagate::kinetic::proto::Command_Header& header);
    static void outputKeyValue(const com::seagate::kinetic::proto::Command_KeyValue& keyvalue);
    static void outputRange(const com::seagate::kinetic::proto::Command_Range& range);
    static void outputConfiguration(const com::seagate::kinetic::proto::Command_GetLog_Configuration& configuration);
    static void outputStatistics(const com::seagate::kinetic::proto::Command_GetLog& getLog);
    static void outputCapacity(const com::seagate::kinetic::proto::Command_GetLog_Capacity& capacity);
    static void outputLimits(const com::seagate::kinetic::proto::Command_GetLog_Limits& limits);
    static void outputGetLog(const com::seagate::kinetic::proto::Command_GetLog& getLog);
    static void outputSetup(const com::seagate::kinetic::proto::Command_Setup& setup);
    static void outputSecurity(const com::seagate::kinetic::proto::Command_Security& security);
    static void outputPinOp(const com::seagate::kinetic::proto::Command_PinOperation& pinop);
    static void outputBatch(const com::seagate::kinetic::proto::Command_Batch& batch);
    static void outputBody(const com::seagate::kinetic::proto::Command_Body& body);
    static void outputStatus(const com::seagate::kinetic::proto::Command_Status& status);
    static void outputHexBytes(const std::string& data, bool newLine = true);
    static void outputString(const std::string& data, bool newLine = true);
};

#endif
