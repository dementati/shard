#pragma once

#include <string>
#include <vector>

#include "../../utility/Assert.hpp"
#include "../../utility/LoggerFactory.hpp"
#include "../jobs/FindWater.hpp"
#include "../jobs/Idle.hpp"
#include "../Job.hpp"
#include "../Need.hpp"

// LCOV_EXCL_START
class Thirst : public Need
{
    LoggerPtr mLogger;
    World &mWorld;
    Entity &mOwner;

public:
    Thirst(World &world, Entity &owner);

    virtual void execute(unsigned int dt);

    virtual unsigned int getIntensity();

    virtual std::unique_ptr<Job> getJob();
};
// LCOV_EXCL_STOP
