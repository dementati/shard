#pragma once

#include <ctime>
#include <iostream>
#include <sstream>
#include <string>

#include "../core/object.hpp"
#include "logger.hpp"

class DefaultLogger : public Logger
{
    const Object &unit;

public:
    DefaultLogger(const Object &unit);

    void log(const std::string message) const;

    void log(const time_t timestamp, const std::string &message) const;

    const std::string getTimestampString(const time_t timestamp) const;
};
