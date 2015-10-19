#pragma once

#include <ctime>
#include <iostream>
#include <sstream>
#include <string>

#include "logger.hpp"

class DefaultLogger : public Logger
{
public:
    void log(std::string message);

    void log(time_t timestamp, std::string message);

    std::string getTimestampString(time_t timestamp);
};
