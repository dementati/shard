#pragma once

#include <cassert>
#include <string>

#include "../Job.hpp"

// LCOV_EXCL_START
class Idle : public Job
{
public:
    virtual void execute(double dt);

    virtual bool hasSucceeded();
};
// LCOV_EXCL_STOP
