#include "BitPattern.hpp"

const uint64_t BitPattern::concatenate(const uint16_t a, const uint16_t b, const uint16_t c)
{
    uint64_t result = a;
    result = (result << 16) | b;
    result = (result << 16) | c;

    return result;
}
