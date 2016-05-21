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
#ifndef OBJECT_STORE_INTERFACE_HPP
#define OBJECT_STORE_INTERFACE_HPP

/*
 * Include Files
 */
#include <stdint.h>
#include <string>
#include "Common.hpp"
#include "Kinetic.pb.hpp"
#include "AccessControl.hpp"

// Need to replace with non-leveldb specific object
#include "leveldb/db.h"
typedef leveldb::WriteBatch BatchDescriptor;

/**
 * Defines the interface for Kinetic object store.
 */
class ObjectStoreInterface {
public:
    virtual void putEntry(const com::seagate::kinetic::proto::Command_KeyValue& params, const std::string& value) = 0;
    virtual void deleteEntry(const com::seagate::kinetic::proto::Command_KeyValue& params) = 0;
    virtual void getEntry(const std::string& key, std::string& returnValue, com::seagate::kinetic::proto::Command_KeyValue* returnMetadata) = 0;
    virtual void getNextEntry(const std::string& key, std::string& returnValue, com::seagate::kinetic::proto::Command_KeyValue* returnMetadata) = 0;
    virtual void getPreviousEntry(const std::string& key, std::string& returnValue, com::seagate::kinetic::proto::Command_KeyValue* returnMetadata) = 0;
    virtual void getEntryMetadata(const std::string& key, bool versionOnly, com::seagate::kinetic::proto::Command_KeyValue* returnMetadata) = 0;
    virtual void getKeyRange(const com::seagate::kinetic::proto::Command_Range& params, AccessControlPtr& accessControl, com::seagate::kinetic::proto::Command_Range* returnData) = 0;
    virtual void getKeyRangeReversed(const com::seagate::kinetic::proto::Command_Range& params, AccessControlPtr& accessControl, com::seagate::kinetic::proto::Command_Range* returnData) = 0;
    virtual bool open() = 0;
    virtual void close() = 0;
    virtual void erase() = 0;
    virtual void flush() = 0;
    virtual void optimizeMedia() = 0;

    // these will be eliminated (and put into a batch object assoicated with the specified database
    virtual void batchedPutEntry(BatchDescriptor& batch, const com::seagate::kinetic::proto::Command_KeyValue& params, const std::string& value) = 0;
    virtual void batchedDeleteEntry(BatchDescriptor& batch, const com::seagate::kinetic::proto::Command_KeyValue& params) = 0;
    virtual void batchCommit(BatchDescriptor& batch) = 0;
};

#endif
