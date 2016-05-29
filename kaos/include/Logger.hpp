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
#ifndef LOGGER_HPP
#define LOGGER_HPP

/*
 * Include Files
 */
#include <stdint.h>
#include <syslog.h>
#include <string>
#include <sstream>
#include <iostream>

/*
 * Event Log Severity Levels
 */
enum LogLevel {
    DEBUG   = LOG_DEBUG,
    INFO    = LOG_INFO,
    WARNING = LOG_WARNING,
    ERROR   = LOG_ERR
};

/*
 * Event Log Facility
 */
enum LogFacility {
    LOCAL0 = LOG_LOCAL0,
    LOCAL1 = LOG_LOCAL1,
    LOCAL2 = LOG_LOCAL2,
    LOCAL3 = LOG_LOCAL3,
    LOCAL4 = LOG_LOCAL4,
    LOCAL5 = LOG_LOCAL5,
    LOCAL6 = LOG_LOCAL6,
    LOCAL7 = LOG_LOCAL7
};

/*
 * Manages the event log.
 */
class LogControl {
public:
    /**
     * Sets log control to its default state.
     */
    LogControl()
        : m_logLevel(WARNING), m_standardOutEnabled(false) {
    }

    /**
     * Opens the event log and sets up its behavior.
     *
     * @param   facility    Identifies the event so that it can be directed to the correct logfile
     * @param   logLevel    Indicates which events will be logged based on severity level
     */
    void open(LogFacility facility, LogLevel logLevel) {
        m_logLevel = logLevel;
        ::openlog(nullptr, 0, facility);
    }

    /**
     * Closes the event log.
     */
    ~LogControl() {
        ::closelog();
    }

    /**
     * Indicates the selected logging level.
     *
     * @return  The selected log level
     */

    inline LogLevel logLevel() const {return m_logLevel;}
    /**
     * Indicates if outputting events to standard-out is enabled.
     *
     * @return  true if outputting to standard-out is enabled.
     */
    inline bool standardOutEnabled() const {return m_standardOutEnabled;}

    /**
     * Sets the logging level
     *
     * @param logLevel  The log level
     */
    inline void setLogLevel(LogLevel logLevel) {m_logLevel = logLevel;}

    /**
     * Enable or disable events being output to standard out.
     *
     * @param   enabled     True if the events are to be output to standard-out
     */
    inline void setStandardOutEnabled(bool enabled) {m_standardOutEnabled = enabled;}

private:
    LogLevel    m_logLevel;             //!< Indicates the highest level to be logged where ERROR < WARNING < INFO < DEBUG
    bool        m_standardOutEnabled;   //!< If true, the events are to be output to standard-out
};

extern LogControl logControl;

namespace _InternalUseOnly_ {

/*
 * Describes a single event log entry.
 */
class LogEntry {
public:
    /**
     * Creates an event log entry and sets the message with its severity level.  If debug logging is
     * enabled, it also logs where the event was logged from (filename, function name and line number).
     *
     * @param  level       Severity level of event
     * @param  filename    Name of the file the event was logged from
     * @param  lineNumber  The line number that the event was logged from
     * @param  function    The function that the event was logged from
     */
    LogEntry(LogLevel level, std::string filename, int32_t lineNumber, const std::string& function)
        : m_level(level), m_message(), m_location() {
        captureLevel(level);
        if (logControl.logLevel() == DEBUG)
            captureLocation(filename, lineNumber, function);
    }

    /**
     * Causes the event to be recorded in the syslog if the level of the event is allowed to be
     * logged.
    */
    ~LogEntry() {
        if (m_level <= logControl.logLevel()) {
            m_message << m_location.str();
            syslog(m_level, "%s", m_message.str().c_str());
            if (logControl.standardOutEnabled())
                std::cout << m_message.str() << std::endl;
        }
    }

    /**
     * Returns the event log message.
     *
     * @return a reference to the events message
     */
    std::stringstream& message() {
        return (m_message);
    }

private:
    /**
     * Records the filename, line number, and function of where the event was logged.
     *
     * @param  filename    Name of the file the event was logged from
     * @param  lineNumber  The line number that the event was logged from
     * @param  function    The function that the event was logged from
     */
    inline void captureLocation(std::string filename, int32_t lineNumber, const std::string& function) {
        /*
         * Remove the path from the filename.
         */
        std::size_t position = filename.rfind('/');
        if (position != std::string::npos)
            filename = filename.substr(position + 1);
        m_location << ", file=" << filename << ", line=" << lineNumber << ", function=" << function;
    }

    /**
     * Records the severity level of the event to its message.
     *
     * @param  level   Severity level of event
     */
    void captureLevel(LogLevel level) {
        std::string levelString;
        if (level == LOG_ERR)
            levelString = "ERROR";
        else if (level == LOG_WARNING)
            levelString = "WARNING";
        else if (level == LOG_INFO)
            levelString = "INFO";
        else if (level == LOG_DEBUG)
            levelString = "DEBUG";
        m_message << levelString << ": ";
    }

    LogLevel            m_level;        //!< Severity level of event
    std::stringstream   m_message;      //!< Contents of event's message
    std::stringstream   m_location;     //!< File, line, and function of event
};

}  // namespace _InternalUseOnly_

/*
 * Macro to record an entry in the event log (imitates the GLog API)
 */
#define LOG(level) _InternalUseOnly_::LogEntry(level, __FILE__, __LINE__, __FUNCTION__).message()

#endif
