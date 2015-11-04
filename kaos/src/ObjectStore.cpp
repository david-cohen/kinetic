/*
    Copyright (c) [2014 - 2015] Western Digital Technologies, Inc. All rights reserved.
*/

/*
    Include Files
*/

#include <stdint.h>
#include <unistd.h>
#include <list>
#include <string>
#include <memory>
#include "leveldb/cache.h"
#include "leveldb/slice.h"
#include "leveldb/write_batch.h"
#include "Entry.pb.hpp"
#include "ObjectStore.hpp"
#include "SystemConfig.hpp"

/*
    Used Namespaces
*/

using std::string;
using std::unique_ptr;

/*
    Constants
*/

#define CHECK_ALL

static leveldb::WriteOptions asyncWriteOptions;
static leveldb::WriteOptions syncWriteOptions;
static leveldb::WriteOptions flushWriteOptions;
static leveldb::ReadOptions defaultReadOptions;

inline leveldb::WriteOptions getWriteOptions(PersistOption option) {
    return option == PersistOption::Command_Synchronization_WRITEBACK ? asyncWriteOptions : syncWriteOptions;
}

inline bool validPersistOption(PersistOption option) {
    return ((static_cast<int32_t>(option) >= static_cast<int32_t>(PersistOption::Command_Synchronization_WRITETHROUGH))
            && (static_cast<int32_t>(option) <= static_cast<int32_t>(PersistOption::Command_Synchronization_FLUSH)));
}

/**
    ObjectStore Constructor

    @param  databaseDirectory   directory where the database resides
*/

ObjectStore::ObjectStore(std::string databaseDirectory)
    : m_databaseDirectory(databaseDirectory) {

    syncWriteOptions.sync = true;
    asyncWriteOptions.sync = false;
}

/**
    ObjectStore Destructor
*/

ObjectStore::~ObjectStore() {
    delete m_database;
}

/**
    Open

    @return the completion status of the operations (success of failure)
*/

ReturnStatus
ObjectStore::open() {

    asyncWriteOptions.sync = false;
    syncWriteOptions.sync = true;
    flushWriteOptions.sync = true;
    defaultReadOptions.verify_checksums = false;
    defaultReadOptions.fill_cache = true;

    leveldb::Options options;
    options.create_if_missing = true;
    options.block_cache = leveldb::NewLRUCache(64 * 1048576);
    options.compression = systemConfig.objectStoreCompressionEnabled() ? leveldb::kSnappyCompression : leveldb::kNoCompression;
    leveldb::Status status = leveldb::DB::Open(options, m_databaseDirectory, &m_database);
    return status.ok() ? ReturnStatus::SUCCESS : ReturnStatus::FAILURE;
}

/**
    Erase

    @return the completion status of the operations (success of failure)
*/

ReturnStatus
ObjectStore::erase() {

    delete m_database;
    leveldb::Options options;
    DestroyDB(m_databaseDirectory, options);
    open();
    return ReturnStatus::SUCCESS;
}

/**
    Flush

    @return the completion status of the operations (success or the error status)
*/

ReturnStatus
ObjectStore::flush() {

    /*
        Make a key that will not match any entry in the database (by making the key size larger than
        the that supported by the Kinetic API and setting a unique ID).
    */

    string serializedEntryData;
    leveldb::Status status = m_database->Get(defaultReadOptions, systemConfig.flushDataKey(), &serializedEntryData);
    leveldb::WriteBatch batch;

    /*
        No entry for key. perform no op
    */

    if (!status.ok()) {
        leveldb::Slice emptyData;
        batch.Put(systemConfig.flushDataKey(), emptyData);
        batch.Delete(systemConfig.flushDataKey());
    }

    /*
        entry found, put back after delete - is the delete necessary?
    */

    else {
        leveldb::Slice slicedData(serializedEntryData);
        batch.Delete(systemConfig.flushDataKey());
        batch.Put(systemConfig.flushDataKey(), slicedData);
    }

    /*
        do batch operation with sync option.
    */

    status = m_database->Write(syncWriteOptions, &batch);
    sync();
    return status.ok() ? ReturnStatus::SUCCESS : ReturnStatus::FAILURE;
}

/**
    Put

    @param  key             the key of the entry to be put in the object store
    @param  value           the value of the entry to be put in the object store
    @param  newVersion      the new version of the entry to be put in the object store
    @param  oldVersion      the (optional) old version of the entry in the object store
    @param  tag             the (optional) tag of the entry to be put in the object store
    @param  algorithm       the (optional) algorithm of the entry to be put in the object store
    @param  persistOption   indicates how the change to the object store is to be persisted
                            (SYNC - before returning status
                             ASYNC - after returning status
                             FLUSH - before return status and after all data destaged)

    @return the completion status of the operations (success or the error status)
*/

ReturnStatus
ObjectStore::put(const string& key, const string& value, const string& newVersion, const string& oldVersion,
                 const string& tag, Algorithm algorithm, PersistOption persistOption) {

    /*
        Ensure that the parameters are valid.  If not, fail the operation.
    */

#ifdef CHECK_ALL
    if (key.size() < systemConfig.minKeySize())
        return ReturnStatus::KEY_SIZE_TOO_SMALL;

    if (key.size() > systemConfig.maxKeySize())
        return ReturnStatus::KEY_SIZE_TOO_LARGE;

    if (value.size() > systemConfig.maxValueSize())
        return ReturnStatus::VALUE_SIZE_TOO_LARGE;

    if (newVersion.size() > systemConfig.maxVersionSize())
        return ReturnStatus::VERSION_SIZE_TOO_LARGE;

    if (tag.size() > systemConfig.maxTagSize())
        return ReturnStatus::TAG_SIZE_TOO_LARGE;

    if (!validPersistOption(persistOption))
        return ReturnStatus::INVALID_PERSIST_OPTION;
#endif

    /*
        Validating the version includes checking if an entry with the specified key is already in
        the object store.  If it is, the specified version must be the same.
    */

    string serializedEntryData;
    leveldb::Status status = m_database->Get(defaultReadOptions, key, &serializedEntryData);

    if (status.ok()) {
        unique_ptr<kaos::Entry> entry(new kaos::Entry());
        entry->ParseFromString(serializedEntryData);
        if (entry->version() != oldVersion) {
            return ReturnStatus::VERSION_MISMATCH;
        }
    }
    else if (!oldVersion.empty()) {
        return ReturnStatus::VERSION_MISMATCH;
    }

    /*
        First, create the metadata for the entry set set the write options, then put the entry in
        the object store.
    */

    unique_ptr<kaos::Entry> entry(new kaos::Entry());
    entry->set_key(key);
    entry->set_value(value);
    entry->set_version(newVersion);
    entry->set_tag(tag);
    entry->set_algorithm(algorithm);

    string serializedData;
    entry->SerializeToString(&serializedData);
    status = m_database->Put(getWriteOptions(persistOption), key, serializedData);

    if (status.ok() && (persistOption == PersistOption::Command_Synchronization_FLUSH))
        sync();

    return status.ok() ? ReturnStatus::SUCCESS : ReturnStatus::FAILURE;
}

/**
    Put Forced

    @param  key             the key of the entry to be put in the object store
    @param  value           the value of the entry to be put in the object store
    @param  version         the (optional) version of the entry to be put in the object store
    @param  tag             the (optional) tag of the entry to be put in the object store
    @param  algorithm       the (optional) algorithm of the entry to be put in the object store
    @param  persistOption   indicates how the change to the object store is to be persisted
                            (SYNC - before returning status
                             ASYNC - after returning status
                             FLUSH - before return status and after all data destaged)

    @return the completion status of the operations (success or the error status)
*/

ReturnStatus
ObjectStore::putForced(const string& key, const string& value, const string& version, const string& tag, Algorithm algorithm, PersistOption persistOption) {

    /*
        Ensure that the parameters are valid.  If not, fail the operation.
    */

#ifdef CHECK_ALL
    if (key.size() < systemConfig.minKeySize())
        return ReturnStatus::KEY_SIZE_TOO_SMALL;

    if (key.size() > systemConfig.maxKeySize())
        return ReturnStatus::KEY_SIZE_TOO_LARGE;

    if (value.size() > systemConfig.maxValueSize())
        return ReturnStatus::VALUE_SIZE_TOO_LARGE;

    if (version.size() > systemConfig.maxVersionSize())
        return ReturnStatus::VERSION_SIZE_TOO_LARGE;

    if (tag.size() > systemConfig.maxTagSize())
        return ReturnStatus::TAG_SIZE_TOO_LARGE;

    if (!validPersistOption(persistOption))
        return ReturnStatus::INVALID_PERSIST_OPTION;
#endif

    unique_ptr<kaos::Entry> entry(new kaos::Entry());
    entry->set_key(key);
    entry->set_value(value);
    entry->set_version(version);
    entry->set_tag(tag);
    entry->set_algorithm(algorithm);

    string serializedData;
    entry->SerializeToString(&serializedData);
    leveldb::Status status = m_database->Put(getWriteOptions(persistOption), key, serializedData);

    if (status.ok() && (persistOption == PersistOption::Command_Synchronization_FLUSH))
        sync();

    return status.ok() ? ReturnStatus::SUCCESS : ReturnStatus::FAILURE;
}

/**
    Get

    @param  key             the key of the entry in the object store to get
    @param  value           the value of the entry in the object store
    @param  version         the version of the entry in the object store
    @param  tag             the tag of the entry in the object store
    @param  algorithm       the algorithm of the entry in the object store

    @return the completion status of the operations (success or the error status)
*/

ReturnStatus
ObjectStore::get(const string& key, string& value, string& version, string& tag, Algorithm& algorithm) {

#ifdef CHECK_ALL
    if (key.size() < systemConfig.minKeySize())
        return ReturnStatus::KEY_SIZE_TOO_SMALL;

    if (key.size() > systemConfig.maxKeySize())
        return ReturnStatus::KEY_SIZE_TOO_LARGE;
#endif

    string serializedEntryData;
    leveldb::Status status = m_database->Get(defaultReadOptions, key, &serializedEntryData);

    if (!status.ok())
        return ReturnStatus::ENTRY_NOT_FOUND;

    unique_ptr<kaos::Entry> entry(new kaos::Entry());
    entry->ParseFromString(serializedEntryData);
    value.assign(entry->value());
    version.assign(entry->version());
    tag.assign(entry->tag());
    algorithm = entry->algorithm();

    return ReturnStatus::SUCCESS;
}

/**
    Get Next

    @param  key             the key of the entry before the one in the object store to get
    @param  nextKey         the key of the next entry in the object store to get
    @param  nextValue       the value of the next entry in the object store
    @param  nextVersion     the version of the next entry in the object store
    @param  nextTag         the tag of the next entry in the object store
    @param  nextAlgorithm   the algorithm of the next entry in the object store

    @return the completion status of the operations (success or the error status)
*/

ReturnStatus
ObjectStore::getNext(const string& key, string& nextKey, string& nextValue, string& nextVersion, string& nextTag, Algorithm& nextAlgorithm) {

#ifdef CHECK_ALL
    if (key.size() < systemConfig.minKeySize())
        return ReturnStatus::KEY_SIZE_TOO_SMALL;

    if (key.size() > systemConfig.maxKeySize())
        return ReturnStatus::KEY_SIZE_TOO_LARGE;
#endif

    /*
        The seek function will cause the iterator to be positioned at the entry with the requested
        key, or at the entry in the database that is next after the requested key (if the entry with
        the requested key is not in the database), or the iterator will be invalid (because
        there are no entries in the database on or after the requested key).
    */

    leveldb::Iterator* iterator = m_database->NewIterator(defaultReadOptions);
    iterator->Seek(key);

    /*
        If the iterator is positioned at the entry of the requested key, advanced to the next entry.
        If the iterator is at the entry past the request key, then that's the entry we want (so no
        need to advance the iterator).
    */

    if (iterator->Valid() && (iterator->key().ToString() == key))
        iterator->Next();

    if (!iterator->Valid())
        return ReturnStatus::ENTRY_NOT_FOUND;

    unique_ptr<kaos::Entry> entry(new kaos::Entry());
    entry->ParseFromString(iterator->value().ToString());
    nextKey.assign(iterator->key().ToString());
    nextValue.assign(entry->value());
    nextVersion.assign(entry->version());
    nextTag.assign(entry->tag());
    nextAlgorithm = entry->algorithm();

    return ReturnStatus::SUCCESS;
}

/**
    Get Previous

    @param  key                 the key of the entry after the one in the object store to get
    @param  previousKey         the key of the previous entry in the object store to get
    @param  previousValue       the value of the previous entry in the object store
    @param  previousVersion     the version of the previous entry in the object store
    @param  previousTag         the tag of the previous entry in the object store
    @param  previousAlgorithm   the algorithm of the previous entry in the object store

    @return the completion status of the operations (success or the error status)
*/

ReturnStatus
ObjectStore::getPrevious(const string& key, string& previousKey, string& previousValue, string& previousVersion, string& previousTag, Algorithm& previousAlgorithm) {

#ifdef CHECK_ALL
    if (key.size() < systemConfig.minKeySize())
        return ReturnStatus::KEY_SIZE_TOO_SMALL;

    if (key.size() > systemConfig.maxKeySize())
        return ReturnStatus::KEY_SIZE_TOO_LARGE;
#endif

    /*
        The seek function will cause the iterator to be positioned at the entry with the requested
        key, or at the entry in the database that is next after the requested key (if the entry with
        the requested key is not in the database), or the iterator will be invalid (because
        there are no entries in the database on or after the requested key).
    */

    leveldb::Iterator* iterator = m_database->NewIterator(defaultReadOptions);
    iterator->Seek(key);

    /*
        If there are no entries on or after the requested key, position the iterator at the last key
        in the database because it might be in the requested range.
    */

    if (!iterator->Valid())
        iterator->SeekToLast();

    /*
        If the iterator is positioned at or past the entry of the requested key, move it to the
        previous entry.
    */

    else if (iterator->Valid() && (iterator->key().ToString() >= key))
        iterator->Prev();

    if (!iterator->Valid())
        return ReturnStatus::ENTRY_NOT_FOUND;

    unique_ptr<kaos::Entry> entry(new kaos::Entry());
    entry->ParseFromString(iterator->value().ToString());
    previousKey.assign(iterator->key().ToString());
    previousValue.assign(entry->value());
    previousVersion.assign(entry->version());
    previousTag.assign(entry->tag());
    previousAlgorithm = entry->algorithm();

    return ReturnStatus::SUCCESS;
}

/**
    Get Metadata

    @param  key             the key of the entry in the object store to get
    @param  version         the version of the entry in the object store
    @param  tag             the tag of the entry in the object store
    @param  algorithm       the algorithm of the entry in the object store

    @return the completion status of the operations (success or the error status)
*/

ReturnStatus
ObjectStore::getMetadata(const string& key, string& version, string& tag, Algorithm& algorithm) {

#ifdef CHECK_ALL
    if (key.size() < systemConfig.minKeySize())
        return ReturnStatus::KEY_SIZE_TOO_SMALL;

    if (key.size() > systemConfig.maxKeySize())
        return ReturnStatus::KEY_SIZE_TOO_LARGE;
#endif

    string serializedEntryData;
    leveldb::Status status = m_database->Get(defaultReadOptions, key, &serializedEntryData);

    if (!status.ok())
        return ReturnStatus::ENTRY_NOT_FOUND;

    unique_ptr<kaos::Entry> entry(new kaos::Entry());
    entry->ParseFromString(serializedEntryData);
    version.assign(entry->version());
    tag.assign(entry->tag());
    algorithm = entry->algorithm();

    return ReturnStatus::SUCCESS;
}

/**
    Get Key Range

    @param  startKey            the start key in the specified key range
    @param  startKeyInclusive   true if the start key is inclusive
    @param  endKey              the end key in the specified key range
    @param  endKeyInclusive     true if the end key is inclusive
    @param  maxKeys             the maximum number of keys to return
    @param  accessControl       access control to be used for this operation

    @return the completion status of the operations (success or the error status)

    Note: A zero byte start key is allowed.
*/

ReturnStatus
ObjectStore::getKeyRange(const string& startKey, bool startKeyInclusive, const string& endKey, bool endKeyInclusive,
                         int32_t maxKeys, std::list<string>& keyList, AccessControlPtr& accessControl) {

    if (startKey.size() > systemConfig.maxKeySize())
        return ReturnStatus::START_KEY_SIZE_TOO_LARGE;

    if (endKey.size() < systemConfig.minKeySize())
        return ReturnStatus::END_KEY_SIZE_TOO_SMALL;

    if (endKey.size() > systemConfig.maxKeySize())
        return ReturnStatus::END_KEY_SIZE_TOO_LARGE;

    if (((size_t)maxKeys) > systemConfig.maxKeyRangeCount())
        return ReturnStatus::MAX_KEYS_RETURNED_COUNT_TOO_LARGE;

    /*
        The seek function will cause the iterator to be positioned at the entry with the requested
        key, or at the entry in the database that is next after the requested key (if the entry with
        the requested key is not in the database), or the iterator will be invalid (because
        there are no entries in the database on or after the requested key).
    */

    leveldb::Iterator* iterator = m_database->NewIterator(defaultReadOptions);
    iterator->Seek(startKey);

    /*
        If the iterator is positioned at the start key and the start key is not to be included,
        advanced to the next entry.
    */

    if (!startKeyInclusive && iterator->Valid() && (iterator->key().ToString() == startKey))
        iterator->Next();

    /*
        Add keys to the list as long as they are less than the end key or equal to the end key if it
        is to be included and the number of keys don't exceed the specified maximum keys to return.
    */

    for (int32_t keyCount = 0; iterator->Valid() && (keyCount < maxKeys); iterator->Next()) {
        string key = iterator->key().ToString();
        if (accessControl->permissionToGetRange(key)) {
            if ((key < endKey) || ((endKeyInclusive) && (key == endKey))) {
                keyList.push_back(key);
                keyCount++;
            }
            else
                break;
        }

        /*
            If keys were already found, stop at the first miss.
        */

        else if (keyCount > 0)
            break;
    }

    delete iterator;
    return ReturnStatus::SUCCESS;
}

/**
    Get Key Range Reversed

    @param  startKey            the start key in the specified key range
    @param  startKeyInclusive   true if the start key is inclusive
    @param  endKey              the end key in the specified key range
    @param  endKeyInclusive     true if the end key is inclusive
    @param  maxKeys             the maximum number of keys to return
    @param  accessControl       access control to be used for this operation

    @return the completion status of the operations (success or the error status)

    Note: A zero byte start key is allowed.
*/

ReturnStatus
ObjectStore::getKeyRangeReversed(const string& startKey, bool startKeyInclusive, const string& endKey, bool endKeyInclusive,
                                 int32_t maxKeys, std::list<string>& keyList, AccessControlPtr& accessControl) {

    if (startKey.size() > systemConfig.maxKeySize())
        return ReturnStatus::START_KEY_SIZE_TOO_LARGE;

    if (endKey.size() < systemConfig.minKeySize())
        return ReturnStatus::END_KEY_SIZE_TOO_SMALL;

    if (endKey.size() > systemConfig.maxKeySize())
        return ReturnStatus::END_KEY_SIZE_TOO_LARGE;

    if (((size_t)maxKeys) > systemConfig.maxKeyRangeCount())
        return ReturnStatus::MAX_KEYS_RETURNED_COUNT_TOO_LARGE;

    /*
        The seek function will cause the iterator to be positioned at the entry with the requested
        key, or at the entry in the database that is next after the requested key (if the entry with
        the requested key is not in the database), or the iterator will be invalid (because
        there are no entries in the database on or after the requested key).
    */

    leveldb::Iterator* iterator = m_database->NewIterator(defaultReadOptions);
    iterator->Seek(endKey);

    /*
        If there are no entries on or after the requested key, position the iterator at the last key
        in the database because it might be in the requested range.
    */

    if (!iterator->Valid())
        iterator->SeekToLast();

    /*
        If the iterator is positioned at an entry past the end key, move it to the previous entry.
        If the iterator is positioned at the entry with the last key and it is not to be included,
        move the iterator to the previous entry.
    */

    else if (iterator->Valid() && ((iterator->key().ToString() > endKey) || (!endKeyInclusive && (iterator->key().ToString() == endKey))))
        iterator->Prev();

    /*
        Add keys to the list as long as they are greater than the start key or equal to the start
        key if it is to be included and the number of keys don't exceed the specified maximum keys
        to return.
    */

    for (int32_t keyCount = 0; iterator->Valid() && (keyCount < maxKeys); iterator->Prev()) {
        string key = iterator->key().ToString();

        if (accessControl->permissionToGetRange(key)) {
            if ((key > startKey) || ((startKeyInclusive) && (key == startKey))) {
                keyList.push_back(key);
                keyCount++;
            }
            else
                break;
        }

        /*
            If keys were already found, stop at the first miss.
        */

        else if (keyCount > 0)
            break;
    }

    delete iterator;
    return ReturnStatus::SUCCESS;
}

/**
    Delete Versioned

    @param  key             the key of the entry to delete
    @param  version         the version of the entry to delete
    @param  persistOption   indicates how the change to the object store is to be persisted
                            (SYNC - before returning status
                             ASYNC - after returning status
                             FLUSH - before return status and after all data destaged)

    @return the completion status of the operations (success or the error status)

    Delete the entry that is associated with the key specified.
*/

ReturnStatus
ObjectStore::deleteVersioned(const string& key, const string& version, PersistOption persistOption) {

    /*
        Ensure that the parameters are valid.  If not, fail the operation.
    */

#ifdef CHECK_ALL
    if (key.size() < systemConfig.minKeySize())
        return ReturnStatus::KEY_SIZE_TOO_SMALL;

    if (key.size() > systemConfig.maxKeySize())
        return ReturnStatus::KEY_SIZE_TOO_LARGE;

    if (version.size() > systemConfig.maxVersionSize())
        return ReturnStatus::VERSION_SIZE_TOO_LARGE;

    if (!validPersistOption(persistOption))
        return ReturnStatus::INVALID_PERSIST_OPTION;
#endif

    /*
        Validating the version includes checking if an entry with the specified key is already in
        the object store.  If it is, the specified version must be the same.
    */

    string serializedEntryData;
    leveldb::Status status = m_database->Get(defaultReadOptions, key, &serializedEntryData);

    if (!status.ok())
        return ReturnStatus::ENTRY_NOT_FOUND;

    if (status.ok()) {
        unique_ptr<kaos::Entry> entry(new kaos::Entry());
        entry->ParseFromString(serializedEntryData);
        if (entry->has_version() && (entry->version() != version)) {
            return ReturnStatus::VERSION_MISMATCH;
        }
    }

    status = m_database->Delete(getWriteOptions(persistOption), key);

    if (status.ok() && (persistOption == PersistOption::Command_Synchronization_FLUSH))
        sync();

    return status.ok() ? ReturnStatus::SUCCESS : ReturnStatus::FAILURE;
}

/**
    Delete Forced

    @param  key             the key of the entry to delete
    @param  persistOption   indicates how the change to the object store is to be persisted
                            (SYNC - before returning status
                             ASYNC - after returning status
                             FLUSH - before return status and after all data destaged)

    @return the completion status of the operations (success or the error status)

    Delete the entry that is associated with the key specified.
*/

ReturnStatus
ObjectStore::deleteForced(const string& key, PersistOption persistOption) {

    /*
        Ensure that the parameters are valid.  If not, fail the operation.
    */

#ifdef CHECK_ALL
    if (key.size() < systemConfig.minKeySize())
        return ReturnStatus::KEY_SIZE_TOO_SMALL;

    if (key.size() > systemConfig.maxKeySize())
        return ReturnStatus::KEY_SIZE_TOO_LARGE;

    if (!validPersistOption(persistOption))
        return ReturnStatus::INVALID_PERSIST_OPTION;
#endif

    leveldb::Status status = m_database->Delete(getWriteOptions(persistOption), key);

    if (status.ok() && (persistOption == PersistOption::Command_Synchronization_FLUSH))
        sync();

    return status.ok() ? ReturnStatus::SUCCESS : ReturnStatus::FAILURE;
}

/**
    Batch Put

    @param  batch           the batch to add an operation to
    @param  key             the key of the entry to be put in the object store
    @param  value           the value of the entry to be put in the object store
    @param  newVersion      the new version of the entry to be put in the object store
    @param  oldVersion      the (optional) old version of the entry in the object store
    @param  tag             the (optional) tag of the entry to be put in the object store
    @param  algorithm       the (optional) algorithm of the entry to be put in the object store

    @return the status of adding the operation to the batch job
*/

ReturnStatus
ObjectStore::batchPut(BatchDescriptor& batch, const string& key, const string& value, const string& newVersion,
                      const string& oldVersion, const string& tag, Algorithm algorithm) {

    /*
        Ensure that the parameters are valid.  If not, fail the operation.
    */

#ifdef CHECK_ALL
    if (key.size() < systemConfig.minKeySize())
        return ReturnStatus::KEY_SIZE_TOO_SMALL;

    if (key.size() > systemConfig.maxKeySize())
        return ReturnStatus::KEY_SIZE_TOO_LARGE;

    if (value.size() > systemConfig.maxValueSize())
        return ReturnStatus::VALUE_SIZE_TOO_LARGE;

    if (newVersion.size() > systemConfig.maxVersionSize())
        return ReturnStatus::VERSION_SIZE_TOO_LARGE;

    if (tag.size() > systemConfig.maxTagSize())
        return ReturnStatus::TAG_SIZE_TOO_LARGE;

#endif

    /*
        Validating the version includes checking if an entry with the specified key is already in
        the object store.  If it is, the specified version must be the same.
    */

    string serializedEntryData;
    leveldb::Status status = m_database->Get(defaultReadOptions, key, &serializedEntryData);

    if (status.ok()) {
        unique_ptr<kaos::Entry> entry(new kaos::Entry());
        entry->ParseFromString(serializedEntryData);
        if (entry->version() != oldVersion) {
            return ReturnStatus::VERSION_MISMATCH;
        }
    }
    else if (!oldVersion.empty()) {
        return ReturnStatus::VERSION_MISMATCH;
    }

    /*
        First, create the metadata for the entry set set the write options, then put the entry in
        the object store.
    */

    unique_ptr<kaos::Entry> entry(new kaos::Entry());
    entry->set_key(key);
    entry->set_value(value);
    entry->set_version(newVersion);
    entry->set_tag(tag);
    entry->set_algorithm(algorithm);

    string serializedData;
    entry->SerializeToString(&serializedData);
    batch.Put(key, serializedData);
    return ReturnStatus::SUCCESS;
}

/**
    Batch Put Forced

    @param  batch           the batch to add an operation to
    @param  key             the key of the entry to be put in the object store
    @param  value           the value of the entry to be put in the object store
    @param  version         the (optional) version of the entry to be put in the object store
    @param  tag             the (optional) tag of the entry to be put in the object store
    @param  algorithm       the (optional) algorithm of the entry to be put in the object store

    @return the status of adding the operation to the batch job
*/

ReturnStatus
ObjectStore::batchPutForced(BatchDescriptor& batch, const string& key, const string& value,
                            const string& version, const string& tag, Algorithm algorithm) {

    /*
        Ensure that the parameters are valid.  If not, fail the operation.
    */

#ifdef CHECK_ALL
    if (key.size() < systemConfig.minKeySize())
        return ReturnStatus::KEY_SIZE_TOO_SMALL;

    if (key.size() > systemConfig.maxKeySize())
        return ReturnStatus::KEY_SIZE_TOO_LARGE;

    if (value.size() > systemConfig.maxValueSize())
        return ReturnStatus::VALUE_SIZE_TOO_LARGE;

    if (version.size() > systemConfig.maxVersionSize())
        return ReturnStatus::VERSION_SIZE_TOO_LARGE;

    if (tag.size() > systemConfig.maxTagSize())
        return ReturnStatus::TAG_SIZE_TOO_LARGE;
#endif

    unique_ptr<kaos::Entry> entry(new kaos::Entry());
    entry->set_key(key);
    entry->set_value(value);
    entry->set_version(version);
    entry->set_tag(tag);
    entry->set_algorithm(algorithm);

    string serializedData;
    entry->SerializeToString(&serializedData);
    batch.Put(key, serializedData);
    return ReturnStatus::SUCCESS;
}

/**
    Delete

    @param  batch           the batch to add an operation to
    @param  key             the key of the entry to delete
    @param  version         the version of the entry to delete

    @return the status of adding the operation to the batch job

    Batches a delete of the entry that is associated with the key specified.
*/

ReturnStatus
ObjectStore::batchDelete(BatchDescriptor& batch, const string& key, const string& version) {

    /*
        Ensure that the parameters are valid.  If not, fail the operation.
    */

#ifdef CHECK_ALL
    if (key.size() < systemConfig.minKeySize())
        return ReturnStatus::KEY_SIZE_TOO_SMALL;

    if (key.size() > systemConfig.maxKeySize())
        return ReturnStatus::KEY_SIZE_TOO_LARGE;

    if (version.size() > systemConfig.maxVersionSize())
        return ReturnStatus::VERSION_SIZE_TOO_LARGE;
#endif

    /*
        Validating the version includes checking if an entry with the specified key is already in
        the object store.  If it is, the specified version must be the same.
    */

    string serializedEntryData;
    leveldb::Status status = m_database->Get(defaultReadOptions, key, &serializedEntryData);

    if (!status.ok())
        return ReturnStatus::ENTRY_NOT_FOUND;

    if (status.ok()) {
        unique_ptr<kaos::Entry> entry(new kaos::Entry());
        entry->ParseFromString(serializedEntryData);
        if (entry->has_version() && (entry->version() != version)) {
            return ReturnStatus::VERSION_MISMATCH;
        }
    }

    batch.Delete(key);
    return ReturnStatus::SUCCESS;
}

/**
    Batch Delete Forced

    @param  batch           the batch to add an operation to
    @param  key             the key of the entry to delete

    @return the status of adding the operation to the batch job

    Batches a delete of the entry that is associated with the key specified.
*/

ReturnStatus
ObjectStore::batchDeleteForced(BatchDescriptor& batch, const string& key) {

    /*
        Ensure that the parameters are valid.  If not, fail the operation.
    */

#ifdef CHECK_ALL
    if (key.size() < systemConfig.minKeySize())
        return ReturnStatus::KEY_SIZE_TOO_SMALL;

    if (key.size() > systemConfig.maxKeySize())
        return ReturnStatus::KEY_SIZE_TOO_LARGE;
#endif

    batch.Delete(key);
    return ReturnStatus::SUCCESS;
}

/**
    Batch Commit

    @param  batch   contains the batch operations to perform

    @return the status of the commit operation

    Performs all the batched operations commiting them to the database.
*/

ReturnStatus
ObjectStore::batchCommit(BatchDescriptor& batch) {

    leveldb::Status status = m_database->Write(flushWriteOptions, &batch);
    return status.ok() ? ReturnStatus::SUCCESS : ReturnStatus::FAILURE;
}

ReturnStatus
ObjectStore::optimizeMedia() {

    m_database->CompactRange(nullptr, nullptr);
    return ReturnStatus::SUCCESS;
}

