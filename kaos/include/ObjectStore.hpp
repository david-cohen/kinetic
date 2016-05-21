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
#include "ObjectStoreInterface.hpp"

/**
 * Object database of the Kinetic server.  It provides a Kinetic friendly interface to the levelDB
 * database.
 */
class ObjectStore : public ObjectStoreInterface {

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

private:

    leveldb::WriteOptions& getWriteOptions(com::seagate::kinetic::proto::Command_Synchronization option);

    /*
     * Private Data Members
     */
    leveldb::DB*            m_database;     //!< Actual levelDB database
    std::recursive_mutex    m_mutex;        //!< Mutex to make object thread safe

    DISALLOW_COPY_AND_ASSIGN(ObjectStore);
};

#endif
