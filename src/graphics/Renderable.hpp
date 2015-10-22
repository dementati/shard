#pragma once

#include "../core/Object.hpp"

// LCOV_EXCL_START
class Renderable : public Object
{
public:
    virtual void draw() = 0;
};
// LCOV_EXCL_STOP
