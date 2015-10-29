#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "../utility/Assert.hpp"

class CharBitmap
{
    std::vector<char> mBuffer;

    const glm::uvec2 mDimensions;

public:
    CharBitmap(const char *bitmap, const glm::uvec2 dimensions);

    const glm::uvec2 getDimensions() const;

    char get(const glm::uvec2 position) const;
};
