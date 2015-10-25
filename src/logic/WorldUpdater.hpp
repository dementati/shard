#pragma once

#include <string>

#include "../core/Object.hpp"
#include "World.hpp"

class WorldUpdater : public Object
{
    World &world;

public:
    WorldUpdater(World &world);

    void update(double dt);

    const std::string unitName() const;
};
