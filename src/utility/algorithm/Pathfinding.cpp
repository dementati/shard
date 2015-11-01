#include "Pathfinding.hpp"

std::vector<glm::ivec2> Pathfinding::findPath(glm::ivec2 start, glm::ivec2 stop,
    std::function<bool(glm::ivec2)> isBlocked, Box boundingBox)
{
    return AStar::findPath(start, stop, isBlocked, boundingBox);
}
