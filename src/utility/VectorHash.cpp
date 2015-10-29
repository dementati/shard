#include "VectorHash.hpp"

uint64_t VectorHash::hash(glm::ivec2 vector)
{
    return BitPattern::concatenate(vector.x, vector.y);
}
