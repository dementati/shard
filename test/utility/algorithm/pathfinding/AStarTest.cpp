#include <gtest/gtest.h>

#include "../../../../src/utility/algorithm/pathfinding/AStar.hpp"

class AStarTest : public ::testing::Test
{
};

// # - edge
// S - start
// G - goal
//   - unvisited position
// . - visited position
// , - optionally visited position
// ¤ - obstacle

// Note: Upper left open square is 0x0 unless otherwise specified.

// ####
// #SG#
// ####
TEST_F(AStarTest, MinimalMap)
{
    glm::ivec2 start(0, 0);
    glm::ivec2 stop(1, 0);
    std::function<bool(glm::ivec2)> isBlocked = [] (glm::ivec2 v) { return v != v; };
    Box boundingBox(glm::ivec2(0, 0), glm::uvec2(2, 1));

    std::vector<glm::ivec2> path = AStar::findPath(start, stop, isBlocked, boundingBox);

    EXPECT_EQ(2, path.size());
    EXPECT_EQ(stop, path[0]);
    EXPECT_EQ(start, path[1]);
}

// ####
// #SG#
// ####
TEST_F(AStarTest, MinimalMapBB1x1)
{
    glm::ivec2 start(1, 1);
    glm::ivec2 stop(2, 1);
    std::function<bool(glm::ivec2)> isBlocked = [] (glm::ivec2 v) { return v != v; };
    Box boundingBox(glm::ivec2(1, 1), glm::uvec2(2, 1));

    std::vector<glm::ivec2> path = AStar::findPath(start, stop, isBlocked, boundingBox);

    EXPECT_EQ(2, path.size());
    EXPECT_EQ(stop, path[0]);
    EXPECT_EQ(start, path[1]);
}

// ####
// #SG#
// ####
TEST_F(AStarTest, MinimalMapBBMinus1xMinus1)
{
    glm::ivec2 start(-1, -1);
    glm::ivec2 stop(0, -1);
    std::function<bool(glm::ivec2)> isBlocked = [] (glm::ivec2 v) { return v != v; };
    Box boundingBox(glm::ivec2(-1, -1), glm::uvec2(2, 1));

    std::vector<glm::ivec2> path = AStar::findPath(start, stop, isBlocked, boundingBox);

    EXPECT_EQ(2, path.size());
    EXPECT_EQ(stop, path[0]);
    EXPECT_EQ(start, path[1]);
}


// #####
// #S.G#
// #####
TEST_F(AStarTest, Map3x1)
{
    glm::ivec2 start(0, 0);
    glm::ivec2 stop(2, 0);
    std::function<bool(glm::ivec2)> isBlocked = [] (glm::ivec2 v) { return v != v; };
    Box boundingBox(glm::ivec2(0, 0), glm::uvec2(3, 1));

    std::vector<glm::ivec2> path = AStar::findPath(start, stop, isBlocked, boundingBox);

    EXPECT_EQ(3, path.size());
    EXPECT_EQ(stop, path[0]);
    EXPECT_EQ(glm::ivec2(1, 0), path[1]);
    EXPECT_EQ(start, path[2]);
}

// ####
// #S,#
// #,G#
// ####
TEST_F(AStarTest, Map2x2)
{
    glm::ivec2 start(0, 0);
    glm::ivec2 stop(1, 1);
    std::function<bool(glm::ivec2)> isBlocked = [] (glm::ivec2 v) { return v != v; };
    Box boundingBox(glm::ivec2(0, 0), glm::uvec2(2, 2));

    std::vector<glm::ivec2> path = AStar::findPath(start, stop, isBlocked, boundingBox);

    EXPECT_EQ(3, path.size());
    EXPECT_EQ(stop, path[0]);
    EXPECT_EQ(start, path[2]);
}

// ####
// #S¤#
// #.G#
// ####
TEST_F(AStarTest, Map2x2SingleObstacle)
{
    glm::ivec2 start(0, 0);
    glm::ivec2 stop(1, 1);
    std::function<bool(glm::ivec2)> isBlocked = [] (glm::ivec2 v) 
    { 
        return v == glm::ivec2(1, 0); 
    };
    Box boundingBox(glm::ivec2(0, 0), glm::uvec2(2, 2));

    std::vector<glm::ivec2> path = AStar::findPath(start, stop, isBlocked, boundingBox);

    ASSERT_EQ(3, path.size());
    EXPECT_EQ(stop, path[0]);
    EXPECT_EQ(glm::ivec2(0, 1), path[1]);
    EXPECT_EQ(start, path[2]);
}

// #####
// #S,,#
// #,,G#
// #####
TEST_F(AStarTest, Map3x2)
{
    glm::ivec2 start(0, 0);
    glm::ivec2 stop(2, 1);
    std::function<bool(glm::ivec2)> isBlocked = [] (glm::ivec2 v) 
    { 
        return v != v; 
    };
    Box boundingBox(glm::ivec2(0, 0), glm::uvec2(3, 2));

    std::vector<glm::ivec2> path = AStar::findPath(start, stop, isBlocked, boundingBox);

    ASSERT_EQ(4, path.size());
    EXPECT_EQ(stop, path[0]);
    EXPECT_EQ(start, path[3]);
}

// #####
// #S¤G#
// #####
TEST_F(AStarTest, Map3x1Blocked)
{
    glm::ivec2 start(0, 0);
    glm::ivec2 stop(2, 0);
    std::function<bool(glm::ivec2)> isBlocked = [] (glm::ivec2 v) 
    { 
        return v == glm::ivec2(1, 0); 
    };
    Box boundingBox(glm::ivec2(0, 0), glm::uvec2(3, 1));

    std::vector<glm::ivec2> path = AStar::findPath(start, stop, isBlocked, boundingBox);

    ASSERT_EQ(0, path.size());
}

// #####
// #,,,#
// #S¤G#
// #,,,#
// #####
TEST_F(AStarTest, Map3x3SingleObstacle)
{
    glm::ivec2 start(0, 1);
    glm::ivec2 stop(2, 1);
    std::function<bool(glm::ivec2)> isBlocked = [] (glm::ivec2 v) 
    { 
        return v == glm::ivec2(1, 1); 
    };
    Box boundingBox(glm::ivec2(0, 0), glm::uvec2(3, 3));

    std::vector<glm::ivec2> path = AStar::findPath(start, stop, isBlocked, boundingBox);

    ASSERT_EQ(5, path.size());
    EXPECT_EQ(stop, path[0]);
    EXPECT_EQ(2, path[1].x);
    EXPECT_EQ(1, path[2].x);
    EXPECT_EQ(0, path[3].x);
    EXPECT_EQ(start, path[4]);
}

// #####
// # ¤ #
// #S¤G#
// #...#
// #####
TEST_F(AStarTest, Map3x3TwoObstacles)
{
    glm::ivec2 start(0, 1);
    glm::ivec2 stop(2, 1);
    std::function<bool(glm::ivec2)> isBlocked = [] (glm::ivec2 v) 
    { 
        return v == glm::ivec2(1, 1) || v == glm::ivec2(1, 0); 
    };
    Box boundingBox(glm::ivec2(0, 0), glm::uvec2(3, 3));

    std::vector<glm::ivec2> path = AStar::findPath(start, stop, isBlocked, boundingBox);

    ASSERT_EQ(5, path.size());
    EXPECT_EQ(stop, path[0]);
    EXPECT_EQ(glm::ivec2(2, 2), path[1]);
    EXPECT_EQ(glm::ivec2(1, 2), path[2]);
    EXPECT_EQ(glm::ivec2(0, 2), path[3]);
    EXPECT_EQ(start, path[4]);
}

// #####
// #S. #
// #¤.¤#
// # .G#
// #####
TEST_F(AStarTest, Map3x3TwoObstacles2)
{
    glm::ivec2 start(0, 0);
    glm::ivec2 stop(2, 2);
    std::function<bool(glm::ivec2)> isBlocked = [] (glm::ivec2 v) 
    { 
        return v == glm::ivec2(0, 1) || v == glm::ivec2(2, 1); 
    };
    Box boundingBox(glm::ivec2(0, 0), glm::uvec2(3, 3));

    std::vector<glm::ivec2> path = AStar::findPath(start, stop, isBlocked, boundingBox);

    ASSERT_EQ(5, path.size());
    EXPECT_EQ(stop, path[0]);
    EXPECT_EQ(glm::ivec2(1, 2), path[1]);
    EXPECT_EQ(glm::ivec2(1, 1), path[2]);
    EXPECT_EQ(glm::ivec2(1, 0), path[3]);
    EXPECT_EQ(start, path[4]);
}

// 
//  ,,,
//  S¤G
//  ,,,
//  
TEST_F(AStarTest, Map20x20OneObstacle)
{
    glm::ivec2 start(0, 0);
    glm::ivec2 stop(2, 0);
    std::function<bool(glm::ivec2)> isBlocked = [] (glm::ivec2 v) 
    { 
        return v == glm::ivec2(1, 0); 
    };
    Box boundingBox(glm::ivec2(-10, -10), glm::uvec2(20, 20));

    std::vector<glm::ivec2> path = AStar::findPath(start, stop, isBlocked, boundingBox);

    ASSERT_EQ(5, path.size());
    EXPECT_EQ(stop, path[0]);
    EXPECT_EQ(start, path[4]);
}

// #######
// #S>v¤¤#
// #v¤>>v#
// #>>o¤G#
// #######
TEST_F(AStarTest, SwitchRouteTest)
{
    glm::ivec2 start(0, 0);
    glm::ivec2 stop(4, 2);
    std::function<bool(glm::ivec2)> isBlocked = [] (glm::ivec2 v) 
    { 
        return v == glm::ivec2(3, 0) 
            || v == glm::ivec2(4, 0)
            || v == glm::ivec2(3, 2)
            || v == glm::ivec2(1, 1); 
    };
    Box boundingBox(glm::ivec2(0, 0), glm::uvec2(5, 3));

    std::vector<glm::ivec2> path = AStar::findPath(start, stop, isBlocked, boundingBox);

    EXPECT_EQ(7, path.size());
    EXPECT_EQ(stop, path[0]);
    EXPECT_EQ(start, path[6]);
}
