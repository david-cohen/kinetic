/*
 * Copyright (c) [2014 - 2016] Western Digital Technologies, Inc. All rights reserved.
 */
#pragma once
#ifndef OBJECT_STORE_HPP
#define OBJECT_STORE_HPP

/*
 * Include Files
 */
#include <stdint.h>
#include <list>
#include <string>
#include <memory>
#include "Common.hpp"
#include "leveldb/db.h"
#include "leveldb/write_batch.h"
#include "Kinetic.pb.hpp"
#include "AccessControl.hpp"

/*
 * Types taken from the Kinetic message.
 */
typedef com::seagate::kinetic::proto::Command_Synchronization PersistOption;
typedef com::seagate::kinetic::proto::Command_Algorithm Algorithm;
typedef leveldb::WriteBatch BatchDescriptor;

/*
 * Return Status
 */
enum class ReturnStatus {
    SUCCESS                           = 0,
    UNSUPPORTED_MESSAGE               = 1,
    FAILURE                           = 2,
    ENTRY_NOT_FOUND                   = 3,
    VERSION_MISMATCH                  = 4,
    KEY_SIZE_TOO_SMALL                = 5,
    KEY_SIZE_TOO_LARGE                = 6,
    START_KEY_SIZE_TOO_SMALL          = 7,
    START_KEY_SIZE_TOO_LARGE          = 8,
    END_KEY_SIZE_TOO_SMALL            = 9,
    END_KEY_SIZE_TOO_LARGE            = 10,
    VALUE_SIZE_TOO_LARGE              = 11,
    VERSION_SIZE_TOO_LARGE            = 12,
    TAG_SIZE_TOO_LARGE                = 13,
    ALGORITHM_SIZE_TOO_LARGE          = 14,
    INVALID_PERSIST_OPTION            = 15,
    MAX_KEYS_RETURNED_COUNT_TOO_LARGE = 16,
};

/*
 * Object Store
 *
 * Provides a Kinetic friendly wrapper for the levelDB database.
 */
class ObjectStore {

public:

    /*
     * Constructor/Destructor
     */
    explicit ObjectStore(std::string databaseDirectory);
    ~ObjectStore();

    /*
     * Public Member Functions
     */
    ReturnStatus open();
    ReturnStatus erase();
    ReturnStatus flush();
    ReturnStatus put(const std::string& key, const std::string& value, const std::string& newVersion,
                     const std::string& oldVersion, const std::string& tag, Algorithm algorithm, PersistOption persistOption);
    ReturnStatus putForced(const std::string& key, const std::string& value, const std::string& version,
                           const std::string& tag, Algorithm algorithm, PersistOption persistOption);
    ReturnStatus get(const std::string& key, std::string& value, std::string& version, std::string& tag, Algorithm& algorithm);
    ReturnStatus getNext(const std::string& key, std::string& nextKey, std::string& nextValue, std::string& newVersion, std::string& nextTag, Algorithm& nextAlgorithm);
    ReturnStatus getPrevious(const std::string& key, std::string& previousKey, std::string& previousValue,
                             std::string& previousVersion, std::string& previousTag, Algorithm& previousAlgorithm);
    ReturnStatus getMetadata(const std::string& key, std::string& version, std::string& tag, Algorithm& algorithm);
    ReturnStatus getKeyRange(const std::string& startKey, bool startKeyInclusive, const std::string& endKey,
                             bool endKeyInclusive, int32_t maxKeys, std::list<std::string>& keyList, AccessControlPtr& accessControl);
    ReturnStatus getKeyRangeReversed(const std::string& startKey, bool startKeyInclusive, const std::string& endKey,
                                     bool endKeyInclusive, int32_t maxKeys, std::list<std::string>& keyList, AccessControlPtr& accessControl);
    ReturnStatus deleteVersioned(const std::string& key, const std::string& version, PersistOption persistOption);
    ReturnStatus deleteForced(const std::string& key, PersistOption persistOption);
    ReturnStatus batchPut(BatchDescriptor& batch, const std::string& key, const std::string& value, const std::string&
                          newVersion, const std::string& oldVersion, const std::string& tag, Algorithm algorithm);
    ReturnStatus batchPutForced(BatchDescriptor& batch, const std::string& key, const std::string& value,
                                const std::string& version, const std::string& tag, Algorithm algorithm);
    ReturnStatus batchDelete(BatchDescriptor& batch, const std::string& key, const std::string& version);
    ReturnStatus batchDeleteForced(BatchDescriptor& batch, const std::string& key);
    ReturnStatus batchCommit(BatchDescriptor& batch);
    ReturnStatus optimizeMedia();
    std::string  getDatabaseDirectory() {return m_databaseDirectory;}

private:

    /*
     * Private Data Members
     */
    leveldb::DB*        m_database;             //!< Actual levelDB database
    const std::string   m_databaseDirectory;    //!< Directory where database files reside

    DISALLOW_COPY_AND_ASSIGN(ObjectStore);
};

/*
 * Shared pointer for ObjectStore
 */
typedef std::shared_ptr<ObjectStore> ObjectStorePtr;

extern ObjectStorePtr objectStore;

#endif
