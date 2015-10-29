#include <gtest/gtest.h>

#include "../../../../src/utility/algorithm/pathfinding/AStar.hpp"

class AStarTest : public ::testing::Test
{
};

TEST_F(AStarTest, MinimalMap)
{
    glm::ivec2 start(0, 0);
    glm::ivec2 stop(1, 0);
    std::map<uint64_t, bool> obstacles;
    Box boundingBox(glm::ivec2(0, 0), glm::uvec2(2, 1));

    std::vector<glm::ivec2> path = AStar::findPath(start, stop, obstacles, boundingBox);

    EXPECT_EQ(start, path[0]);
    EXPECT_EQ(stop, path[1]);
}

TEST_F(AStarTest, Map3x1)
{
    glm::ivec2 start(0, 0);
    glm::ivec2 stop(2, 0);
    std::map<uint64_t, bool> obstacles;
    Box boundingBox(glm::ivec2(0, 0), glm::uvec2(3, 1));

    std::vector<glm::ivec2> path = AStar::findPath(start, stop, obstacles, boundingBox);

    EXPECT_EQ(start, path[0]);
    EXPECT_EQ(glm::ivec2(1, 0), path[1]);
    EXPECT_EQ(stop, path[2]);
}
