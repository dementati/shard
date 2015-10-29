#include "CharBitmap.hpp"

CharBitmap::CharBitmap(const char *bitmap, const glm::uvec2 dimensions)
: 
    mBuffer(std::vector<char>()), 
    mDimensions(dimensions)
{
    ASSERT(bitmap != nullptr, "Bitmap cannot be null");
    ASSERT(dimensions.x != 0, "Width must be positive");
    ASSERT(dimensions.y != 0, "Width must be positive");

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
    ASSERT(position.x < mDimensions.x, "x must be within bounds");
    ASSERT(position.y < mDimensions.y, "x must be within bounds");

    return mBuffer[position.y*mDimensions.x + position.x];
}
