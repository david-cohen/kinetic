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
#pragma once
#ifndef MESSAGE_TRACE_HPP
#define MESSAGE_TRACE_HPP

/*
 * Include Files
 */
#include <string>
#include "Kinetic.pb.hpp"
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
    static std::string toString(bool boolValue);
    static std::string toString(com::seagate::kinetic::proto::Command_Algorithm algorithm);
    static std::string toString(com::seagate::kinetic::proto::Command_PinOperation_PinOpType pinop);
    static std::string toString(com::seagate::kinetic::proto::Command_Security_ACL_HMACAlgorithm algorithm);
    static std::string toString(com::seagate::kinetic::proto::Message_AuthType authType);
    static std::string toString(com::seagate::kinetic::proto::Command_MessageType messageType);
    static std::string toString(com::seagate::kinetic::proto::Command_GetLog_Type type);
    static std::string toString(com::seagate::kinetic::proto::Command_Security_ACL_Permission permission);
    static std::string toString(com::seagate::kinetic::proto::Command_Synchronization synchronization);
    static std::string toString(com::seagate::kinetic::proto::Command_Status_StatusCode statusCode);
};

#endif
