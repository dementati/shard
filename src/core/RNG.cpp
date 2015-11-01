#include "RNG.hpp"

// LCOV_EXCL_START
RNG::RNG(std::default_random_engine rng)
:
    mRng(rng)
{
}

RNG::~RNG()
{
}

unsigned int RNG::random(unsigned int lowerBoundInclusive, unsigned int upperBoundInclusive)
{
    std::uniform_int_distribution<unsigned int> 
        uniform_dist(lowerBoundInclusive, upperBoundInclusive);
    return uniform_dist(mRng); 
}

RNG RNG::createTrueRandomRNG()
{
    std::random_device rd;
    return RNG(std::default_random_engine(rd()));
}
// LCOV_EXCL_STOP
