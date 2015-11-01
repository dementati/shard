#pragma once

#include <string>
#include <vector>

#include "../../utility/Assert.hpp"
#include "../jobs/FindWater.hpp"
#include "../jobs/Idle.hpp"
#include "../Job.hpp"
#include "../Need.hpp"

// LCOV_EXCL_START
class Thirst : public Need
{
    World &mWorld;
    Entity &mOwner;

public:
    Thirst(World &world, Entity &owner);

    virtual int getIntensity();

    virtual void execute(unsigned int dt);
};
// LCOV_EXCL_STOP
