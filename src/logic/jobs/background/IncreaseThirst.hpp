#pragma once

#include <string>

#include "../../../utility/Assert.hpp"
#include "../../Entity.hpp"
#include "../../BackgroundJob.hpp"
#include "../../World.hpp"

// LCOV_EXCL_START
class IncreaseThirst : public BackgroundJob
{
    World &mWorld;
    Entity &mOwner;
    float mUnitPerSecond;

public:
    IncreaseThirst(World &world, Entity &owner, float unitPerSecond);

    virtual void execute(unsigned int dt);
};
// LCOV_EXCL_STOP
