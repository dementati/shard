#pragma once

#include <string>

#include "../utility/Logger.hpp"

// LCOV_EXCL_START
class Object
{
public:
    virtual ~Object() {}

    virtual const std::string unitName() const = 0;
};
// LCOV_EXCL_STOP
