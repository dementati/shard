#pragma once

#include <glm/glm.hpp>

#include "BitPattern.hpp"

struct VectorHash
{
    template <typename T>
    std::size_t operator()(T t) const
    {
        return BitPattern::concatenate(t.x, t.y);
    }
};
