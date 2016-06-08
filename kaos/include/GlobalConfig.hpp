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
#ifndef GLOBAL_CONFIG_HPP
#define GLOBAL_CONFIG_HPP

/*
 * Include Files
 */
#include <stdint.h>
#include <set>
#include <memory>
#include <string>
#include <sstream>
#include <typeinfo>
#include <unordered_map>
#include "Hmac.hpp"
#include "Kinetic.pb.hpp"
#include "NetworkInterface.hpp"

/*
 * Commonly Used Constants
 */
const int32_t  STATUS_SUCCESS(0);
const int32_t  STATUS_FAILURE(-1);

typedef std::set<com::seagate::kinetic::proto::Command_GetLog_Type> GetLogTypeSet;

/**
 * Contains read-only global configuration data.
 */
class GlobalConfig {
public:
    /*
     * Constructor
     */
    GlobalConfig();

    /*
     * Public Accessors
     */
    inline bool runAsDaemon() const {return m_runAsDaemon;}
    inline bool debugEnabled() const {return m_debugEnabled;}
    inline const char* pidFileName() const {return m_pidFileName;}
    inline std::string databaseDirectory() const {return m_databaseDirectory;}
    inline std::string sslPrivateKeyFile() const {return m_sslPrivateKeyFile;}
    inline std::string sslCertificateFile() const {return m_sslCertificateFile;}
    inline std::string serverSettingsFile() const {return m_serverSettingsFile;}
    inline const char* vendor() const {return m_vendor;}
    inline const char* model() const {return m_model;}
    inline const char* version() const {return m_version;}
    inline std::string serialNumber() const {return m_serialNumber;}
    inline std::string worldWideName() const {return m_worldWideName;}
    inline const char* protocolVersion() const {return m_protocolVersion;}
    inline const char* compilationDate() const {return m_compilationDate;}
    inline const char* sourceHash() const {return m_sourceHash;}
    inline bool objectStoreCompressionEnabled() const {return m_objectStoreCompressionEnabled;}
    inline uint32_t objectStoreCacheSize() const {return m_objectStoreCacheSize;}
    inline const std::string& flushDataKey() const {return m_flushDataKey;}
    inline uint32_t tcpPort() const {return m_tcpPort;}
    inline uint32_t sslPort() const {return m_sslPort;}
    inline uint32_t multicastPort() const {return m_multicastPort;}
    inline const char* multicastIpAddress() const {return m_multicastIpAddress;}
    inline uint32_t heartbeatSendInterval() const {return m_heartbeatSendInterval;}
    inline uint32_t heartbeatConnectionRetryInterval() const {return m_heartbeatConnectionRetryInterval;}
    inline size_t maxPendingConnections() const {return m_maxPendingConnections;}
    inline size_t maxActiveConnections() const {return m_maxActiveConnections;}
    inline size_t minKeySize() const {return m_minKeySize;}
    inline size_t maxKeySize() const {return m_maxKeySize;}
    inline size_t maxValueSize() const {return m_maxValueSize;}
    inline size_t maxVersionSize() const {return m_maxVersionSize;}
    inline size_t maxTagSize() const {return m_maxTagSize;}
    inline size_t maxOutstandingReadRequests() const {return m_maxOutstandingReadRequests;}
    inline size_t maxOutstandingWriteRequests() const {return m_maxOutstandingWriteRequests;}
    inline size_t maxMessageSize() const {return m_maxMessageSize;}
    inline size_t maxKeyRangeCount() const {return m_maxKeyRangeCount;}
    inline size_t maxIdentityCount() const {return m_maxIdentityCount;}
    inline size_t maxPinSize() const {return m_maxPinSize;}
    inline size_t maxOperationCountPerBatch() const {return m_maxOperationCountPerBatch;}
    inline size_t maxBatchCountPerDevice() const {return m_maxBatchCountPerDevice;}
    inline size_t maxAlgorithmSize() const {return m_maxAlgorithmSize;}
    inline size_t maxHmacKeySize() const {return m_maxHmacKeySize;}
    inline int64_t defaultClusterVersion() const {return m_defaultClusterVersion;}
    inline bool defaultLocked() const {return m_defaultLocked;}
    inline std::string defaultLockPin() const {return m_defaultLockPin;}
    inline std::string defaultErasePin() const {return m_defaultErasePin;}
    inline bool accessControlDefaultTlsRequired() const {return m_accessControlDefaultTlsRequired;}
    inline int64_t accessControlDefaultIdentity() const {return m_accessControlDefaultIdentity;}
    inline std::string accessControlDefaultHmacKey() const {return m_accessControlDefaultHmacKey;}
    inline HmacAlgorithm accessControlDefaultHmacAlgorithm() const {return m_accessControlDefaultHmacAlgorithm;}
    inline std::string accessScopeDefaultKeySubstring() const {return m_accessScopeDefaultKeySubstring;}
    inline uint32_t accessScopeDefaultKeySubstringOffset() const {return m_accessScopeDefaultKeySubstringOffset;}
    inline std::set<com::seagate::kinetic::proto::Command_GetLog_Type> defaultLogTypes() const {return m_defaultLogTypes;}
    inline NetworkInterfaceMap networkInterfaceMap() const {return m_networkInterfaceMap;}

private:
    /*
     * Private Data Members
     */
    bool                 m_runAsDaemon;                             //!< True if the server is to run in the background as a daemon
    bool                 m_debugEnabled;                            //!< True if the server is to run in debug mode (provide additional output)
    const char*          m_pidFileName;                             //!< Name of the server's process ID file (used by the start/stop script)
    std::string          m_databaseDirectory;                       //!< Path to the location of the database files
    std::string          m_serverSettingsFile;                      //!< Path to the location of the server settings file
    std::string          m_sslPrivateKeyFile;                       //!< Path to the location of the SSL private key file
    std::string          m_sslCertificateFile;                      //!< Path to the location of the SSL certificate file
    const char*          m_vendor;                                  //!< Text description of the vendor of the Kinetic device
    const char*          m_model;                                   //!< Text description of the model of the Kinetic device
    const char*          m_version;                                 //!< Text description of the version of the Kinetic device
    std::string          m_serialNumber;                            //!< Text description of the serial number of the Kinetic device
    std::string          m_worldWideName;                           //!< Text description of the world-wide name of the Kinetic device
    const char*          m_protocolVersion;                         //!< Text description of the supported Kinetic protocol version
    const char*          m_compilationDate;                         //!< Text description of the date the Kinetic code was compiled
    const char*          m_sourceHash;                              //!< Text description of the hast of the Kinetic source code
    bool                 m_objectStoreCompressionEnabled;           //!< True if compression is to be used by the object store
    uint32_t             m_objectStoreCacheSize;                    //!< Size of the object store's cache
    const std::string    m_flushDataKey;                            //!< Data key used to flush object store's data
    uint32_t             m_tcpPort;                                 //!< TCP port number for clear text communications
    uint32_t             m_sslPort;                                 //!< TCP port number of SSL/TLS communications
    uint32_t             m_multicastPort;                           //!< Multicast port number for heartbeat message broadcast
    const char*          m_multicastIpAddress;                      //!< Multicast IP address for heartbeat message broadcast
    uint32_t             m_heartbeatSendInterval;                   //!< Number of seconds between heartbeat message broadcast
    uint32_t             m_heartbeatConnectionRetryInterval;        //!< Number of seconds to wait between attempting heartbeat connection
    size_t               m_maxPendingConnections;                   //!< Number of allowed pending Kinetic connections
    uint32_t             m_maxActiveConnections;                    //!< Number of allowed active Kinetic connections
    size_t               m_minKeySize;                              //!< Number of bytes for smallest object key size
    size_t               m_maxKeySize;                              //!< Number of bytes for largest object key size
    size_t               m_maxValueSize;                            //!< Number of bytes for largest object value size
    size_t               m_maxVersionSize;                          //!< Number of bytes for largest object version size
    size_t               m_maxTagSize;                              //!< Number of bytes for largest object tag size
    size_t               m_maxAlgorithmSize;                        //!< Number of bytes for largest object algorithm size
    size_t               m_maxOutstandingReadRequests;              //!< Maximum number read requests allowed to be held at one time
    size_t               m_maxOutstandingWriteRequests;             //!< Maximum number writes requests allowed to be held at one time
    size_t               m_maxMessageSize;                          //!< Number of bytes for the largest message size
    size_t               m_maxKeyRangeCount;                        //!< Maximum count allowed for a get key range request
    size_t               m_maxIdentityCount;                        //!< Maximum number of identities allowed
    size_t               m_maxPinSize;                              //!< Maximum number of bytes allowed for a personal ID number
    size_t               m_maxOperationCountPerBatch;               //!< Maximum number of operations (put/delete) allowed for a single batch command
    size_t               m_maxBatchCountPerDevice;                  //!< Maximum number of active batch commands allowed on the server
    size_t               m_maxHmacKeySize;                          //!< Maximum number of bytes allowed for an HMAC key
    int64_t              m_defaultClusterVersion;                   //!< Default value fo the server's cluster version
    bool                 m_defaultLocked;                           //!< Default locked state for the server
    std::string          m_defaultLockPin;                          //!< Default value for the server's lock PIN
    std::string          m_defaultErasePin;                         //!< Default value for the server's erase PIN
    bool                 m_accessControlDefaultTlsRequired;         //!< TLS required value for the default access control
    int64_t              m_accessControlDefaultIdentity;            //!< Identity value for the default access control
    std::string          m_accessControlDefaultHmacKey;             //!< HMAC key value for the default access control
    HmacAlgorithm        m_accessControlDefaultHmacAlgorithm;       //!< HMAC algorithm value for the default access control
    std::string          m_accessScopeDefaultKeySubstring;          //!< Key substring value for the default access control
    uint32_t             m_accessScopeDefaultKeySubstringOffset;    //!< Key substring offset value for the default access control
    GetLogTypeSet        m_defaultLogTypes;                         //!< Log types returned when no type is specified for the get log request
    NetworkInterfaceMap  m_networkInterfaceMap;                     //!< Describes the network interface for the server
};

extern GlobalConfig globalConfig;

#endif
