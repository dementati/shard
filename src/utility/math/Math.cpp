#include "Math.hpp"

unsigned int Math::manhattanDistance(glm::ivec2 a, glm::ivec2 b)
{
    return abs(a.x - b.x) + abs(a.y - b.y);
}
