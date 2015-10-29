#pragma once

#include <glm/glm.hpp>

#include <cassert> 
#include <vector>

class CharBitmap
{
    std::vector<char> mBuffer;

    const glm::uvec2 mDimensions;

public:
    CharBitmap(const char *bitmap, const glm::uvec2 dimensions);

    const glm::uvec2 getDimensions() const;

    char get(const glm::uvec2 position) const;
};
