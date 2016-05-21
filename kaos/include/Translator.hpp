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
#ifndef TRANSLATOR_HPP
#define TRANSLATOR_HPP

/*
 * Include Files
 */
#include <string>
#include <sstream>
#include "Hmac.hpp"
#include "Common.hpp"
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
