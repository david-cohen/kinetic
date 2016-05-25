/*
 * Copyright (c) 2014-2016 Western Digital Technologies, Inc. <copyrightagent@wdc.com>
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
#ifndef LEVEL_DB_BATCH_HPP
#define LEVEL_DB_BATCH_HPP

/*
 * Include Files
 */
#include <string>
#include "leveldb/write_batch.h"
#include "BatchInterface.hpp"
#include "LevelDbObjectStore.hpp"

/**
 * Level DB batch operator object used to support Kinetic batch operations (performing a group of
 * puts and deletes as a single transaction).
 */
class LevelDbBatch : public BatchInterface {
public:
    /**
     * Initializes the object.
     */
    explicit LevelDbBatch(LevelDbObjectStore* const objectStore)
        : m_objectStore(objectStore) {}

    /**
     * Adds a put request to the batch operation to be performed.
     *
     * @param   params  The entry's metadata and if the put is to be "forced"
     * @param   value   The value of the entry to be put in the object store
     *
     * @throws  VERSION_MISMATCH if the existing entry's version does not match the one specified
     */
    inline void putEntry(const com::seagate::kinetic::proto::Command_KeyValue& params, const std::string& value) {
        m_objectStore->batchedPutEntry(m_batchDescriptor, params, value);
    }

    /**
     * Adds a delete request to the batch operation to be performed.
     *
     * @param   params  The key of the entry, persistence option, and if the delete is to be "forced"
     *
     * @throws  NOT_FOUND if the entry to be deleted is not in the database (for a non-forced operation)
     * @throws  INTERNAL_ERROR if the delete failed due to a database error (such as I/O failure)
     * @throws  VERSION_MISMATCH if the existing entry's version does not match the one specified
     */
    inline void deleteEntry(const com::seagate::kinetic::proto::Command_KeyValue& params) {
        m_objectStore->batchedDeleteEntry(m_batchDescriptor, params);
    }

    /**
     * Executes all the requests that were batched together, committing them to the object store,
     * and performing the operation atomically.  Currently, the persistence option is not specified,
     * so we will be cautious and use the sync option.
     *
     * @throws  INTERNAL_ERROR if the operation failed due to a database error (such as I/O failure)
     */
    inline void commit() {
        m_objectStore->batchCommit(m_batchDescriptor);
    }

private:
    /*
     * Private Data Members
     */
    LevelDbObjectStore* const   m_objectStore;      //!< Level DB object store to perform batch operation on
    leveldb::WriteBatch         m_batchDescriptor;  //!< Level DB batch descriptor
};

#endif
