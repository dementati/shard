#include "BitPattern.hpp"

uint64_t BitPattern::concatenate(const uint16_t a, const uint16_t b, const uint16_t c)
{
    uint64_t result = a;
    result = (result << 16) | b;
    result = (result << 16) | c;

    return result;
}

uint32_t BitPattern::concatenate(const uint16_t a, const uint16_t b)
{
    uint32_t result = a;
    result = (result << 16) | b;

    return result;
}
