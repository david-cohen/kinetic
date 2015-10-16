/*
    Copyright (c) [2014 - 2015] Western Digital Technologies, Inc. All rights reserved.
*/

#pragma once
#ifndef SYSTEM_CONTROL_HPP
#define SYSTEM_CONTROL_HPP

/*
    Include Files
*/

#include <stdint.h>
#include <string>
#include "Common.hpp"

class SystemControl {

public:

    SystemControl() : m_locked(false), m_debugEnabled(false) {}
    bool locked() { return m_locked;}
    void setLocked(bool locked) {m_locked = locked;}
    bool debugEnabled() { return m_debugEnabled;}
    void setDebugEnabled(bool debugEnabled) {m_debugEnabled = debugEnabled;}

private:

    bool m_locked;
    bool m_debugEnabled;

    DISALLOW_COPY_AND_ASSIGN(SystemControl);
};

extern SystemControl systemControl;

#endif
