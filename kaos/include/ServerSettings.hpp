/*
 * Copyright (c) 2014-2016 Western Digital Technologies, Inc. <copyrightagent@wdc.com>
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
#ifndef SERVER_SETTINGS_HPP
#define SERVER_SETTINGS_HPP

/*
 * Include Files
 */
#include <stdint.h>
#include <list>
#include <string>
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
    explicit ServerSettings(const std::string& filename);

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
    inline int64_t clusterVersion() const {return m_clusterVersion;}
    inline bool locked() const {return m_locked;}
    inline std::string lockPin() const {return m_lockPin;}
    inline std::string erasePin() const {return m_erasePin;}
    inline AccessControlMap accessControlMap() const {return m_accessControlMap;}
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
    const std::string   m_filename;             //!< Name of the file containing the settings
    int64_t             m_clusterVersion;       //!< Cluster version of object store
    bool                m_locked;               //!< Indicates if object store is locked
    std::string         m_lockPin;              //!< Personal ID Number to lock/unlock object store
    std::string         m_erasePin;             //!< Personal ID Number to erase object store
    AccessControlMap    m_accessControlMap;     //!< Access Control map (for fast look-up)
};

#endif
