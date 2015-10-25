#include "FindWater.hpp"

FindWater::FindWater(Need &need)
    : need(need)
{
}

void FindWater::execute(double dt)
{
    // Check if water source can be found within sensory range

    // If yes, set nearest water source as target and go there

    // If no, start wandering
}

void FindWater::hasSucceeded()
{
    return false;
}
