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
#pragma once
#ifndef ROCKS_DB_OBJECT_STORE_HPP
#define ROCKS_DB_OBJECT_STORE_HPP

/*
 * Include Files
 */
#include <stdint.h>
#include <list>
#include <mutex>
#include <string>
#include <memory>
#include "rocksdb/db.h"
#include "rocksdb/write_batch.h"
#include "Kinetic.pb.hpp"
#include "AccessControl.hpp"
#include "ObjectStoreInterface.hpp"

/*
 * Incomplete Class Definition
 */
class RocksDbBatch;

/**
 * Level DB object store with a Kinetic API.
 */
class RocksDbObjectStore : public ObjectStoreInterface {
public:
    /*
     * Constructor/Destructor
     */
    RocksDbObjectStore();
    ~RocksDbObjectStore();

    /*
     * Public Member Functions
     */
    bool open();
    void close();
    void erase();
    void flush();
    void optimizeMedia();
    BatchInterface* createBatch();
    void putEntry(const com::seagate::kinetic::proto::Command_KeyValue& params, const std::string& value);
    void deleteEntry(const com::seagate::kinetic::proto::Command_KeyValue& params);
    void getEntry(const std::string& key, std::string& returnValue, com::seagate::kinetic::proto::Command_KeyValue* returnMetadata);
    void getNextEntry(const std::string& key, std::string& returnValue, com::seagate::kinetic::proto::Command_KeyValue* returnMetadata);
    void getPreviousEntry(const std::string& key, std::string& returnValue, com::seagate::kinetic::proto::Command_KeyValue* returnMetadata);
    void getEntryMetadata(const std::string& key, bool versionOnly, com::seagate::kinetic::proto::Command_KeyValue* returnMetadata);
    void getKeyRange(const com::seagate::kinetic::proto::Command_Range& params, AccessControlPtr& accessControl,
                     com::seagate::kinetic::proto::Command_Range* returnData);
    void getKeyRangeReversed(const com::seagate::kinetic::proto::Command_Range& params, AccessControlPtr& accessControl,
                             com::seagate::kinetic::proto::Command_Range* returnData);
    void batchedPutEntry(rocksdb::WriteBatch& batch, const com::seagate::kinetic::proto::Command_KeyValue& params, const std::string& value);
    void batchedDeleteEntry(rocksdb::WriteBatch& batch, const com::seagate::kinetic::proto::Command_KeyValue& params);
    void batchCommit(rocksdb::WriteBatch& batch);

private:
    /*
     * Private Member Functions
     */
    rocksdb::WriteOptions& getWriteOptions(com::seagate::kinetic::proto::Command_Synchronization option);

    /*
     * Private Data Members
     */
    rocksdb::DB*            m_database;     //!< Actual levelDB database
    std::recursive_mutex    m_mutex;        //!< Mutex to make object thread safe
};

#endif
