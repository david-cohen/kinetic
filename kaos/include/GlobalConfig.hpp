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
#include "leveldb/slice.h"
#include "Hmac.hpp"
#include "Common.hpp"
#include "Kinetic.pb.hpp"
#include "NetworkInterface.hpp"

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
    inline bool debugEnabled() const {return m_debugEnabled;}
    inline std::string defaultPidFileName() const {return m_defaultPidFileName;}
    inline std::string databaseDirectory() const {return m_databaseDirectory;}
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
    inline int32_t maxPendingAdminConnections() const {return m_maxPendingAdminConnections;}
    inline uint32_t maxActiveAdminConnections() const {return m_maxActiveAdminConnections;}
    inline uint32_t tcpPort() const {return m_tcpPort;}
    inline uint32_t sslPort() const {return m_sslPort;}
    inline uint32_t multicastPort() const {return m_multicastPort;}
    inline const char* multicastIpAddress() const {return m_multicastIpAddress;}
    inline uint32_t heartbeatSendInterval() const {return m_heartbeatSendInterval;}
    inline uint32_t heartbeatConnectionRetryInterval() const {return m_heartbeatConnectionRetryInterval;}
    inline size_t minKeySize() const {return m_minKeySize;}
    inline size_t maxKeySize() const {return m_maxKeySize;}
    inline size_t maxValueSize() const {return m_maxValueSize;}
    inline size_t maxVersionSize() const {return m_maxVersionSize;}
    inline size_t maxTagSize() const {return m_maxTagSize;}
    inline size_t maxConnections() const {return m_maxConnectionse;}
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
    inline std::string sslPrivateKeyFile() const {return m_sslPrivateKeyFile;}
    inline std::string sslCertificateFile() const {return m_sslCertificateFile;}
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
    inline const leveldb::Slice& flushDataKey() const {return m_flushDataKey;}
    inline std::set<com::seagate::kinetic::proto::Command_GetLog_Type> defaultLogTypes() const {return m_defaultLogTypes;}
    inline NetworkInterfaceMap networkInterfaceMap() const {return m_networkInterfaceMap;}

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
    bool                 m_defaultLocked;
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

    DISALLOW_COPY_AND_ASSIGN(GlobalConfig);
};

extern GlobalConfig globalConfig;

#endif
