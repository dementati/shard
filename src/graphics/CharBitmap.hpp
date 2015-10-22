#pragma once

#include <glm/glm.hpp>

#include <cassert> 
#include <vector>

class CharBitmap
{
    std::vector<char> buffer;

public:
    const glm::uvec2 dimensions;

    CharBitmap(const char *bitmap, const glm::uvec2 dimensions);

    const char get(const glm::uvec2 position) const;
};
