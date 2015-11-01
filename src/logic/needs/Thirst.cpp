#include "Thirst.hpp"

Thirst::Thirst(World &world, Entity &owner)
: 
    mWorld(world), 
    mOwner(owner)
{
    ASSERT(owner.hasAttribute("thirst"), "Owner must have the thirst attribute");
    ASSERT(owner.getAttribute("thirst").isOfType<int>(), "Owner thirst attribute must be an int");
}

void Thirst::execute(unsigned int dt)
{
    if(getIntensity() == 0)
    {
        Idle idle;
        idle.execute(dt);
    } 
    else 
    {
        FindWater findWater(mWorld, mOwner);
        findWater.execute(dt);
    }
}

int Thirst::getIntensity()
{
    Variant thirst = mOwner.getAttribute("thirst");
    return thirst.get<int>();
}
