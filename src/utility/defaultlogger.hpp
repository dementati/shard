#pragma once

#include <iostream>
#include <string>

#include "logger.hpp"

class DefaultLogger : public Logger
{
public:
    void log(std::string message);
};
