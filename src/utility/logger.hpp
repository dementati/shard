#pragma once

#include <string>

class Logger
{
public:
    virtual void log(const std::string message) const = 0;
};
