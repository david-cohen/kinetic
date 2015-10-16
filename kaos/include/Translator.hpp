/*
    Copyright (c) [2014 - 2015] Western Digital Technologies, Inc. All rights reserved.
*/

#pragma once
#ifndef TRANSLATOR_HPP
#define TRANSLATOR_HPP

/*
    Include Files
*/

#include <string>
#include <sstream>
#include "Hmac.hpp"
#include "Common.hpp"
#include "Kinetic.pb.hpp"
#include "ObjectStore.hpp"
#include "AccessScope.hpp"
#include "Settings.pb.hpp"

/**
    Translator Class
*/

class Translator {
public:
    static HmacAlgorithm fromSettingsFormat(kaos::Settings_ACL_HmacAlgorithm hmacAlgorithmSetting);
    static kaos::Settings_ACL_HmacAlgorithm toSettingsFormat(HmacAlgorithm hmacAlgorithm);
    static Operation fromSettingsFormat(kaos::Settings_ACL_Operation aclOperationSetting);
    static kaos::Settings_ACL_Operation toSettingsFormat(Operation operation);
    static HmacAlgorithm fromMessageFormat(com::seagate::kinetic::proto::Command_Security_ACL_HMACAlgorithm hmacAlgorithm);
    static Operation fromMessageFormat(com::seagate::kinetic::proto::Command_Security_ACL_Permission permission);
    static void setMessageStatus(com::seagate::kinetic::proto::Command_Status* messageStatus, ReturnStatus returnStatus);
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
