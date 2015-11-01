#pragma once

#include <random>

#include <gmock/gmock.h>

#include "../../src/core/RNG.hpp"


class MockRNG : public RNG
{
public:
    MockRNG()
    : 
        RNG(std::default_random_engine(0))
    {
    }

    MOCK_METHOD2(random, unsigned int(unsigned int, unsigned int));
};
