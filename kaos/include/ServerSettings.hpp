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
 * Contains the user specified settings for the server.
 */
class ServerSettings {

public:

    /*
     * Constructor
     */
    ServerSettings();
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
    inline bool locked() const {return m_locked;}
    inline std::string lockPin() {return m_lockPin;}
    inline std::string erasePin() {return m_erasePin;}
    inline AccessControlMap accessControlMap() {return m_accessControlMap;}
    inline void setClusterVersion(int64_t clusterVersion) {m_clusterVersion = clusterVersion;}
    inline void setLocked(bool locked) {m_locked = locked;}
    inline void setLockPin(std::string lockPin) {m_lockPin.assign(lockPin);}
    inline void setErasePin(std::string erasePin) {m_erasePin.assign(erasePin);}

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
    bool                m_locked;               //!< Indicates if object store is locked
    std::string         m_lockPin;              //!< Personal ID Number to lock/unlock object store
    std::string         m_erasePin;             //!< Personal ID Number to erase object store
    AccessControlMap    m_accessControlMap;     //!< Access Control map (for fast look-up)

    DISALLOW_COPY_AND_ASSIGN(ServerSettings);
};

#endif
