/*
 * Copyright (c) [2014 - 2016] Western Digital Technologies, Inc. All rights reserved.
 */
#pragma once
#ifndef SERVER_SETTINGS_HPP
#define SERVER_SETTINGS_HPP

/*
 * Include Files
 */
#include <stdint.h>
#include <list>
#include <string>
#include "Common.hpp"
#include "AccessControl.hpp"

/**
 * Server Settings
 *
 * Maintains the user controlled settings for the server.
 */
class ServerSettings {

public:

    /*
     * Constructor
     */
    explicit ServerSettings(std::string filename);

    /*
     * Public Member Functions
     */
    void save();
    void setDefaults();
    AccessControlPtr accessControl(int64_t identity);
    void updateAccessControl(std::list<AccessControlPtr> newAccessControlList);

    /*
     * Public Accessors
     */
    inline int64_t clusterVersion() {return m_clusterVersion;}
    inline std::string lockPin() {return m_lockPin;}
    inline std::string erasePin() {return m_erasePin;}
    inline AccessControlMap accessControlMap() {return m_accessControlMap;}
    inline void setClusterVersion(int64_t clusterVersion) {m_clusterVersion = clusterVersion;}
    inline void setErasePin(std::string erasePin) {m_erasePin.assign(erasePin);}
    inline void setLockPin(std::string lockPin) {m_lockPin.assign(lockPin);}

private:

    /*
     * Private Member Functions
     */
    bool load();

    /*
     * Private Data Members
     */
    std::string         m_filename;             //!< Name of the file containing the settings
    int64_t             m_clusterVersion;       //!< Cluster version of object store
    std::string         m_lockPin;              //!< Personal ID Number to lock/unlock drive
    std::string         m_erasePin;             //!< Personal ID Number to erase drive
    AccessControlMap    m_accessControlMap;     //!< Access Control map (for fast look-up)

    DISALLOW_COPY_AND_ASSIGN(ServerSettings);
};

extern ServerSettings serverSettings;

#endif
