/*
    Copyright (c) [2014 - 2015] Western Digital Technologies, Inc. All rights reserved.
*/

/*
    Include Files
*/

#include <errno.h>
#include <stdint.h>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netpacket/packet.h>
#include <set>
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <typeinfo>
#include "Hmac.hpp"
#include "Logger.hpp"
#include "Kinetic.pb.hpp"
#include "SystemConfig.hpp"

using std::string;

/*
    Identification
*/

static const char* VENDOR("Western Digital");
static const char* MODEL("Wasp");
static const char* VERSION("0.0.2");
static const char* WORLD_WIDE_NAME_PREFIX("2d2ca5d0-c201-48da-b2c2-");

/*
    Build/Source Information (updated on every build)
*/

static const char* COMPILATION_DATE("Wed Dec 8 05:59:59 PDT 2015");
static const char* SOURCE_HASH("2d2ca5d0-c201-48da-b2c2-00803bd2c7c5");

/*
    Daemon Realted Settings
*/

static const char* PID_FILE_DIR("/var/run");
static const char* PID_FILE_EXTENSION(".pid");
static const char* DATABASE_DIRECTORY("/export/dfs/objectDatabase");
static const char* SERVER_SETTINGS_FILE("/export/dfs/serverSettings");
static const LogFacility KAOS_LOG_FACILITY(LOCAL0);

/*
    Object Store Settings
*/

static const bool OBJECT_STORE_COMPRESSION_ENABLED(false);
static const char* FLUSH_DATA_KEY_PATTERN("04231970_WesternDigital_07913240");

/*
    Communication Settings
*/

static const int32_t  MAX_PENDING_ADMIN_CONNECTIONS(5);
static const uint32_t MAX_ACTIVE_ADMIN_CONNECTIONS(10);
static const uint32_t TCP_PORT(8123);
static const uint32_t SSL_PORT(8443);
static const uint32_t MULTICAST_PORT(8123);
static const char*    MULTICAST_IP_ADDRESS("239.1.2.3");
static const char*    PROTOCOL_VERSION("3.0.6");
static const uint32_t HEARTBEAT_SEND_INTERVAL(5);
static const uint32_t HEARTBEAT_CONNECTION_RETRY_INTERVAL(60);

/*
    Limits
*/

static const size_t UNSUPPORTED_LIMIT((uint32_t)0xffffffff);
static const size_t MIN_KEY_SIZE(1);
static const size_t MAX_KEY_SIZE(4096);
static const size_t MAX_VALUE_SIZE(1048576);
static const size_t MAX_VERSION_SIZE(2048);
static const size_t MAX_TAG_SIZE(4096);
static const size_t MAX_CONNECTIONS(32);
static const size_t MAX_OUTSTANDING_READ_REQUESTS(8);
static const size_t MAX_OUTSTANDING_WRITE_REQUESTS(8);
static const size_t MAX_MESSAGE_SIZE(2097152);
static const size_t MAX_KEY_RANGE_COUNT(200);
static const size_t MAX_IDENTITY_COUNT(16);
static const size_t MAX_PIN_SIZE(128);
static const size_t MAX_OPERATION_COUNT_PER_BATCH(UNSUPPORTED_LIMIT);  // 15
static const size_t MAX_BATCH_COUNT_PER_DEVICE(UNSUPPORTED_LIMIT);     // 5
static const size_t MAX_ALGORITHM_SIZE(64);
static const size_t MAX_HMAC_KEY_SIZE(4096);

/*
    SSL Settings
*/

static const char* SSL_PRIVATE_KEY_FILE("/etc/kaos/cert.pem");
static const char* SSL_CERTIFICATE_FILE("/etc/kaos/cert.pem");

/*
    Setup Settings
*/

static const int64_t DEFAULT_CLUSTER_VERSION(0);
static const char* DEFAULT_LOCK_PIN("");
static const char* DEFAULT_ERASE_PIN("");

static const bool ACCESS_CONTROL_DEFAULT_TLS_REQUIRED(false);
static const int64_t ACCESS_CONTROL_DEFAULT_IDENTITY(1);
static const char* ACCESS_CONTROL_DEFAULT_HMAC_KEY("asdfasdf");
static const HmacAlgorithm ACCESS_CONTROL_DEFAULT_HMAC_ALGORITHM(HmacAlgorithm::SHA1);

static const char* ACCESS_SCOPE_DEFAULT_KEY_SUBSTRING("");
static const uint32_t ACCESS_SCOPE_DEFAULT_KEY_SUBSTRING_OFFSET(0);

bool getNextworkInfo(string name, string& ipv4, string& ipv6, string& macAddress);


static std::string
createFlushDataKey() {
    std::string flushDataKey;
    while (flushDataKey.size() <= MAX_KEY_SIZE) {
        flushDataKey.append(FLUSH_DATA_KEY_PATTERN);
    }
    return flushDataKey;
}

SystemConfig::SystemConfig()
    : m_pidFileDir(PID_FILE_DIR),
      m_pidFileExtension(PID_FILE_EXTENSION),
      m_databaseDirectory(DATABASE_DIRECTORY),
      m_serverSettingsFile(SERVER_SETTINGS_FILE),
      m_vendor(VENDOR),
      m_model(MODEL),
      m_version(VERSION),
      m_serialNumber(""),
      m_worldWideName(""),
      m_protocolVersion(PROTOCOL_VERSION),
      m_compilationDate(COMPILATION_DATE),
      m_sourceHash(SOURCE_HASH),
      m_kaosLogFacility(KAOS_LOG_FACILITY),
      m_objectStoreCompressionEnabled(OBJECT_STORE_COMPRESSION_ENABLED),
      m_maxPendingAdminConnections(MAX_PENDING_ADMIN_CONNECTIONS),
      m_maxActiveAdminConnections(MAX_ACTIVE_ADMIN_CONNECTIONS),                // Not used yet
      m_tcpPort(TCP_PORT),
      m_sslPort(SSL_PORT),
      m_multicastPort(MULTICAST_PORT),
      m_multicastIpAddress(MULTICAST_IP_ADDRESS),
      m_heartbeatSendInterval(HEARTBEAT_SEND_INTERVAL),
      m_heartbeatConnectionRetryInterval(HEARTBEAT_CONNECTION_RETRY_INTERVAL),
      m_minKeySize(MIN_KEY_SIZE),
      m_maxKeySize(MAX_KEY_SIZE),
      m_maxValueSize(MAX_VALUE_SIZE),
      m_maxVersionSize(MAX_VERSION_SIZE),
      m_maxTagSize(MAX_TAG_SIZE),
      m_maxConnectionse(MAX_CONNECTIONS),
      m_maxOutstandingReadRequests(MAX_OUTSTANDING_READ_REQUESTS),
      m_maxOutstandingWriteRequests(MAX_OUTSTANDING_WRITE_REQUESTS),
      m_maxMessageSize(MAX_MESSAGE_SIZE),
      m_maxKeyRangeCount(MAX_KEY_RANGE_COUNT),
      m_maxIdentityCount(MAX_IDENTITY_COUNT),
      m_maxPinSize(MAX_PIN_SIZE),
      m_maxOperationCountPerBatch(MAX_OPERATION_COUNT_PER_BATCH),
      m_maxBatchCountPerDevice(MAX_BATCH_COUNT_PER_DEVICE),
      m_maxAlgorithmSize(MAX_ALGORITHM_SIZE),
      m_maxHmacKeySize(MAX_HMAC_KEY_SIZE),
      m_unsupportedLimit(UNSUPPORTED_LIMIT),
      m_sslPrivateKeyFile(SSL_PRIVATE_KEY_FILE),
      m_sslCertificateFile(SSL_CERTIFICATE_FILE),
      m_defaultClusterVersion(DEFAULT_CLUSTER_VERSION),
      m_defaultLockPin(DEFAULT_LOCK_PIN),
      m_defaultErasePin(DEFAULT_ERASE_PIN),
      m_accessControlDefaultTlsRequired(ACCESS_CONTROL_DEFAULT_TLS_REQUIRED),
      m_accessControlDefaultIdentity(ACCESS_CONTROL_DEFAULT_IDENTITY),
      m_accessControlDefaultHmacKey(ACCESS_CONTROL_DEFAULT_HMAC_KEY),
      m_accessControlDefaultHmacAlgorithm(ACCESS_CONTROL_DEFAULT_HMAC_ALGORITHM),
      m_accessScopeDefaultKeySubstring(ACCESS_SCOPE_DEFAULT_KEY_SUBSTRING),
      m_accessScopeDefaultKeySubstringOffset(ACCESS_SCOPE_DEFAULT_KEY_SUBSTRING_OFFSET),
      m_flushDataKey(createFlushDataKey()),
    m_defaultLogTypes({
    com::seagate::kinetic::proto::Command_GetLog_Type_STATISTICS,
    com::seagate::kinetic::proto::Command_GetLog_Type_CONFIGURATION,
    com::seagate::kinetic::proto::Command_GetLog_Type_CAPACITIES,
    com::seagate::kinetic::proto::Command_GetLog_Type_TEMPERATURES,
    com::seagate::kinetic::proto::Command_GetLog_Type_UTILIZATIONS,
    com::seagate::kinetic::proto::Command_GetLog_Type_LIMITS,
    com::seagate::kinetic::proto::Command_GetLog_Type_MESSAGES
}) {
    struct ifaddrs* interfaceList(nullptr);

    if (getifaddrs(&interfaceList) == STATUS_FAILURE) {
        LOG(ERROR) << "Failed to obtain network interface information: error_code=" << errno << ", description=" << strerror(errno);
        return;
    }

    /*
        Put all the names in a set
    */

    std::set<string> interfaceNames;
    for (struct ifaddrs* interface = interfaceList; interface != nullptr; interface = interface->ifa_next) {
        interfaceNames.insert(string(interface->ifa_name));
    }

    for (string name : interfaceNames) {

        string ipv4, ipv6, macAddress;
        for (struct ifaddrs* interface = interfaceList; interface != nullptr; interface = interface->ifa_next) {
            if ((interface->ifa_addr == nullptr) || (name != string(interface->ifa_name)) || (name == "lo"))
                continue;

            int family = interface->ifa_addr->sa_family;

            if (family == AF_PACKET) {
                std::stringstream macAddressStream;
                unsigned char* address = &((struct sockaddr_ll*)interface->ifa_addr)->sll_addr[0];
                macAddressStream << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(address[0]) << ":"
                                 << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(address[1]) << ":"
                                 << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(address[2]) << ":"
                                 << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(address[3]) << ":"
                                 << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(address[4]) << ":"
                                 << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(address[5]);
                macAddress = macAddressStream.str();

                if (m_serialNumber.empty()) {
                    std::stringstream serialNumberStream;
                    serialNumberStream << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(address[0]) 
                                       << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(address[1])
                                       << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(address[2])
                                       << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(address[3])
                                       << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(address[4])
                                       << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(address[5]);
                    m_serialNumber = serialNumberStream.str();
                    m_worldWideName = WORLD_WIDE_NAME_PREFIX + m_serialNumber;
                }             

            }

            else if (family == AF_INET) {
                char addressBuffer[INET6_ADDRSTRLEN];
                ipv4 = inet_ntop(family, &((struct sockaddr_in*)interface->ifa_addr)->sin_addr, addressBuffer, sizeof(addressBuffer));
            }

            else if (family == AF_INET6) {
                char addressBuffer[INET6_ADDRSTRLEN];
                ipv6 = inet_ntop(family, &((struct sockaddr_in6*)interface->ifa_addr)->sin6_addr, addressBuffer, sizeof(addressBuffer));
            }
        }
        if (!ipv4.empty() && !ipv6.empty() && !macAddress.empty()) {
            NetworkInterfacePtr networkInterface(new NetworkInterface(name, macAddress, ipv4, ipv6));
            m_networkInterfaceMap[name] = networkInterface;
        }
    }
    freeifaddrs(interfaceList);
}



