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
#include "Common.hpp"
#include "Kinetic.pb.hpp"
#include "KineticMessage.hpp"

/*
 * Message Statistics Class
 */
class MessageStatistics {

    class Stats {
    public:
        Stats() : count(0), byteCount(0) {}
        uint32_t    count;         //!< Number of times message has been processed
        uint64_t    byteCount;     //!< Number of bytes received and send in processing of message
    };

    typedef std::map<com::seagate::kinetic::proto::Command_MessageType, Stats*> StatsMap;

public:

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
        {com::seagate::kinetic::proto::Command_MessageType_MEDIAOPTIMIZE, {new Stats()}}
    }) {}

    void update(KineticMessagePtr& requestMessage, KineticMessagePtr& responseMessage) {

        std::unique_lock<std::mutex> scopedLock(m_mutex);
        StatsMap::iterator iter = m_statsTable.find(requestMessage->command()->header().messagetype());
        if (iter != m_statsTable.end()) {
            Stats* messageStats = iter->second;
            messageStats->byteCount += requestMessage->totalSize() + responseMessage->totalSize();
            messageStats->count++;
        }
    }

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

    std::mutex  m_mutex;        //!< Mutex to make class thread safe
    StatsMap    m_statsTable;   //!< Message statistics for each message type
};

extern MessageStatistics messageStatistics;

#endif
