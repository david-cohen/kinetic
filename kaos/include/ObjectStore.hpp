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
#include <mutex>
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

/**
 * Object database of the Kinetic server.  It provides a Kinetic friendly interface to the levelDB
 * database.
 */
class ObjectStore {

public:

    /*
     * Constructor/Destructor
     */
    ObjectStore();
    ~ObjectStore();

    /*
     * Public Member Functions
     */
    bool open();
    void close();
    void erase();
    void flush();
    void optimizeMedia();
    void putEntry(const com::seagate::kinetic::proto::Command_KeyValue& params, const std::string& value);
    void batchedPutEntry(BatchDescriptor& batch, const com::seagate::kinetic::proto::Command_KeyValue& params, const std::string& value);
    void deleteEntry(const com::seagate::kinetic::proto::Command_KeyValue& params);
    void batchedDeleteEntry(BatchDescriptor& batch, const com::seagate::kinetic::proto::Command_KeyValue& params);
    void batchCommit(BatchDescriptor& batch);
    void getEntry(const std::string& key, std::string& returnValue, com::seagate::kinetic::proto::Command_KeyValue* returnMetadata);
    void getNextEntry(const std::string& key, std::string& returnValue, com::seagate::kinetic::proto::Command_KeyValue* returnMetadata);
    void getPreviousEntry(const std::string& key, std::string& returnValue, com::seagate::kinetic::proto::Command_KeyValue* returnMetadata);
    void getEntryMetadata(const std::string& key, bool versionOnly, com::seagate::kinetic::proto::Command_KeyValue* returnMetadata);
    void getKeyRange(const com::seagate::kinetic::proto::Command_Range& params, AccessControlPtr& accessControl, com::seagate::kinetic::proto::Command_Range* returnData);
    void getKeyRangeReversed(const com::seagate::kinetic::proto::Command_Range& params, AccessControlPtr& accessControl, com::seagate::kinetic::proto::Command_Range* returnData);
    leveldb::WriteOptions& getWriteOptions(PersistOption option);

private:

    /*
     * Private Data Members
     */
    leveldb::DB*            m_database;     //!< Actual levelDB database
    std::recursive_mutex    m_mutex;        //!< Mutex to make object thread safe

    DISALLOW_COPY_AND_ASSIGN(ObjectStore);
};

extern ObjectStore objectStore;

#endif
