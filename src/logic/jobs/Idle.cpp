#include "Idle.hpp"

// LCOV_EXCL_START
void Idle::execute(double dt)
{
    ASSERT(dt >= 0, "Delta time must be non-negative");
}

bool Idle::hasSucceeded() 
{
    return true;
}
// LCOV_EXCL_START
