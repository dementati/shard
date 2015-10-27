#pragma once

#include <glm/glm.hpp>

#include <cassert> 
#include <vector>

class CharBitmap
{
    std::vector<char> buffer;

public:
    const glm::uvec2 mDimensions;

    CharBitmap(const char *bitmap, const glm::uvec2 dimensions);

    char get(const glm::uvec2 position) const;
};
