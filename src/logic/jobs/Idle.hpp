#pragma once

#include <cassert>

#include "../Job.hpp"

// LCOV_EXCL_START
class Idle : public Job
{
public:
    virtual void execute(double dt);

    virtual bool hasSucceeded();

    const std::string unitName() const;
};
// LCOV_EXCL_STOP
