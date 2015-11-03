#pragma once

#include <string>

#include "../utility/LoggerFactory.hpp"
#include "World.hpp"

// LCOV_EXCL_START
class WorldUpdater
{
    LoggerPtr mLogger;

    World &mWorld;

public:
    WorldUpdater(World &world);

    void update(unsigned int dt);
};
// LCOV_EXCL_STOP
