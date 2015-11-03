#pragma once

#include <map>
#include <vector>

#include <glm/glm.hpp>

#include "../math/geometry/Box.hpp"
#include "../Assert.hpp"
#include "../VectorHash.hpp"
#include "pathfinding/AStar.hpp"

class Pathfinding
{
public:
    static std::vector<glm::ivec2> findPath(glm::ivec2 start, glm::ivec2 stop, 
        std::function<bool(glm::ivec2)> isBlocked, Box boundingBox);
};
