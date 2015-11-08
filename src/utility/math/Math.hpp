#pragma once

#include <cmath>

#include <glm/glm.hpp>

#include "geometry/Box.hpp"

class Math
{
public:
    static unsigned int manhattanDistance(glm::ivec2 a, glm::ivec2 b);

    static unsigned int manhattanDistance(int x1, int y1, int x2, int y2);

    static Box getCenteredBox(glm::ivec2 center, unsigned int radius);
};
