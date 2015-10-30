#include "Pathfinding.hpp"

std::vector<glm::ivec2> Pathfinding::findPath(glm::ivec2 start, glm::ivec2 stop,
    std::map<uint64_t, bool> obstacles, Box boundingBox)
{
    return AStar::findPath(start, stop, obstacles, boundingBox);
}
