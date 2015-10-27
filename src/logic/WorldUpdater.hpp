#pragma once

#include <string>

#include "../core/Object.hpp"
#include "World.hpp"

// LCOV_EXCL_START
class WorldUpdater : public Object
{
    World &mWorld;

public:
    WorldUpdater(World &world);

    void update(double dt);

    const std::string unitName() const;
};
// LCOV_EXCL_STOP
