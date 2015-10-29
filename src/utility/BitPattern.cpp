#include "BitPattern.hpp"

uint32_t BitPattern::concatenate(const short int a, const short int b)
{
    static_assert(sizeof(short int) == 2, "Invalid size of short int");

    return concatenate16(a, b);
}

uint64_t BitPattern::concatenate(const short int a, const short int b, const short int c)
{
    static_assert(sizeof(short int) == 2, "Invalid size of short int");

    return concatenate16(a, b, c);
}

uint64_t BitPattern::concatenate(const int a, const int b)
{
    static_assert(sizeof(int) == 4, "Invalid size of int");

    return concatenate32(a, b);
}

uint64_t BitPattern::concatenate16(const uint16_t a, const uint16_t b, const uint16_t c)
{
    uint64_t result = a;
    result = (result << 16) | b;
    result = (result << 16) | c;

    return result;
}

uint32_t BitPattern::concatenate16(const uint16_t a, const uint16_t b)
{
    uint32_t result = a;
    result = (result << 16) | b;

    return result;
}

uint64_t BitPattern::concatenate32(const uint32_t a, const uint32_t b)
{
    uint64_t result = a;
    result = (result << 32) | b;

    return result;
}
