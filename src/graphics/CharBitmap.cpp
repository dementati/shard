#include "CharBitmap.hpp"

CharBitmap::CharBitmap(const char *bitmap, const unsigned int width, const unsigned int height)
    : width(width), height(height)
{
    assert(bitmap != nullptr && "Bitmap cannot be null");
    assert(width > 0 && "Width must be positive");
    assert(height > 0 && "Width must be positive");

    for(int i = 0; i < width*height; i++)
    {
        buffer.push_back(bitmap[i]); 
    }
}

const char CharBitmap::get(const unsigned int x, const unsigned int y) const
{
    assert(x >= 0 && x < width && "x must be within bounds");
    assert(y >= 0 && y < height && "x must be within bounds");

    return buffer[y*width + x];
}
