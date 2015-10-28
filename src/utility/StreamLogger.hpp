#pragma once

#include <cassert>
#include <ctime>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>

#include "DateTime.hpp"
#include "Logger.hpp"

// LCOV_EXCL_START
class StreamLogger : public Logger
{
private:
    const std::string mUnit;

    std::ostream &mLogStream;

    const Severity mMinSeverity;
    
    void log(const Severity &severity, const std::string &message) const;

public:
    //StreamLogger(const std::string unit);

    //StreamLogger(const std::string unit, std::ostream &logStream);

    StreamLogger(const std::string unit, std::ostream &logStream, const Severity minSeverity);

    void debug(const std::string &message) const;

    void info(const std::string &message) const;

    void warn(const std::string &message) const;

    void error(const std::string &message) const;

    void log(const Severity &severity, const time_t timestamp, const std::string &message) const;

    static std::string severityToString(const Severity &severity);
};
// LCOV_EXCL_STOP
