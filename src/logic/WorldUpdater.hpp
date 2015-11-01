#pragma once

#include <string>

#include "World.hpp"

// LCOV_EXCL_START
class WorldUpdater
{
    World &mWorld;

public:
    WorldUpdater(World &world);

    void update(unsigned int dt);
};
// LCOV_EXCL_STOP
