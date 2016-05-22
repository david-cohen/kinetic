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
#ifndef TRANSLATOR_HPP
#define TRANSLATOR_HPP

/*
 * Include Files
 */
#include <string>
#include <sstream>
#include "Hmac.hpp"
#include "Kinetic.pb.hpp"
#include "AccessScope.hpp"
#include "Settings.pb.hpp"

/**
 * Provides functionality to convert values between formats (such as between Kinetic Message enum
 * and an internal enum or between an enum and a string).
 */
class Translator {
public:
    static HmacAlgorithm fromSettingsFormat(kaos::Settings_ACL_HmacAlgorithm hmacAlgorithmSetting);
    static kaos::Settings_ACL_HmacAlgorithm toSettingsFormat(HmacAlgorithm hmacAlgorithm);
    static Operation fromSettingsFormat(kaos::Settings_ACL_Operation aclOperationSetting);
    static kaos::Settings_ACL_Operation toSettingsFormat(Operation operation);
    static HmacAlgorithm fromMessageFormat(com::seagate::kinetic::proto::Command_Security_ACL_HMACAlgorithm hmacAlgorithm);
    static Operation fromMessageFormat(com::seagate::kinetic::proto::Command_Security_ACL_Permission permission);
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
