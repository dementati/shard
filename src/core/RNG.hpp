#pragma once

#include <random>

#include <glm/glm.hpp>

#define SEED 0;

class RNG
{
    std::default_random_engine mRng;

public:
    RNG(std::default_random_engine rng);

    virtual ~RNG();
    
    virtual unsigned int random(unsigned int lowerBoundInclusive, unsigned int upperBoundInclusive);

    virtual glm::ivec2 random(glm::ivec2 lowerBoundInclusive, glm::ivec2 upperBoundInclusive);

    static RNG createTrueRandomRNG();
};
