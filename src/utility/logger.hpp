#pragma once

#include <string>

class Logger
{
public:
    virtual void debug(const std::string &message) const = 0;

    virtual void info(const std::string &message) const = 0;

    virtual void warn(const std::string &message) const = 0;

    virtual void error(const std::string &message) const = 0;
};
