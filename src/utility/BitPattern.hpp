#pragma once

#include <cstdint>

#include "Assert.hpp"

class BitPattern
{
public:
    static uint32_t concatenate(const short int a, const short int b);

    static uint64_t concatenate(const short int a, const short int b, const short int c);

    static uint64_t concatenate(const int a, const int b);

    static uint64_t concatenate16(const uint16_t a, const uint16_t b, const uint16_t c);

    static uint32_t concatenate16(const uint16_t a, const uint16_t b);

    static uint64_t concatenate32(const uint32_t a, const uint32_t b);
};
