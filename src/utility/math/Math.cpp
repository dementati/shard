#include "Math.hpp"

unsigned int Math::manhattanDistance(glm::ivec2 a, glm::ivec2 b)
{
    return manhattanDistance(a.x, a.y, b.x, b.y);
}


unsigned int Math::manhattanDistance(int x1, int y1, int x2, int y2)
{
    return abs(x1 - x2) + abs(y1 - y2);
}

Box Math::getCenteredBox(glm::ivec2 center, unsigned int radius)
{
    return Box(center - (int)radius*glm::ivec2(1, 1), (int)(2*radius + 1)*glm::ivec2(1, 1));
}
