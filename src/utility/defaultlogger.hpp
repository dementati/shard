#pragma once

#include <ctime>
#include <iostream>
#include <sstream>
#include <string>

#include "../core/object.hpp"
#include "logger.hpp"

enum class Severity
{
    DEBUG,
    INFO,
    WARN,
    ERROR
};

class DefaultLogger : public Logger
{
private:
    const Object &unit;
    
    void log(const Severity &severity, const std::string &message) const;

public:
    DefaultLogger(const Object &unit);

    void debug(const std::string &message) const;

    void info(const std::string &message) const;

    void warn(const std::string &message) const;

    void error(const std::string &message) const;

    void log(const Severity &severity, const time_t timestamp, const std::string &message) const;

    const std::string getTimestampString(const time_t timestamp) const;

    static std::string severityToString(const Severity &severity);
};
