#pragma once

#include <glm/glm.hpp>

#include "BitPattern.hpp"

class VectorHash
{
public:
    static uint64_t hash(glm::ivec2 vector);
};
