#pragma once

#include <string>

#include "../utility/Logger.hpp"

class Object
{
public:
    virtual const std::string unitName() const = 0; 
};
