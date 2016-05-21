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
#ifndef SERVER_HPP
#define SERVER_HPP

/*
 * Include Files
 */
#include <stdint.h>
#include <string>
#include "Common.hpp"
#include "ObjectStore.hpp"
#include "ServerSettings.hpp"
#include "MessageStatistics.hpp"
#include "CommunicationsManager.hpp"

class Server {

public:

    Server(std::string pidFileName, bool foreground);
    ServerSettings& settings() {return m_settings;}
    ObjectStore& objectStore() {return m_objectStore;}
    MessageStatistics& messageStatistics() {return m_messageStatistics;}
    int32_t run();

private:

    std::string             m_pidFileName;
    bool                    m_foreground;
    CommunicationsManager   m_communicationsManager;
    ServerSettings          m_settings;
    MessageStatistics       m_messageStatistics;
    ObjectStore             m_objectStore;

    DISALLOW_COPY_AND_ASSIGN(Server);
};

#endif
