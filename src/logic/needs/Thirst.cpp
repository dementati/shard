#include "Thirst.hpp"

Thirst::Thirst(World &world, Entity &owner)
    : thirst(0), world(world), owner(owner)
{
}

const std::string Thirst::unitName() const
{
    return std::string("Thirst");
}

int Thirst::getIntensity()
{
    return INTENSITY_WEIGHT*thirst;
}

Job& Thirst::getJob()
{
}

World& Thirst::getWorld()
{
    return world;
}

Entity& Thirst::getOwner()
{
    return owner;
}
