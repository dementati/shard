#pragma once

#include <string>

class Logger
{
public:
    virtual void log(std::string message) = 0;
};
