#include "Thirst.hpp"

Thirst::Thirst(World &world, Entity &owner)
: 
    mLogger(LoggerFactory::createLogger("Thirst", Severity::DEBUG)),
    mWorld(world), 
    mOwner(owner),
    mJobStack()
{
    ASSERT(owner.hasAttribute("thirst"), "Owner must have the thirst attribute");
    ASSERT(owner.getAttribute("thirst").isOfType<unsigned int>(), "Owner thirst attribute must be an unsigned int");

    LOG_INFO(mLogger, "Finished construction");
}

// LCOV_EXCL_START
void Thirst::execute(unsigned int dt)
{
    ASSERT(dt == dt, ""); // Getting rid of unused parameter warning

    LOG_DEBUG(mLogger, "Executing...");

    if(getIntensity() == 0)
    {
        LOG_DEBUG(mLogger, "Thirst is zero, idling...");
    } 
    else 
    {
        LOG_DEBUG(mLogger, "Thirst is non-zero, finding water...");
        mJobStack.push_back(std::make_unique<FindWater>(mJobStack, mWorld, mOwner));
    }

    LOG_DEBUG(mLogger, "Finished executing");
}
// LCOV_EXCL_STOP

unsigned int Thirst::getIntensity()
{
    Variant thirst = mOwner.getAttribute("thirst");
    return thirst.get<unsigned int>();
}

JobStack& Thirst::getJobStack()
{
    return mJobStack;
}
