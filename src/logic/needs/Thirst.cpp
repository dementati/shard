#include "Thirst.hpp"

Thirst::Thirst(World &world, Entity &owner)
: 
    mLogger(LoggerFactory::createLogger("Thirst", Severity::DEBUG)),
    mWorld(world), 
    mOwner(owner)
{
    ASSERT(owner.hasAttribute("thirst"), "Owner must have the thirst attribute");
    ASSERT(owner.getAttribute("thirst").isOfType<unsigned int>(), "Owner thirst attribute must be an unsigned int");

    mLogger->info("Finished construction");
}

// LCOV_EXCL_START
void Thirst::execute(unsigned int dt)
{
    mLogger->debug("Executing...");
    auto job = getJob();
    job->execute(dt);
    mLogger->debug("Finished executing");
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
        mLogger->debug("Thirst is zero, idling...");
        return std::make_unique<Idle>();
    } 
    else 
    {
        mLogger->debug("Thirst is non-zero, finding water...");
        return std::make_unique<FindWater>(mWorld, mOwner);
    }
}
