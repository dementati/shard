#pragma once

#include <cassert> 
#include <vector>

class CharBitmap
{
    std::vector<char> buffer;

public:
    const unsigned int width;

    const unsigned int height;

    CharBitmap(const char *bitmap, const unsigned int width, const unsigned int height);

    const char get(const unsigned int x, const unsigned int y) const;
};
