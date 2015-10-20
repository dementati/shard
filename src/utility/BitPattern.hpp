#pragma once

#include <cstdint>

class BitPattern
{
public:
    const static uint64_t concatenate(const uint16_t a, const uint16_t b, const uint16_t c);

    const static uint32_t concatenate(const uint16_t a, const uint16_t b);
};