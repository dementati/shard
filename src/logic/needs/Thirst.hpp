#pragma once

#include <string>
#include <vector>

#include "../jobs/Idle.hpp"
#include "../Job.hpp"
#include "../Need.hpp"

// LCOV_EXCL_START
class Thirst : public Need
{
    unsigned int thirst;
    World &mWorld;
    Entity &mOwner;

    // Jobs
    Idle mIdle;

public:
    Thirst(World &world, Entity &owner);

    const std::string unitName() const;

    int getIntensity();

    Job& getJob();

    World& getWorld();

    Entity& getOwner();
};
// LCOV_EXCL_STOP
