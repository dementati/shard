#pragma once

#include <string>

#include "../Need.hpp"

#define INTENSITY_WEIGHT 1

class Thirst : public Need
{
    unsigned int thirst;
    World &world;
    Entity &owner;

public:
    Thirst(World &world, Entity &owner);

    const std::string unitName() const;

    int getIntensity();

    Job& getJob();

    World& getWorld();

    Entity& getOwner();
};