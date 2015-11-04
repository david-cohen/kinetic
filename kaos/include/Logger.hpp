/*
    Copyright (c) [2014 - 2015] Western Digital Technologies, Inc. All rights reserved.
*/

#pragma once
#ifndef LOGGER_HPP
#define LOGGER_HPP

/*
    Include Files
*/

#include <stdint.h>
#include <syslog.h>
#include <string>
#include <sstream>

/*
    Event Log Severity Levels
*/

enum LogLevel {
    DEBUG   = LOG_DEBUG,
    INFO    = LOG_INFO,
    WARNING = LOG_WARNING,
    ERROR   = LOG_ERR
};

/*
    Event Log Facility
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

namespace _InternalUseOnly_ {

/**
    Log Entry

    Describes a single event log entry.
*/

class LogEntry {
public:

    /**
        LogEntry Constructor

        @param  level       Severity level of event
        @param  filename    Name of the file the event was logged from
        @param  lineNumber  The line number that the event was logged from

        Creates an event log entry and sets the message with its severity level and the filename and
        line number of where the event was logged from.
    */

    LogEntry(LogLevel level, const char* filename, int32_t lineNumber, std::string function) : m_level(level), m_message(), m_location() {
        captureLevel(level);
        captureLocation(filename, lineNumber, function);
    }

    /**
        LogEntry Constructor

        @param  level       Severity level of event

        Creates an event log entry and sets the message with its severity level.
    */

    explicit LogEntry(LogLevel level) : m_level(level), m_message(), m_location() {
        captureLevel(level);
    }

    /**
        LogEntry Destructor

        Causes the event to be recorded in the syslog and, optionally, output to standard out.
    */

    ~LogEntry() {
        m_message << m_location.str();
        syslog(m_level, "%s", m_message.str().c_str());
    }

    /**
        Message

        @return a reference to the events message
    */

    std::stringstream& message() {
        return (m_message);
    }

private:

    /**
        Capture Location

        @param  filename    Name of the file the event was logged from
        @param  lineNumber  The line number that the event was logged from
        @param  function    The function that the event was logged from

        Records the filename, line number, and function of where the event was logged.
    */

    inline void captureLocation(const char* filename, int32_t lineNumber, std::string function) {
        m_location << ", file=" << filename << ", line=" << lineNumber << ", function=" << function;
    }

    /**
        Capture Level

        @param  level   Severity level of event

        Records the severity level of the event to its message.
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

/**
    Log Control

    Used to open and close the syslog.
*/

class LogControl {
public:
    explicit LogControl(const char* name, LogFacility facility, bool logToStandardError) {
        ::openlog(name, logToStandardError ? LOG_PERROR : 0, facility);
    }
    ~LogControl() {
        ::closelog();
    }
};

}  // namespace _InternalUseOnly_

/*
    Macro to setup logging
*/

#define LOG_INIT(name, facility, logToStandardError) _InternalUseOnly_::LogControl _logControl_(name, facility, logToStandardError)

/*
    Macro to record an entry in the log (imitates the GLog API)
*/

#ifdef LOG_EVENT_LOCATION
#define LOG(level) _InternalUseOnly_::LogEntry(level, __FILE__, __LINE__, __FUNCTION__).message()
#define LOG_WITHOUT_LOCATION(level) _InternalUseOnly_::LogEntry(level).message()
#else
#define LOG(level) _InternalUseOnly_::LogEntry(level).message()
#define LOG_WITHOUT_LOCATION(level) _InternalUseOnly_::LogEntry(level).message()
#endif

#endif
