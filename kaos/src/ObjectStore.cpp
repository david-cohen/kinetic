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

/*
 * Include Files
 */
#include <stdint.h>
#include <unistd.h>
#include <list>
#include <string>
#include <memory>
#include "leveldb/cache.h"
#include "leveldb/slice.h"
#include "leveldb/comparator.h"
#include "leveldb/write_batch.h"
#include "leveldb/filter_policy.h"
#include "Logger.hpp"
#include "Entry.pb.hpp"
#include "ObjectStore.hpp"
#include "GlobalConfig.hpp"
#include "MessageException.hpp"

/*
 * Used Namespaces
 */
using std::string;
using std::unique_ptr;
using com::seagate::kinetic::proto::Command_KeyValue;
using com::seagate::kinetic::proto::Command_Status_StatusCode_NOT_FOUND;
using com::seagate::kinetic::proto::Command_Status_StatusCode_INTERNAL_ERROR;
using com::seagate::kinetic::proto::Command_Status_StatusCode_VERSION_MISMATCH;
using com::seagate::kinetic::proto::Command_Synchronization_FLUSH;
using com::seagate::kinetic::proto::Command_Synchronization_WRITEBACK;

/*
 * Constants
 */
static leveldb::WriteOptions asyncWriteOptions;
static leveldb::WriteOptions syncWriteOptions;
static leveldb::ReadOptions defaultReadOptions;
static leveldb::Options databaseOptions;

/**
 * Initializes the object store.
 */
ObjectStore::ObjectStore() {
    syncWriteOptions.sync = true;
    asyncWriteOptions.sync = false;
}

/*
 * Tears down the object store.
 */
ObjectStore::~ObjectStore() {
    close();
}

/**
 * Opens the database in the specified directory.
 *
 * @return  true if the database was opened successfully
 */
bool ObjectStore::open() {

    syncWriteOptions.sync = true;
    asyncWriteOptions.sync = false;

    std::unique_lock<std::recursive_mutex> scopedLock(m_mutex);

    defaultReadOptions.verify_checksums = false;
    defaultReadOptions.fill_cache = true;
    databaseOptions.create_if_missing = true;
    databaseOptions.max_open_files = 256;
    databaseOptions.block_cache = leveldb::NewLRUCache(globalConfig.objectStoreCacheSize());
    databaseOptions.compression = globalConfig.objectStoreCompressionEnabled() ? leveldb::kSnappyCompression : leveldb::kNoCompression;

    leveldb::Status status = leveldb::DB::Open(databaseOptions, globalConfig.databaseDirectory(), &m_database);
    if (!status.ok())
        LOG(ERROR) << "Failed to open database, status: " << status.ToString() << std::endl;

    return status.ok();
}

/*
 * Closes the database (if it was open).
 */
void ObjectStore::close() {

    std::unique_lock<std::recursive_mutex> scopedLock(m_mutex);

    if (m_database != nullptr) {
        delete m_database;
        m_database = nullptr;
    }
}

/**
 * Erases the contents of the database.  This causes the database to temporarily be inaccessible
 * (because it's closes and then opened).
 */
void ObjectStore::erase() {

    std::unique_lock<std::recursive_mutex> scopedLock(m_mutex);

    close();
    DestroyDB(globalConfig.databaseDirectory(), databaseOptions);
    open();
}

/**
 * Flushes all the database data that's in memory to persistent media.
 */
void ObjectStore::flush() {

    std::unique_lock<std::recursive_mutex> scopedLock(m_mutex);
    /*
     * Level DB doesn't have a flush command, so we have to perform a write to force a sync.  Since
     * we don't want to over-write the user's data, we will write a entry whose key is larger that
     * the maximum sized key that a user can make.  To be cautious, check if an entry with the flush
     * get is in the database.  If it's not, write it and delete it in one batch command.  If it
     * exists, don't remove it.  Delete it and re-write it in one batch command.
     */
    string serializedEntryData;
    leveldb::Status status = m_database->Get(defaultReadOptions, globalConfig.flushDataKey(), &serializedEntryData);
    leveldb::WriteBatch batch;

    /*
     * Flush key was not found so put and delete it in one batch command.
     */
    if (!status.ok()) {
        leveldb::Slice emptyData;
        batch.Put(globalConfig.flushDataKey(), emptyData);
        batch.Delete(globalConfig.flushDataKey());
    }

    /*
     * Flush key found.  This should never happen, but if it does, don't remove the data.  So delete
     * it and put in back in one batch command.
     */
    else {
        leveldb::Slice slicedData(serializedEntryData);
        batch.Delete(globalConfig.flushDataKey());
        batch.Put(globalConfig.flushDataKey(), slicedData);
    }

    /*
     * Perform the batch command using the sync option.  Then, flush memory.
     */
    status = m_database->Write(syncWriteOptions, &batch);
    sync();
}

/**
 * Optimizes the media by compacting the underlying storage.  It causes deleted and overwritten
 * versions to be discarded and the data is rearranged to reduce the cost of operations needed to
 * access the data.
 */
void ObjectStore::optimizeMedia() {

    std::unique_lock<std::recursive_mutex> scopedLock(m_mutex);

    /*
     * The parameters passed in indicate the starting and ending keys.  However, passing in null
     * pointers causes the entire database to be compacted.
     */
    m_database->CompactRange(nullptr, nullptr);
}

/**
 * Attempts to put the specified entry in the database.  A database entry consists of a key, value,
 * version, tag (a hash of the value), and an algorithm (the algorithm used to create the hash).
 * A regular put operation where the database already has an entry with same key as the one about to
 * be put requires the version of the existing entry to be specified.  If the versions don't match,
 * the operation fails.  However, a "force" parameter can be specified which eliminates the version
 * check and will always put the new entry.  A persistence option is also specified which indicates
 * if the operation be performed in write-back, write-through, or write-through followed by a flush.
 *
 * @param   params  The entry's metadata, persistence option, and if the put is to be "forced"
 * @param   value   The value of the entry to be put in the database
 *
 * @throws  VERSION_MISMATCH if the existing entry's version does not match the one specified
 * @throws  INTERNAL_ERROR if the put failed due to a database error (such as I/O failure)
 */
void ObjectStore::putEntry(const Command_KeyValue& params, const string& value) {

    std::unique_lock<std::recursive_mutex> scopedLock(m_mutex);
    /*
     * If the request is not "forced", then if the database already has an entry with the same key,
     * then the specified version must match the version of the existing entry.  If there is not an
     * existing entry, then the specified version must be empty.
     */
    if (!params.force()) {
        string serializedEntryData;
        leveldb::Status status = m_database->Get(defaultReadOptions, params.key(), &serializedEntryData);

        if (status.ok()) {
            unique_ptr<kaos::Entry> entry(new kaos::Entry());
            entry->ParseFromString(serializedEntryData);
            if (entry->version() != params.dbversion())
                throw MessageException(Command_Status_StatusCode_VERSION_MISMATCH, "Incorrect version");
        }
        else if (!params.dbversion().empty()) {
            throw MessageException(Command_Status_StatusCode_VERSION_MISMATCH, "No existing entry");
        }
    }

    /*
     * Save the specified value and metadata into a database entry structure, serialize the data,
     * and write it to the database.  Destage all the data in memory to the media if "flush" is
     * specified.
     */
    unique_ptr<kaos::Entry> entry(new kaos::Entry());
    entry->set_key(params.key());
    entry->set_value(value);
    entry->set_version(params.newversion());
    entry->set_tag(params.tag());
    entry->set_algorithm(params.algorithm());

    string serializedData;
    entry->SerializeToString(&serializedData);
    leveldb::Status status = m_database->Put(getWriteOptions(params.synchronization()), params.key(), serializedData);

    if (!status.ok())
        throw MessageException(Command_Status_StatusCode_INTERNAL_ERROR, "Database error: " + status.ToString());

    if (params.synchronization() == Command_Synchronization_FLUSH)
        sync();
}

/**
 * Adds a put request to a "batch", where all the requests in the batch will be performed by the
 * database atomically. A database entry consists of a key, value, version, tag (a hash of the
 * value), and an algorithm (the algorithm used to create the hash). A regular put operation where
 * the database already has an entry with same key as the one about to be put requires the version
 * of the existing entry to be specified. If the versions don't match, the operation fails. However,
 * a "force" parameter can be specified which eliminates the version check and will always put the
 * new entry.  The persistence option is not specified for an individual operation in a batch.  The
 * entire batch operation has a single persistence option.
 *
 * @param   batch   The descriptor for a batched operation
 * @param   params  The entry's metadata and if the put is to be "forced"
 * @param   value   The value of the entry to be put in the database
 *
 * @throws  VERSION_MISMATCH if the existing entry's version does not match the one specified
 */
void ObjectStore::batchedPutEntry(BatchDescriptor& batch, const Command_KeyValue& params, const string& value) {

    std::unique_lock<std::recursive_mutex> scopedLock(m_mutex);
    /*
     * If the request is not "forced", then if the database already has an entry with the same key,
     * then the specified version must match the version of the existing entry.  If there is not an
     * existing entry, then the specified version must be empty.
     */
    if (!params.force()) {
        string serializedEntryData;
        leveldb::Status status = m_database->Get(defaultReadOptions, params.key(), &serializedEntryData);

        if (status.ok()) {
            unique_ptr<kaos::Entry> entry(new kaos::Entry());
            entry->ParseFromString(serializedEntryData);
            if (entry->version() != params.dbversion())
                throw MessageException(Command_Status_StatusCode_VERSION_MISMATCH, "Incorrect version");
        }
        else if (!params.dbversion().empty()) {
            throw MessageException(Command_Status_StatusCode_VERSION_MISMATCH, "No existing entry");
        }
    }

    /*
     * Save the specified value and metadata into a database entry structure, serialize the data,
     * and save the entry to the batch descriptor (to be processed later when the batch is
     * committed).
     */
    unique_ptr<kaos::Entry> entry(new kaos::Entry());
    entry->set_key(params.key());
    entry->set_value(value);
    entry->set_version(params.newversion());
    entry->set_tag(params.tag());
    entry->set_algorithm(params.algorithm());

    string serializedData;
    entry->SerializeToString(&serializedData);
    batch.Put(params.key(), serializedData);
}

/**
 * Attempts to delete the entry in the database with the specified.  A regular delete operation
 * requires the version of the entry to be deleted to be specified.  If the versions don't match,
 * the operation fails. However, a "force" parameter can be specified which eliminates the version
 * check and will always delete the entry.  If the entry for the specified key doesn't exist, a
 * normal delete will fail, but a "forced" delete will not.  A persistence option is also specified
 * which indicates if the operation be performed in write-back, write-through, or write-through
 * followed by a flush.
 *
 * @param   params  The key of the entry, persistence option, and if the delete is to be "forced"
 *
 * @throws  NOT_FOUND if the entry to be deleted is not in the database (for a non-forced operation)
 * @throws  INTERNAL_ERROR if the delete failed due to a database error (such as I/O failure)
 * @throws  VERSION_MISMATCH if the existing entry's version does not match the one specified
 */
void ObjectStore::deleteEntry(const Command_KeyValue& params) {

    const string& key = params.key();
    std::unique_lock<std::recursive_mutex> scopedLock(m_mutex);
    /*
     * If the request is not "forced", then the specified version must match the version of the
     * entry to be deleted.  If they don't match or the entry is not in the database, fail the
     * operation.
     */
    if (!params.force()) {
        string serializedEntryData;
        leveldb::Status status = m_database->Get(defaultReadOptions, key, &serializedEntryData);

        if (!status.ok()) {
            if (status.IsNotFound())
                throw MessageException(Command_Status_StatusCode_NOT_FOUND, "Entry not found");
            else
                throw MessageException(Command_Status_StatusCode_INTERNAL_ERROR, "Database error: " + status.ToString());
        }

        unique_ptr<kaos::Entry> entry(new kaos::Entry());
        entry->ParseFromString(serializedEntryData);
        if (entry->version() != params.dbversion())
            throw MessageException(Command_Status_StatusCode_VERSION_MISMATCH, "Incorrect version");
    }

    /*
     * Delete the entry in the database.  Destage all the data in memory to the media if "flush" is
     * specified.
     */
    leveldb::Status status = m_database->Delete(getWriteOptions(params.synchronization()), key);

    if (!status.ok())
        throw MessageException(Command_Status_StatusCode_INTERNAL_ERROR, "Database error: " + status.ToString());

    if (params.synchronization() == Command_Synchronization_FLUSH)
        sync();
}

/**
 * Adds a delete request to a "batch", where all the requests in the batch will be performed by the
 * database atomically.  A regular delete operation requires the version of the entry to be deleted
 * to be specified.  If the versions don't match, the operation fails. However, a "force" parameter
 * can be specified which eliminates the version check and will always delete the entry.  If the
 * entry for the specified key doesn't exist, a normal delete will fail, but a "forced" delete will
 * not.  The persistence option is not specified for an individual operation in a batch.  The entire
 * batch operation has a single persistence option.
 *
 * @param   params  The key of the entry, persistence option, and if the delete is to be "forced"
 *
 * @throws  NOT_FOUND if the entry to be deleted is not in the database (for a non-forced operation)
 * @throws  INTERNAL_ERROR if the delete failed due to a database error (such as I/O failure)
 * @throws  VERSION_MISMATCH if the existing entry's version does not match the one specified
 */
void ObjectStore::batchedDeleteEntry(BatchDescriptor& batch, const Command_KeyValue& params) {

    const string& key = params.key();
    std::unique_lock<std::recursive_mutex> scopedLock(m_mutex);

    /*
     * If the request is not "forced", then the specified version must match the version of the
     * entry to be deleted.  If they don't match or the entry is not in the database, fail the
     * operation.
     */
    if (!params.force()) {
        string serializedEntryData;
        leveldb::Status status = m_database->Get(defaultReadOptions, key, &serializedEntryData);

        if (!status.ok()) {
            if (status.IsNotFound())
                throw MessageException(Command_Status_StatusCode_NOT_FOUND, "Entry not found");
            else
                throw MessageException(Command_Status_StatusCode_INTERNAL_ERROR, "Database error: " + status.ToString());
        }

        unique_ptr<kaos::Entry> entry(new kaos::Entry());
        entry->ParseFromString(serializedEntryData);
        if (entry->version() != params.dbversion())
            throw MessageException(Command_Status_StatusCode_VERSION_MISMATCH, "Incorrect version");
    }

    /*
     * Add the key of the entry to be deleted in the batch descriptor (to be processed later when
     * the batch is committed).
     */
    batch.Delete(key);
}

/**
 * Executes all the operations that were "batched" together, committing them to the database, and
 * performing the operation atomically.  Currently, the persistence option is not specified, so we
 * will be cautious and use the sync option.
 *
 * @param   batch   Contains all the batched operations to perform
 *
 * @throws  INTERNAL_ERROR if the operation failed due to a database error (such as I/O failure)
 */
void ObjectStore::batchCommit(BatchDescriptor& batch) {

    std::unique_lock<std::recursive_mutex> scopedLock(m_mutex);

    leveldb::Status status = m_database->Write(syncWriteOptions, &batch);
    if (!status.ok())
        throw MessageException(Command_Status_StatusCode_INTERNAL_ERROR, "Database error: " + status.ToString());
}

/**
 * Attempts to retrieve the entry with the specified key from the database.  If there is no entry
 * with the specified key, the operation will fail.  However, if the entry is in the database, its
 * value and metadata will be returned.  The metadata consists of a version, tag (a hash of the
 * value), and an algorithm (the algorithm used to create the hash).
 *
 * @param   key             The key of the requested entry
 * @param   returnValue     The value of the requested entry
 * @param   returnMetadata  The metadata of the requested entry (version, tag, and algorithm)
 *
 * @throws  NOT_FOUND if the entry was not found in the database
 * @throws  INTERNAL_ERROR if the get failed due to a database error (such as I/O failure)
 */
void ObjectStore::getEntry(const string& key, string& returnValue, Command_KeyValue* returnMetadata) {

    std::unique_lock<std::recursive_mutex> scopedLock(m_mutex);

    /*
     * Read the database, failing the operation if the entry could not be found or the database
     * encountered an error while performing the get (such as an I/O error).
     */
    string serializedEntryData;
    leveldb::Status status = m_database->Get(defaultReadOptions, key, &serializedEntryData);

    if (!status.ok()) {
        if (status.IsNotFound())
            throw MessageException(Command_Status_StatusCode_NOT_FOUND, "Entry not found");
        else
            throw MessageException(Command_Status_StatusCode_INTERNAL_ERROR, "Database error: " + status.ToString());
    }

    /*
     * Deserialize the entry data and save its value and metadata in the specified structures.
     */
    unique_ptr<kaos::Entry> entry(new kaos::Entry());
    entry->ParseFromString(serializedEntryData);
    returnValue.assign(entry->value());
    returnMetadata->set_key(key);
    returnMetadata->set_dbversion(entry->version());
    returnMetadata->set_tag(entry->tag());
    returnMetadata->set_algorithm(entry->algorithm());
}

/**
 * Attempts to retrieve the metadata of the entry with the specified key from the database.  If
 * there is no entry with the specified key, the operation will fail.  However, if the entry is in
 * the database, the requested metadata will be returned.  The request can be for all the metadata
 * (the version, tag, and algorithm) or just the version.
 *
 * @param   key             The key of the requested entry
 * @param   returnMetadata  The returned metadata
 *
 * @throws  NOT_FOUND if the entry was not found in the database
 * @throws  INTERNAL_ERROR if the get failed due to a database error (such as I/O failure)
 */
void ObjectStore::getEntryMetadata(const string& key, bool versionOnly, Command_KeyValue* returnMetadata) {

    std::unique_lock<std::recursive_mutex> scopedLock(m_mutex);

    /*
     * Read the database, failing the operation if the entry could not be found or the database
     * encountered an error while performing the get (such as an I/O error).
     */
    string serializedEntryData;
    leveldb::Status status = m_database->Get(defaultReadOptions, key, &serializedEntryData);

    if (!status.ok()) {
        if (status.IsNotFound())
            throw MessageException(Command_Status_StatusCode_NOT_FOUND, "Entry not found");
        else
            throw MessageException(Command_Status_StatusCode_INTERNAL_ERROR, "Database error: " + status.ToString());
    }

    /*
     * Deserialize the entry data and save the requested metadata in the specified structures.
     */
    unique_ptr<kaos::Entry> entry(new kaos::Entry());
    entry->ParseFromString(serializedEntryData);
    returnMetadata->set_key(key);
    returnMetadata->set_dbversion(entry->version());
    if (!versionOnly) {
        returnMetadata->set_tag(entry->tag());
        returnMetadata->set_algorithm(entry->algorithm());
    }
}

/**
 * Attempts to retrieve the entry that following the entry with the specified key from the database.
 * If there is no entry after the one with the specified key, the operation will fail.  However, if
 * there is one, its value and metadata will be returned.  The metadata consists of a version, tag
 * (a hash of the value), and an algorithm (the algorithm used to create the hash).
 *
 * @param   key             The key of the entry proceeding the requested entry
 * @param   returnValue     The value of the requested entry
 * @param   returnMetadata  The metadata of the requested entry (version, tag, and algorithm)
 *
 * @throws  NOT_FOUND if the entry was not found in the database
 */
void ObjectStore::getNextEntry(const string& key, string& returnValue, Command_KeyValue* returnMetadata) {

    std::unique_lock<std::recursive_mutex> scopedLock(m_mutex);

    /*
     * The seek function will cause the iterator to have one of three positions depending on the
     * contents of the database.  First, it can be positioned at the entry with the requested key if
     * that entry is in the database.  Second, it can be position at the entry in the database that
     * is next after the requested key if the entry with the requested key is not in the database.
     * Third, the iterator's position can be invalid if there are no entries in the database on or
     * after the entry with the requested key.
     */
    leveldb::Iterator* iterator = m_database->NewIterator(defaultReadOptions);
    iterator->Seek(key);

    /*
     * If the iterator is positioned at the entry with the requested key, advanced it to the next
     * entry. However, if the iterator is positioned at a valid entry that does not have the request
     * key, then that's the entry we want (so no need to advance the iterator).
     */
    if (iterator->Valid() && (iterator->key().ToString() == key))
        iterator->Next();

    if (!iterator->Valid())
        throw MessageException(Command_Status_StatusCode_NOT_FOUND, "Entry not found");

    /*
     * Deserialize the entry data and save its value and metadata in the specified structures.
     */
    unique_ptr<kaos::Entry> entry(new kaos::Entry());
    entry->ParseFromString(iterator->value().ToString());
    returnValue.assign(entry->value());
    returnMetadata->set_key(iterator->key().ToString());
    returnMetadata->set_dbversion(entry->version());
    returnMetadata->set_tag(entry->tag());
    returnMetadata->set_algorithm(entry->algorithm());
}

/**
 * Attempts to retrieve the entry that precedes the entry with the specified key from the database.
 * If there is no entry before the one with the specified key, the operation will fail.  However, if
 * there is one, its value and metadata will be returned.  The metadata consists of a version, tag
 * (a hash of the value), and an algorithm (the algorithm used to create the hash).
 *
 * @param   key             The key of the entry that follows the requested entry
 * @param   returnValue     The value of the requested entry
 * @param   returnMetadata  The metadata of the requested entry (version, tag, and algorithm)
 *
 * @throws  NOT_FOUND if the entry was not found in the database
 */
void ObjectStore::getPreviousEntry(const string& key, string& returnValue, Command_KeyValue* returnMetadata) {

    std::unique_lock<std::recursive_mutex> scopedLock(m_mutex);

    /*
     * The seek function will cause the iterator to have one of three positions depending on the
     * contents of the database.  First, it can be positioned at the entry with the requested key if
     * that entry is in the database.  Second, it can be position at the entry in the database that
     * is next after the requested key if the entry with the requested key is not in the database.
     * Third, the iterator's position can be invalid if there are no entries in the database on or
     * after the entry with the requested key.
     */
    leveldb::Iterator* iterator = m_database->NewIterator(defaultReadOptions);
    iterator->Seek(key);

    /*
     * If there are no entries on or after the requested key, position the iterator at the last
     * entry in the database because, if it exists, it is the entry that precedes the entry with the
     * requested key.
     */
    if (!iterator->Valid())
        iterator->SeekToLast();

    /*
     * If the iterator is positioned at or past the entry of the requested key, move it to the
     * previous entry.
     */
    else if (iterator->Valid() && (iterator->key().ToString() >= key))
        iterator->Prev();

    if (!iterator->Valid())
        throw MessageException(Command_Status_StatusCode_NOT_FOUND, "Entry not found");

    /*
     * Deserialize the entry data and save its value and metadata in the specified structures.
     */
    unique_ptr<kaos::Entry> entry(new kaos::Entry());
    entry->ParseFromString(iterator->value().ToString());
    returnValue.assign(entry->value());
    returnMetadata->set_key(iterator->key().ToString());
    returnMetadata->set_dbversion(entry->version());
    returnMetadata->set_tag(entry->tag());
    returnMetadata->set_algorithm(entry->algorithm());
}

/**
 * Attempts to retrieve the keys (in ascending order) of all the entries bounded by the specified
 * start and end key. The parameters specify if the start and end keys are to be included as well as
 * a maximum number keys that can be returned.  A user maybe be restricted on what keys they can
 * access, if those keys are bounded by the start and end keys, they will not be returned to the
 * user and the operation will terminate when the first one is encountered.
 *
 * @param  params           Defines the start key (and if it is to be included), the end key
 *                          (and if it is to be included), and maximum number of keys to return
 * @param  accessControl    Describe the keys the user has access to
 * @param  returnData       Where the list or keys to be returned are saved
 */
void ObjectStore::getKeyRange(const com::seagate::kinetic::proto::Command_Range& params, AccessControlPtr& accessControl,
                              com::seagate::kinetic::proto::Command_Range* returnData) {

    std::unique_lock<std::recursive_mutex> scopedLock(m_mutex);

    /*
     * The seek function will cause the iterator to have one of three positions depending on the
     * contents of the database.  First, it can be positioned at the entry with the requested key if
     * that entry is in the database.  Second, it can be position at the entry in the database that
     * is next after the requested key if the entry with the requested key is not in the database.
     * Third, the iterator's position can be invalid if there are no entries in the database on or
     * after the entry with the requested key.
     */
    leveldb::Iterator* iterator = m_database->NewIterator(defaultReadOptions);
    iterator->Seek(params.startkey());

    /*
     * If the iterator is positioned at the start key and the start key is not to be included,
     * advanced to the next entry.
     */
    if (!params.startkeyinclusive() && iterator->Valid() && (iterator->key().ToString() == params.startkey()))
        iterator->Next();

    /*
     * Add keys to the list following these conditions:
     *     the key is less than the end key
     *     the key is equals to the end key and the end key is to be included
     *     the user has permission to access the specific key
     *     the number of keys added are less then the maximum allowed
     */
    for (int32_t keyCount = 0; iterator->Valid() && (keyCount < params.maxreturned()); iterator->Next()) {
        string key = iterator->key().ToString();
        if (accessControl->permissionToGetRange(key)) {
            if ((key < params.endkey()) || ((params.endkeyinclusive()) && (key == params.endkey()))) {
                returnData->add_keys(key);
                keyCount++;
            }
            else
                break;
        }

        /*
         * Once a key has been added to the response, stop gathering keys after the first key that
         * the user doesn't have access to is encountered.
         */
        else if (keyCount > 0)
            break;
    }
    delete iterator;
}

/**
 * Attempts to retrieve the keys (in descending order) of all the entries bounded by the specified
 * start and end key. The parameters specify if the start and end keys are to be included as well as
 * a maximum number keys that can be returned.  A user maybe be restricted on what keys they can
 * access, if those keys are bounded by the start and end keys, they will not be returned to the
 * user and the operation will terminate when the first one is encountered.
 *
 * @param  params           Defines the start key (and if it is to be included), the end key
 *                          (and if it is to be included), and maximum number of keys to return
 * @param  accessControl    Describe the keys the user has access to
 * @param  returnData       Where the list or keys to be returned are saved
 */
void ObjectStore::getKeyRangeReversed(const com::seagate::kinetic::proto::Command_Range& params, AccessControlPtr& accessControl,
                                      com::seagate::kinetic::proto::Command_Range* returnData) {

    std::unique_lock<std::recursive_mutex> scopedLock(m_mutex);

    /*
     * The seek function will cause the iterator to have one of three positions depending on the
     * contents of the database.  First, it can be positioned at the entry with the requested key if
     * that entry is in the database.  Second, it can be position at the entry in the database that
     * is next after the requested key if the entry with the requested key is not in the database.
     * Third, the iterator's position can be invalid if there are no entries in the database on or
     * after the entry with the requested key.
     */
    leveldb::Iterator* iterator = m_database->NewIterator(defaultReadOptions);
    iterator->Seek(params.endkey());

    /*
     * If there are no entries on or after the requested key, position the iterator at the last key
     * in the database because it might be in the requested range.
     */
    if (!iterator->Valid())
        iterator->SeekToLast();

    /*
     * If the iterator is positioned at an entry past the end key, move it to the previous entry.
     * If the iterator is positioned at the entry with the last key and it is not to be included,
     * move the iterator to the previous entry.
     */
    else if (iterator->Valid() && ((iterator->key().ToString() > params.endkey())
                                   || (!params.endkeyinclusive() && (iterator->key().ToString() == params.endkey())))) {
        iterator->Prev();
    }

    /*
     * Add keys to the list following these conditions:
     *     the key is greater than start end key
     *     the key is equals to the start key and the start key is to be included
     *     the user has permission to access the specific key
     *     the number of keys added are less then the maximum allowed
     */
    for (int32_t keyCount = 0; iterator->Valid() && (keyCount < params.maxreturned()); iterator->Prev()) {
        string key = iterator->key().ToString();
        if (accessControl->permissionToGetRange(key)) {
            if ((key > params.startkey()) || ((params.startkeyinclusive()) && (key == params.startkey()))) {
                returnData->add_keys(key);
                keyCount++;
            }
            else
                break;
        }

        /*
         * Once a key has been added to the response, stop gathering keys after the first key that
         * the user doesn't have access to is encountered.
         */
        else if (keyCount > 0)
            break;
    }
    delete iterator;
}

/**
 * Converts the Kinetic persistence option into a level DB write option.
 */
inline leveldb::WriteOptions& ObjectStore::getWriteOptions(com::seagate::kinetic::proto::Command_Synchronization option) {
    return option == Command_Synchronization_WRITEBACK ? asyncWriteOptions : syncWriteOptions;
}


