#pragma once

#include <random>

#define SEED 0;

class RNG
{
    std::default_random_engine mRng;

public:
    RNG(std::default_random_engine rng);

    virtual ~RNG();
    
    virtual unsigned int random(unsigned int lowerBoundInclusive, unsigned int upperBoundInclusive);

    static RNG createTrueRandomRNG();
};
