/*
 * Copyright (c) [2014 - 2016] Western Digital Technologies, Inc. All rights reserved.
 */
#pragma once
#ifndef MESSAGE_STATISTICS_HPP
#define MESSAGE_STATISTICS_HPP

/*
 * Include Files
 */
#include <map>
#include <mutex>
#include "Kinetic.pb.hpp"
#include "KineticMessage.hpp"

/**
 * Message Statistics
 *
 * The keeper of message statistics, which maintains for each message type the number of time the
 * message type has been processed and the number of bytes transferred to process it (for both the
 * request and response messages).  This information is reported through a Kinetic get log request.
 */
class MessageStatistics {

    /**
     * Private Stats Record (plain old data)
     *
     * Maintains the count for number of times a message type has been processed and the number of
     * bytes transferred for the request and response messages.  There is one stats object for every
     * message type.
     */
    struct Stats {
        Stats() : count(0), byteCount(0) {}
        uint32_t    count;         //!< Number of times message has been processed
        uint64_t    byteCount;     //!< Number of bytes received and send in processing of message
    };

    typedef std::map<com::seagate::kinetic::proto::Command_MessageType, Stats*> StatsMap;

public:

    /**
     * Message Statistics Constructor
     *
     * Initializes the tables that maintains the stats for each message type.
     */
    MessageStatistics()
        : m_statsTable({
        {com::seagate::kinetic::proto::Command_MessageType_PUT,           {new Stats()}},
        {com::seagate::kinetic::proto::Command_MessageType_GET,           {new Stats()}},
        {com::seagate::kinetic::proto::Command_MessageType_GETNEXT,       {new Stats()}},
        {com::seagate::kinetic::proto::Command_MessageType_GETPREVIOUS,   {new Stats()}},
        {com::seagate::kinetic::proto::Command_MessageType_GETVERSION,    {new Stats()}},
        {com::seagate::kinetic::proto::Command_MessageType_GETKEYRANGE,   {new Stats()}},
        {com::seagate::kinetic::proto::Command_MessageType_GETLOG,        {new Stats()}},
        {com::seagate::kinetic::proto::Command_MessageType_DELETE,        {new Stats()}},
        {com::seagate::kinetic::proto::Command_MessageType_SETUP,         {new Stats()}},
        {com::seagate::kinetic::proto::Command_MessageType_SECURITY,      {new Stats()}},
        {com::seagate::kinetic::proto::Command_MessageType_PEER2PEERPUSH, {new Stats()}},
        {com::seagate::kinetic::proto::Command_MessageType_NOOP,          {new Stats()}},
        {com::seagate::kinetic::proto::Command_MessageType_FLUSHALLDATA,  {new Stats()}},
        {com::seagate::kinetic::proto::Command_MessageType_PINOP,         {new Stats()}},
        {com::seagate::kinetic::proto::Command_MessageType_MEDIASCAN,     {new Stats()}},
        {com::seagate::kinetic::proto::Command_MessageType_MEDIAOPTIMIZE, {new Stats()}},
        {com::seagate::kinetic::proto::Command_MessageType_START_BATCH,   {new Stats()}},
        {com::seagate::kinetic::proto::Command_MessageType_END_BATCH,     {new Stats()}},
        {com::seagate::kinetic::proto::Command_MessageType_ABORT_BATCH,   {new Stats()}}
    }) {}

    /**
     * Update
     *
     * @param requestMessage    a processed request message
     * @param responseMessage   the associated response
     *
     * Updates the number times this operation has been performed and the number of bytes
     * transferred for its request and response.  Some operations have no response (such as a
     * batched put).  In those cases, there is still a response message, but it is unused and will
     * have a message size of zero.
     */
    void update(KineticMessagePtr& requestMessage, KineticMessagePtr& responseMessage) {

        std::unique_lock<std::mutex> scopedLock(m_mutex);
        StatsMap::iterator iter = m_statsTable.find(requestMessage->command()->header().messagetype());
        if (iter != m_statsTable.end()) {
            Stats* messageStats = iter->second;
            messageStats->byteCount += requestMessage->totalSize() + responseMessage->totalSize();
            messageStats->count++;
        }
    }

    /**
     * Get
     *
     * @param response  pointer to where the statistics are to be set
     *
     * Sets the statistic values for all the message types.
     */
    void get(com::seagate::kinetic::proto::Command_GetLog* response) {

        std::unique_lock<std::mutex> scopedLock(m_mutex);
        for (auto& messageStats : m_statsTable) {
            com::seagate::kinetic::proto::Command_GetLog_Statistics* statistics(response->add_statistics());
            statistics->set_messagetype(messageStats.first);
            statistics->set_count(messageStats.second->count);
            statistics->set_bytes(messageStats.second->byteCount);
        }
    }

private:

    /*
     * Private Data Members
     */
    std::mutex  m_mutex;        //!< Mutex to make the class thread safe
    StatsMap    m_statsTable;   //!< Statistics for all message types
};

extern MessageStatistics messageStatistics;

#endif
