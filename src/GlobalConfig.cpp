/*
 * Copyright (c) 2014-2016 Western Digital Corporation or its affiliates <copyrightagent@wdc.com>
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

/*
 * Include Files
 */
#include <fcntl.h>
#include <errno.h>
#include <stdint.h>
#include <unistd.h>
#include <net/if.h>
#include <ifaddrs.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <linux/hdreg.h>
#include <netpacket/packet.h>
#include <boost/algorithm/string.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <set>
#include <string>
#include <memory>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include "Hmac.hpp"
#include "Logger.hpp"
#include "Kinetic.pb.hpp"
#include "GlobalConfig.hpp"

/*
 * Used Namespace Members
 */
using std::string;

/*
 * Identification
 */
static const char* VENDOR("WDC");
static const char* MODEL("Wasp");
static const char* VERSION("1.0.6");

/*
 * Daemon Related Settings
 */
static const char* DRIVE_DEV_NODE("/dev/sda");
static const char* PID_FILE_NAME("/var/run/kaos.pid");
static const char* CONFIG_FILE_NAME("/etc/default/kaos");
static const char* DEFAULT_STORAGE_DIRECTORY("/export/dfs");
static const char* DATABASE_DIRECTORY("objectDatabase");
static const char* SERVER_SETTINGS_FILE("serverSettings");
static const LogFacility LOGGING_FACILITY(LOCAL2);
static const LogLevel DEFAULT_LOGGING_LEVEL(WARNING);
static const bool DEBUG_ENABLED(false);

/*
 * Object Store Settings
 */
static const bool OBJECT_STORE_COMPRESSION_ENABLED(false);
static const bool OBJECT_STORE_CACHE_SIZE(67108864);
static const char* FLUSH_DATA_KEY_PATTERN("04231970_WesternDigital_07913240");

/*
 * Communication Settings
 */
static const size_t   MAX_PENDING_CONNECTIONS(8);
static const uint32_t MAX_ACTIVE_CONNECTIONS(128);
static const uint32_t TCP_PORT(8123);
static const uint32_t SSL_PORT(8443);
static const uint32_t MULTICAST_PORT(8123);
static const char*    MULTICAST_IP_ADDRESS("239.1.2.3");
static const char*    PROTOCOL_VERSION("3.0.6");
static const uint32_t HEARTBEAT_SEND_INTERVAL(60);
static const uint32_t HEARTBEAT_CONNECTION_RETRY_INTERVAL(60);

/*
 * Limits
 */
static const size_t MIN_KEY_SIZE(1);
static const size_t MAX_KEY_SIZE(4096);
static const size_t MAX_VALUE_SIZE(1048576);
static const size_t MAX_VERSION_SIZE(2048);
static const size_t MAX_TAG_SIZE(4096);
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
static const bool DEFAULT_LOCKED(false);
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
static std::string createFlushDataKey() {
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
static LogLevel toLogLevel(std::string logLevel) {
    std::transform(logLevel.begin(), logLevel.end(), logLevel.begin(), ::toupper);
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
GlobalConfig::GlobalConfig()
    : m_debugEnabled(DEBUG_ENABLED),
      m_pidFileName(PID_FILE_NAME),
      m_databaseDirectory(),
      m_serverSettingsFile(),
      m_sslPrivateKeyFile(SSL_PRIVATE_KEY_FILE),
      m_sslCertificateFile(SSL_CERTIFICATE_FILE),
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
      m_flushDataKey(createFlushDataKey()),
      m_tcpPort(TCP_PORT),
      m_sslPort(SSL_PORT),
      m_multicastPort(MULTICAST_PORT),
      m_multicastIpAddress(MULTICAST_IP_ADDRESS),
      m_heartbeatSendInterval(HEARTBEAT_SEND_INTERVAL),
      m_heartbeatConnectionRetryInterval(HEARTBEAT_CONNECTION_RETRY_INTERVAL),
      m_maxPendingConnections(MAX_PENDING_CONNECTIONS),
      m_maxActiveConnections(MAX_ACTIVE_CONNECTIONS),
      m_minKeySize(MIN_KEY_SIZE),
      m_maxKeySize(MAX_KEY_SIZE),
      m_maxValueSize(MAX_VALUE_SIZE),
      m_maxVersionSize(MAX_VERSION_SIZE),
      m_maxTagSize(MAX_TAG_SIZE),
      m_maxAlgorithmSize(MAX_ALGORITHM_SIZE),
      m_maxOutstandingReadRequests(MAX_OUTSTANDING_READ_REQUESTS),
      m_maxOutstandingWriteRequests(MAX_OUTSTANDING_WRITE_REQUESTS),
      m_maxMessageSize(MAX_MESSAGE_SIZE),
      m_maxKeyRangeCount(MAX_KEY_RANGE_COUNT),
      m_maxIdentityCount(MAX_IDENTITY_COUNT),
      m_maxPinSize(MAX_PIN_SIZE),
      m_maxOperationCountPerBatch(MAX_OPERATION_COUNT_PER_BATCH),
      m_maxBatchCountPerDevice(MAX_BATCH_COUNT_PER_DEVICE),
      m_maxHmacKeySize(MAX_HMAC_KEY_SIZE),
      m_defaultClusterVersion(DEFAULT_CLUSTER_VERSION),
      m_defaultLocked(DEFAULT_LOCKED),
      m_defaultLockPin(DEFAULT_LOCK_PIN),
      m_defaultErasePin(DEFAULT_ERASE_PIN),
      m_accessControlDefaultTlsRequired(ACCESS_CONTROL_DEFAULT_TLS_REQUIRED),
      m_accessControlDefaultIdentity(ACCESS_CONTROL_DEFAULT_IDENTITY),
      m_accessControlDefaultHmacKey(ACCESS_CONTROL_DEFAULT_HMAC_KEY),
      m_accessControlDefaultHmacAlgorithm(ACCESS_CONTROL_DEFAULT_HMAC_ALGORITHM),
      m_accessScopeDefaultKeySubstring(ACCESS_SCOPE_DEFAULT_KEY_SUBSTRING),
      m_accessScopeDefaultKeySubstringOffset(ACCESS_SCOPE_DEFAULT_KEY_SUBSTRING_OFFSET),
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
    boost::property_tree::ini_parser::read_ini(CONFIG_FILE_NAME, defaultConfigData);

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
        else {
            LOG(ERROR) << "Specified storage directory (" << specifiedStorageDirectory << ") failed stat: error code="
                       << errno << ", description=" << strerror(errno);
        }
    }

    m_databaseDirectory = storageDirectory + "/" + DATABASE_DIRECTORY;
    m_serverSettingsFile = storageDirectory + "/" + SERVER_SETTINGS_FILE;

    /*
     * Get the serial number and world-wide name of the drive.
     */
    int32_t driveHandle = open(DRIVE_DEV_NODE, O_RDONLY | O_NONBLOCK);
    if (driveHandle < 0) {
        LOG(ERROR) << "Failed to access drive information: error code=" << errno << ", description=" << strerror(errno);
    }
    else {
        struct hd_driveid driveInfo;
        if (ioctl(driveHandle, HDIO_GET_IDENTITY, &driveInfo) != STATUS_SUCCESS) {
            LOG(ERROR) << "Failed to obtain drive information: error code=" << errno << ", description=" << strerror(errno);
        }
        else {
            /*
             * Null terminate the serial number character array (we don't care that we set to zero
             * the buf_type field that follows the serial number because we don't use it and it has
             * been retired. Also, remove any space characters.  Convert the world-wide name to a
             * hex string.
             */
            const uint32_t SERIAL_NUMBER_SIZE(20);
            driveInfo.serial_no[SERIAL_NUMBER_SIZE] = 0;
            m_serialNumber = reinterpret_cast<char*>(driveInfo.serial_no);
            boost::trim(m_serialNumber);

            const uint32_t WWN_STARTING_INDEX(4);
            std::stringstream worldWideNameStream;
            worldWideNameStream << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(driveInfo.words104_125[WWN_STARTING_INDEX])
                                << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(driveInfo.words104_125[WWN_STARTING_INDEX + 1])
                                << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(driveInfo.words104_125[WWN_STARTING_INDEX + 2])
                                << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(driveInfo.words104_125[WWN_STARTING_INDEX + 3]);
            m_worldWideName = worldWideNameStream.str();
            boost::trim(m_worldWideName);
        }
        close(driveHandle);
    }
}

/**
 * Obtains the network interface information.
 *
 * @return a list of the network interfaces
 */
NetworkInterfaceList GlobalConfig::networkInterfaceList() {
    NetworkInterfaceList  networkInterfaceList;

    /*
     * Discover the network interfaces.
     */
    struct ifaddrs* interfaceList(nullptr);
    if (getifaddrs(&interfaceList) == STATUS_FAILURE) {
        LOG(ERROR) << "Failed to obtain network interface information: error code=" << errno << ", description=" << strerror(errno);
        return networkInterfaceList;
    }

    /*
     * Gather the network interface names (eliminating duplicates by using a set).
     */
    std::set<string> interfaceNames;
    for (struct ifaddrs* interface = interfaceList; interface != nullptr; interface = interface->ifa_next) {
        string interfaceName(interface->ifa_name);
        if (interfaceName != "lo")
            interfaceNames.insert(interfaceName);
    }

    /*
     * Open the socket that will be used to perform the I/O control commands.
     */
    const int USE_DEFAULT_PROTOCOL(0);
    int socketFileDescriptor = socket(AF_INET, SOCK_DGRAM, USE_DEFAULT_PROTOCOL);
    if (socketFileDescriptor < 0) {
        LOG(ERROR) << "Failed to open socket for network settings: error code=" << errno << ", description=" << strerror(errno);
        return networkInterfaceList;
    }

    /*
     * Get the version 4 IP address, version 6 IP address, and MAC address of each interface.  If an
     * interface doesn't have all three, don't report it.
     */
    for (string interfaceName : interfaceNames) {
        string ipv4, ipv6, macAddress;
        struct ifreq interfaceRequest;
        memset(&interfaceRequest, 0, sizeof(interfaceRequest));
        strncpy(interfaceRequest.ifr_name, interfaceName.c_str(), IFNAMSIZ);
        interfaceRequest.ifr_addr.sa_family = AF_INET;

        /*
         * Get the version 4 IP address.
         */
        if (ioctl(socketFileDescriptor, SIOCGIFADDR, &interfaceRequest) == STATUS_SUCCESS) {
            char addressBuffer[INET6_ADDRSTRLEN];
            struct sockaddr_in* sockaddr = static_cast<struct sockaddr_in*>(static_cast<void*>(&interfaceRequest.ifr_addr));
            ipv4 = inet_ntop(AF_INET, &sockaddr->sin_addr, addressBuffer, sizeof(addressBuffer));

            /*
             * Get the version 6 IP address.
             */
            for (struct ifaddrs* interface = interfaceList; interface != nullptr; interface = interface->ifa_next) {
                if ((interface->ifa_addr != nullptr) && (interfaceName == string(interface->ifa_name))
                        && (interface->ifa_addr->sa_family == AF_INET6)) {
                    char addressBuffer[INET6_ADDRSTRLEN];
                    struct sockaddr_in6* sockaddr = static_cast<struct sockaddr_in6*>(static_cast<void*>(interface->ifa_addr));
                    ipv6 = inet_ntop(AF_INET6, &sockaddr->sin6_addr, addressBuffer, sizeof(addressBuffer));
                    break;
                }
            }

            /*
             * Get the MAC address.
             */
            memset(&interfaceRequest, 0, sizeof(interfaceRequest));
            strncpy(interfaceRequest.ifr_name, interfaceName.c_str(), IFNAMSIZ);
            if (ioctl(socketFileDescriptor, SIOCGIFHWADDR, &interfaceRequest) == STATUS_SUCCESS) {
                std::stringstream macAddressStream;
                macAddressStream << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(interfaceRequest.ifr_hwaddr.sa_data[0]) << ":"
                                 << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(interfaceRequest.ifr_hwaddr.sa_data[1]) << ":"
                                 << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(interfaceRequest.ifr_hwaddr.sa_data[2]) << ":"
                                 << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(interfaceRequest.ifr_hwaddr.sa_data[3]) << ":"
                                 << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(interfaceRequest.ifr_hwaddr.sa_data[4]) << ":"
                                 << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(interfaceRequest.ifr_hwaddr.sa_data[5]);
                macAddress = macAddressStream.str();
            }

            /*
             * Report the interface if it has all of the required information.
             */
            if (!ipv4.empty() && !ipv6.empty() && !macAddress.empty()) {
                NetworkInterfacePtr networkInterface(new NetworkInterface(interfaceName, macAddress, ipv4, ipv6));
                networkInterfaceList.push_back(networkInterface);
            }
        }
    }

    close(socketFileDescriptor);
    freeifaddrs(interfaceList);
    return networkInterfaceList;
}

