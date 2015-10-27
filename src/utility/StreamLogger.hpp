#pragma once

#include <cassert>
#include <ctime>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>

#include "../core/Object.hpp"
#include "Logger.hpp"

// LCOV_EXCL_START
enum class Severity
{
    DEBUG,
    INFO,
    WARN,
    ERROR
};

class StreamLogger : public Logger
{
private:
    const Object &mUnit;

    std::ostream &mLogStream;
    
    void log(const Severity &severity, const std::string &message) const;

public:
    StreamLogger(const Object &unit);

    StreamLogger(const Object &unit, std::ostream &logStream);

    void debug(const std::string &message) const;

    void info(const std::string &message) const;

    void warn(const std::string &message) const;

    void error(const std::string &message) const;

    void log(const Severity &severity, const time_t timestamp, const std::string &message) const;

    const std::string getTimestampString(const time_t timestamp) const;

    static std::string severityToString(const Severity &severity);
};
// LCOV_EXCL_STOP
