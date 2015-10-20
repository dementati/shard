#pragma once

#include <string>

#include "../utility/Logger.hpp"

class Object
{
public:
    virtual const Logger& logger() const = 0;

    virtual const std::string unitName() const = 0; 
};
