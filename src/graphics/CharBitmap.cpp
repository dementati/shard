#include "CharBitmap.hpp"

CharBitmap::CharBitmap(const char *bitmap, const glm::uvec2 dimensions)
: 
    mBuffer(std::vector<char>()), 
    mDimensions(dimensions)
{
    assert(bitmap != nullptr && "Bitmap cannot be null");
    assert(dimensions.x != 0 && "Width must be positive");
    assert(dimensions.y != 0 && "Width must be positive");

    for(unsigned int i = 0; i < dimensions.x*dimensions.y; i++)
    {
        mBuffer.push_back(bitmap[i]); 
    }
}

const glm::uvec2 CharBitmap::getDimensions() const
{
    return mDimensions;
}

char CharBitmap::get(const glm::uvec2 position) const
{
    assert(position.x < mDimensions.x && "x must be within bounds");
    assert(position.y < mDimensions.y && "x must be within bounds");

    return mBuffer[position.y*mDimensions.x + position.x];
}
