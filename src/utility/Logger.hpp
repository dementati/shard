#pragma once

#include <string>

enum class Severity
{
    DEBUG = 0,
    INFO = 1,
    WARN = 2,
    ERROR = 3
};

// LCOV_EXCL_START
class Logger
{
public:
    virtual ~Logger() {};

    virtual void debug(const std::string &message) const = 0;

    virtual void info(const std::string &message) const = 0;

    virtual void warn(const std::string &message) const = 0;

    virtual void error(const std::string &message) const = 0;
};
// LCOV_EXCL_STOP
