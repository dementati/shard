#pragma once

#include <string>

#include "../../../utility/Assert.hpp"
#include "../../Entity.hpp"
#include "../../Job.hpp"
#include "../../World.hpp"

// LCOV_EXCL_START
class IncreaseThirst : public Job
{
    World &mWorld;
    Entity &mOwner;
    unsigned int mUnitPerSecond;

public:
    IncreaseThirst(World &world, Entity &owner, unsigned int unitPerSecond);

    virtual void execute(unsigned int dt);
};
// LCOV_EXCL_STOP
