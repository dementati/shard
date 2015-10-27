#include "Thirst.hpp"

Thirst::Thirst(World &world, Entity &owner)
: 
    thirst(0), 
    mWorld(world), 
    mOwner(owner),
    mIdle(Idle())
{
}

// LCOV_EXCL_START
const std::string Thirst::unitName() const
{
    return std::string("Thirst");
}
// LCOV_EXCL_STOP

int Thirst::getIntensity()
{
    return 0;
}

Job& Thirst::getJob()
{
    return mIdle;
}

World& Thirst::getWorld()
{
    return mWorld;
}

Entity& Thirst::getOwner()
{
    return mOwner;
}
