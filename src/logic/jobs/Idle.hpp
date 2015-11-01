#pragma once

#include <string>

#include "../../utility/Assert.hpp"
#include "../Job.hpp"

// LCOV_EXCL_START
class Idle : public Job
{
public:
    virtual void execute(unsigned int dt);
};
// LCOV_EXCL_STOP
