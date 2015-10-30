#pragma once

#include <algorithm>
#include <functional>
#include <unordered_map>
#include <vector>

#include <glm/glm.hpp>

#include "../../math/geometry/Box.hpp"
#include "../../Assert.hpp"
#include "../../LoggerFactory.hpp"

class AStar
{
    static int dist(int x1, int y1, int x2, int y2);

public:
    static std::vector<glm::ivec2> findPath(glm::ivec2 start, glm::ivec2 stop, 
        std::function<bool(glm::ivec2)> isBlocked, Box boundingBox);
};
