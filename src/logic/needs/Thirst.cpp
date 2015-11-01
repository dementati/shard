#include "Thirst.hpp"

Thirst::Thirst(World &world, Entity &owner)
: 
    mWorld(world), 
    mOwner(owner)
{
    ASSERT(owner.hasAttribute("thirst"), "Owner must have the thirst attribute");
    ASSERT(owner.getAttribute("thirst").isOfType<unsigned int>(), "Owner thirst attribute must be an unsigned int");
}

// LCOV_EXCL_START
void Thirst::execute(unsigned int dt)
{
    auto job = getJob();
    job->execute(dt);
}
// LCOV_EXCL_STOP

unsigned int Thirst::getIntensity()
{
    Variant thirst = mOwner.getAttribute("thirst");
    return thirst.get<unsigned int>();
}

std::unique_ptr<Job> Thirst::getJob()
{
    if(getIntensity() == 0)
    {
        return std::make_unique<Idle>();
    } 
    else 
    {
        return std::make_unique<FindWater>(mWorld, mOwner);
    }
}
