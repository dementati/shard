#include "Math.hpp"

unsigned int Math::manhattanDistance(glm::ivec2 a, glm::ivec2 b)
{
    return manhattanDistance(a.x, a.y, b.x, b.y);
}


unsigned int Math::manhattanDistance(int x1, int y1, int x2, int y2)
{
    return abs(x1 - x2) + abs(y1 - y2);
}
