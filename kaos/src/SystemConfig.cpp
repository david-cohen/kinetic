/*
 * Copyright (c) [2014 - 2016] Western Digital Technologies, Inc. All rights reserved.
 */

/*
 * Include Files
 */
#include <errno.h>
#include <stdio.h>
#include <stdint.h>
#include <ifaddrs.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netpacket/packet.h>
#include <boost/algorithm/string.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
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

/*
 * Used Namespaces
 */
using std::string;

/*
 * Identification
 */
static const char* VENDOR("WDC");
static const char* MODEL("Wasp");
static const char* VERSION("1.0.1-FOR-EVAL-ONLY");

/*
 * Daemon Related Settings
 */
static const char* DEFAULT_PID_FILE_NAME("/var/run/kaos.pid");
static const char* DEFAULT_CONFIG_FILE_NAME("/etc/default/kaos");
static const char* DEFAULT_STORAGE_DIRECTORY("/export/dfs");
static const char* DATABASE_DIRECTORY("objectDatabase");
static const char* SERVER_SETTINGS_FILE("serverSettings");
static const LogFacility LOGGING_FACILITY(LOCAL2);
static const LogLevel DEFAULT_LOGGING_LEVEL(WARNING);
static const bool DEFAULT_LOCKED(false);
static const bool DEFAULT_DEBUG_ENABLED(false);

/*
 * Object Store Settings
 */
static const bool OBJECT_STORE_COMPRESSION_ENABLED(false);
static const bool OBJECT_STORE_CACHE_SIZE(67108864);
static const char* FLUSH_DATA_KEY_PATTERN("04231970_WesternDigital_07913240");

/*
 * Communication Settings
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
 * Limits
 */
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
static const size_t MAX_OPERATION_COUNT_PER_BATCH(15);
static const size_t MAX_BATCH_COUNT_PER_DEVICE(5);
static const size_t MAX_ALGORITHM_SIZE(64);
static const size_t MAX_HMAC_KEY_SIZE(4096);

/*
 * SSL Settings
 */
static const char* SSL_PRIVATE_KEY_FILE("/etc/kaos/cert.pem");
static const char* SSL_CERTIFICATE_FILE("/etc/kaos/cert.pem");

/*
 * Setup Settings
 */
static const int64_t DEFAULT_CLUSTER_VERSION(0);
static const char* DEFAULT_LOCK_PIN("");
static const char* DEFAULT_ERASE_PIN("");

/*
 * Access Settings
 */
static const bool ACCESS_CONTROL_DEFAULT_TLS_REQUIRED(false);
static const int64_t ACCESS_CONTROL_DEFAULT_IDENTITY(1);
static const char* ACCESS_CONTROL_DEFAULT_HMAC_KEY("asdfasdf");
static const HmacAlgorithm ACCESS_CONTROL_DEFAULT_HMAC_ALGORITHM(HmacAlgorithm::SHA1);
static const char* ACCESS_SCOPE_DEFAULT_KEY_SUBSTRING("");
static const uint32_t ACCESS_SCOPE_DEFAULT_KEY_SUBSTRING_OFFSET(0);

/**
 * Creates a flush data key (a key used to purge the database of write-back data).  The key must not
 * be a valid user key, which is accomplished by making it larger than the maximum size of a user
 * key.
 *
 * @return  The key used to perform a flush write on the database
 */
static std::string
createFlushDataKey() {
    std::string flushDataKey;
    while (flushDataKey.size() <= MAX_KEY_SIZE) {
        flushDataKey.append(FLUSH_DATA_KEY_PATTERN);
    }
    return flushDataKey;
}

/**
 * Translates log level in string form to the LogLevel format.  If no valid log level is found, then
 * the default log level will be returned.
 *
 * @param   logLevel    String form of the log level
 *
 * @return  Enum value of LogLevel
 */
static LogLevel
toLogLevel(std::string logLevel) {

    if (logLevel == "ERROR")
        return ERROR;
    else if (logLevel == "WARNING")
        return WARNING;
    else if (logLevel == "INFO")
        return INFO;
    else if (logLevel == "DEBUG")
        return DEBUG;
    else
        return DEFAULT_LOGGING_LEVEL;
}

/**
 * Initializes the system configuration object, which contains the attributes that a user can not
 * set.
 */
SystemConfig::SystemConfig()
    : m_locked(DEFAULT_LOCKED),
      m_debugEnabled(DEFAULT_DEBUG_ENABLED),
      m_defaultPidFileName(DEFAULT_PID_FILE_NAME),
      m_databaseDirectory(),
      m_serverSettingsFile(),
      m_vendor(VENDOR),
      m_model(MODEL),
      m_version(VERSION),
      m_serialNumber(),
      m_worldWideName(),
      m_protocolVersion(PROTOCOL_VERSION),
      m_compilationDate(TIMESTAMP),
      m_sourceHash(SOURCE_HASH),
      m_objectStoreCompressionEnabled(OBJECT_STORE_COMPRESSION_ENABLED),
      m_objectStoreCacheSize(OBJECT_STORE_CACHE_SIZE),
      m_maxPendingAdminConnections(MAX_PENDING_ADMIN_CONNECTIONS),
      m_maxActiveAdminConnections(MAX_ACTIVE_ADMIN_CONNECTIONS),
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

    /*
     * Read configuration data from the default configuration file.
     */
    boost::property_tree::ptree defaultConfigData;
    boost::property_tree::ini_parser::read_ini(DEFAULT_CONFIG_FILE_NAME, defaultConfigData);

    /*
     * Set the logging level first, so that events can be logged correctly fro the beginning.
     */
    LogLevel loggingLevel = toLogLevel(defaultConfigData.get<string>("LOGGING_LEVEL", "WARNING"));
    logControl.open(LOGGING_FACILITY, loggingLevel);
    m_debugEnabled = loggingLevel == DEBUG;

    /*
     * Set the location of the database and server settings.
     */
    string storageDirectory(DEFAULT_STORAGE_DIRECTORY);
    string specifiedStorageDirectory = defaultConfigData.get<std::string>("ROOT_STORAGE_DIRECTORY", DEFAULT_STORAGE_DIRECTORY);
    if (!specifiedStorageDirectory.empty()) {
        struct stat info;
        if (stat(specifiedStorageDirectory.c_str(), &info) == STATUS_SUCCESS)
            storageDirectory = specifiedStorageDirectory;
        else
            LOG(ERROR) << "Specified storage directory (" << specifiedStorageDirectory << ") failed stat: Error Code=" << errno << ", Description=" << strerror(errno);
    }

    m_databaseDirectory = storageDirectory + "/" + DATABASE_DIRECTORY;
    m_serverSettingsFile = storageDirectory + "/" + SERVER_SETTINGS_FILE;

    /*
     * Discover the network interfaces.
     */
    struct ifaddrs* interfaceList(nullptr);

    if (getifaddrs(&interfaceList) == STATUS_FAILURE) {
        LOG(ERROR) << "Failed to obtain network interface information: Error Code=" << errno << ", Description=" << strerror(errno);
        return;
    }

    /*
     * Gather network interface information (which is reported in the Kinetic protocol).
     */
    std::set<string> interfaceNames;
    for (struct ifaddrs* interface = interfaceList; interface != nullptr; interface = interface->ifa_next)
        interfaceNames.insert(string(interface->ifa_name));

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

    /*
     * Get the serial number and world-wide name from the drive.
     */
    FILE* fp = popen("/sbin/hdparm -I /dev/sda", "r");
    if (fp == nullptr) {
        LOG(ERROR) << "Failed to obtain drive information: Error Code=" << errno << ", Description=" << strerror(errno);
    }
    else {
        char* line = nullptr;
        size_t length = 0;
        ssize_t read;
        const int32_t GET_LINE_FAILURE(-1);
        const string serialNumberLabel("Serial Number:");
        const string worldWideNameLabel("Logical Unit WWN Device Identifier:");
        while ((read = getline(&line, &length, fp)) != GET_LINE_FAILURE) {
            string stringLine(line);
            if (m_serialNumber.empty()) {
                std::size_t index = stringLine.find(serialNumberLabel);
                if (index != std::string::npos)
                    m_serialNumber = stringLine.substr(index + serialNumberLabel.size());
            }

            if (m_worldWideName.empty()) {
                std::size_t index = stringLine.find(worldWideNameLabel);
                if (index != std::string::npos)
                    m_worldWideName = stringLine.substr(index + worldWideNameLabel.size());
            }
        }
        free(line);
        pclose(fp);
        boost::trim(m_serialNumber);
        boost::trim(m_worldWideName);
    }
}
