#pragma once

#include <map>
#include <vector>

#include <glm/glm.hpp>

#include "../../math/geometry/Box.hpp"
#include "../../Assert.hpp"
#include "../../VectorHash.hpp"

class AStar
{
public:
    static std::vector<glm::ivec2> findPath(glm::ivec2 start, glm::ivec2 stop, 
        std::map<uint64_t, bool> obstacles, Box boundingBox);
};
