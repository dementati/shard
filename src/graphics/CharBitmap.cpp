#include "CharBitmap.hpp"

CharBitmap::CharBitmap(const char *bitmap, const glm::uvec2 dimensions)
    : dimensions(dimensions)
{
    assert(bitmap != nullptr && "Bitmap cannot be null");
    assert(dimensions.x != 0 && "Width must be positive");
    assert(dimensions.y != 0 && "Width must be positive");

    for(int i = 0; i < dimensions.x*dimensions.y; i++)
    {
        buffer.push_back(bitmap[i]); 
    }
}

const char CharBitmap::get(const glm::uvec2 position) const
{
    assert(position.x < dimensions.x && "x must be within bounds");
    assert(position.y < dimensions.y && "x must be within bounds");

    return buffer[position.y*dimensions.x + position.x];
}
