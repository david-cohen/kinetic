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
#ifndef MESSAGE_TRACE_HPP
#define MESSAGE_TRACE_HPP

/*
 * Include Files
 */
#include <string>
#include "KineticMessage.hpp"
#include "KineticMessageFraming.hpp"

/**
 * Debug utility that allows the contents of a Kinetic message to be output to standard-out.
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
