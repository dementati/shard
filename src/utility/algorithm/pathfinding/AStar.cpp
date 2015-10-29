#include "AStar.hpp"

std::vector<glm::ivec2> AStar::findPath(glm::ivec2 start, glm::ivec2 stop, 
    std::map<uint64_t, bool> obstacles, Box boundingBox)
{
    ASSERT(start != stop, "Start and stop positions cannot be the same");
    ASSERT(boundingBox.getVolume() > 1, 
        "Bounding box must have room for both a start and a stop position");
    ASSERT(boundingBox.contains(start), "Bounding box must contain start position");
    ASSERT(boundingBox.contains(stop), "Bounding box must contain stop position");

    std::vector<glm::ivec2> result;
    result.push_back(start);
    result.push_back(stop);
    obstacles[VectorHash::hash(start)] = true;

    return result;
}
