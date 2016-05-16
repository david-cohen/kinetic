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
#ifndef SYSTEM_CONFIG_HPP
#define SYSTEM_CONFIG_HPP

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
#include "leveldb/slice.h"
#include "Hmac.hpp"
#include "Common.hpp"
#include "Kinetic.pb.hpp"
#include "NetworkInterface.hpp"

typedef std::set<com::seagate::kinetic::proto::Command_GetLog_Type> GetLogTypeSet;

/**
 * Contains the system configuration data that can not be set by a user.
 */
class SystemConfig {
public:

    /*
     * Constructor
     */
    SystemConfig();

    /*
     * Public Accessors
     */
    inline bool locked() { return m_locked;}
    inline void setLocked(bool locked) {m_locked = locked;}
    inline bool debugEnabled() { return m_debugEnabled;}
    inline std::string defaultPidFileName() {return m_defaultPidFileName;}
    inline std::string databaseDirectory() {return m_databaseDirectory;}
    inline std::string serverSettingsFile() {return m_serverSettingsFile;}
    inline const char* vendor() {return m_vendor;}
    inline const char* model() {return m_model;}
    inline const char* version() {return m_version;}
    inline std::string serialNumber() {return m_serialNumber;}
    inline std::string worldWideName() {return m_worldWideName;}
    inline const char* protocolVersion() {return m_protocolVersion;}
    inline const char* compilationDate() {return m_compilationDate;}
    inline const char* sourceHash() {return m_sourceHash;}
    inline bool objectStoreCompressionEnabled() {return m_objectStoreCompressionEnabled;}
    inline uint32_t objectStoreCacheSize() {return m_objectStoreCacheSize;}
    inline int32_t maxPendingAdminConnections() {return m_maxPendingAdminConnections;}
    inline uint32_t maxActiveAdminConnections() {return m_maxActiveAdminConnections;}
    inline uint32_t tcpPort() {return m_tcpPort;}
    inline uint32_t sslPort() {return m_sslPort;}
    inline uint32_t multicastPort() {return m_multicastPort;}
    inline const char* multicastIpAddress() {return m_multicastIpAddress;}
    inline uint32_t heartbeatSendInterval() {return m_heartbeatSendInterval;}
    inline uint32_t heartbeatConnectionRetryInterval() {return m_heartbeatConnectionRetryInterval;}
    inline size_t minKeySize() {return m_minKeySize;}
    inline size_t maxKeySize() {return m_maxKeySize;}
    inline size_t maxValueSize() {return m_maxValueSize;}
    inline size_t maxVersionSize() {return m_maxVersionSize;}
    inline size_t maxTagSize() {return m_maxTagSize;}
    inline size_t maxConnections() {return m_maxConnectionse;}
    inline size_t maxOutstandingReadRequests() {return m_maxOutstandingReadRequests;}
    inline size_t maxOutstandingWriteRequests() {return m_maxOutstandingWriteRequests;}
    inline size_t maxMessageSize() {return m_maxMessageSize;}
    inline size_t maxKeyRangeCount() {return m_maxKeyRangeCount;}
    inline size_t maxIdentityCount() {return m_maxIdentityCount;}
    inline size_t maxPinSize() {return m_maxPinSize;}
    inline size_t maxOperationCountPerBatch() {return m_maxOperationCountPerBatch;}
    inline size_t maxBatchCountPerDevice() {return m_maxBatchCountPerDevice;}
    inline size_t maxAlgorithmSize() {return m_maxAlgorithmSize;}
    inline size_t maxHmacKeySize() {return m_maxHmacKeySize;}
    inline std::string sslPrivateKeyFile() {return m_sslPrivateKeyFile;}
    inline std::string sslCertificateFile() {return m_sslCertificateFile;}
    inline int64_t defaultClusterVersion() {return m_defaultClusterVersion;}
    inline std::string defaultLockPin() {return m_defaultLockPin;}
    inline std::string defaultErasePin() {return m_defaultErasePin;}
    inline bool accessControlDefaultTlsRequired() {return m_accessControlDefaultTlsRequired;}
    inline int64_t accessControlDefaultIdentity() {return m_accessControlDefaultIdentity;}
    inline std::string accessControlDefaultHmacKey() {return m_accessControlDefaultHmacKey;}
    inline HmacAlgorithm accessControlDefaultHmacAlgorithm() {return m_accessControlDefaultHmacAlgorithm;}
    inline std::string accessScopeDefaultKeySubstring() {return m_accessScopeDefaultKeySubstring;}
    inline uint32_t accessScopeDefaultKeySubstringOffset() {return m_accessScopeDefaultKeySubstringOffset;}
    inline const leveldb::Slice& flushDataKey() {return m_flushDataKey;}
    inline std::set<com::seagate::kinetic::proto::Command_GetLog_Type> defaultLogTypes() {return m_defaultLogTypes;}
    inline NetworkInterfaceMap networkInterfaceMap() {return m_networkInterfaceMap;}

private:

    /*
     * Private Data Members
     */
    bool                 m_locked;
    bool                 m_debugEnabled;
    std::string          m_defaultPidFileName;
    std::string          m_databaseDirectory;
    std::string          m_serverSettingsFile;
    const char*          m_vendor;
    const char*          m_model;
    const char*          m_version;
    std::string          m_serialNumber;
    std::string          m_worldWideName;
    const char*          m_protocolVersion;
    const char*          m_compilationDate;
    const char*          m_sourceHash;
    bool                 m_objectStoreCompressionEnabled;
    uint32_t             m_objectStoreCacheSize;
    int32_t              m_maxPendingAdminConnections;
    uint32_t             m_maxActiveAdminConnections;
    uint32_t             m_tcpPort;
    uint32_t             m_sslPort;
    uint32_t             m_multicastPort;
    const char*          m_multicastIpAddress;
    uint32_t             m_heartbeatSendInterval;
    uint32_t             m_heartbeatConnectionRetryInterval;
    size_t               m_minKeySize;
    size_t               m_maxKeySize;
    size_t               m_maxValueSize;
    size_t               m_maxVersionSize;
    size_t               m_maxTagSize;
    size_t               m_maxConnectionse;
    size_t               m_maxOutstandingReadRequests;
    size_t               m_maxOutstandingWriteRequests;
    size_t               m_maxMessageSize;
    size_t               m_maxKeyRangeCount;
    size_t               m_maxIdentityCount;
    size_t               m_maxPinSize;
    size_t               m_maxOperationCountPerBatch;
    size_t               m_maxBatchCountPerDevice;
    size_t               m_maxAlgorithmSize;
    size_t               m_maxHmacKeySize;
    std::string          m_sslPrivateKeyFile;
    std::string          m_sslCertificateFile;
    int64_t              m_defaultClusterVersion;
    std::string          m_defaultLockPin;
    std::string          m_defaultErasePin;
    bool                 m_accessControlDefaultTlsRequired;
    int64_t              m_accessControlDefaultIdentity;
    std::string          m_accessControlDefaultHmacKey;
    HmacAlgorithm        m_accessControlDefaultHmacAlgorithm;
    std::string          m_accessScopeDefaultKeySubstring;
    uint32_t             m_accessScopeDefaultKeySubstringOffset;
    const leveldb::Slice m_flushDataKey;
    GetLogTypeSet        m_defaultLogTypes;
    NetworkInterfaceMap  m_networkInterfaceMap;

    DISALLOW_COPY_AND_ASSIGN(SystemConfig);
};

extern SystemConfig systemConfig;

#endif
