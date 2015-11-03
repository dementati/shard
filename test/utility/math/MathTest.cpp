#include <gtest/gtest.h>

#include "../../../src/utility/math/Math.hpp"

class MathTest : public ::testing::Test
{
};

// 0x0 <-> 0x0 -> 0
TEST_F(MathTest, ManhattanDistanceEqualZero)
{
    EXPECT_EQ(0, Math::manhattanDistance(glm::ivec2(0, 0), glm::ivec2(0, 0)));
}

// 1x1 <-> 1x1 -> 0
TEST_F(MathTest, ManhattanDistanceEqual1x1)
{
    EXPECT_EQ(0, Math::manhattanDistance(glm::ivec2(1, 1), glm::ivec2(1, 1)));
}

// 0x0 <-> 0x1 -> 1
TEST_F(MathTest, ManhattanDistance_0x0_0x1)
{
    EXPECT_EQ(1, Math::manhattanDistance(glm::ivec2(0, 0), glm::ivec2(0, 1)));
}

// 0x0 <-> 0x-1 -> 1
TEST_F(MathTest, ManhattanDistance_0x0_0xMinus1)
{
    EXPECT_EQ(1, Math::manhattanDistance(glm::ivec2(0, 0), glm::ivec2(0, -1)));
}

// 0x0 <-> 1x1 -> 2
TEST_F(MathTest, ManhattanDistance_0x0_1x1)
{
    EXPECT_EQ(2, Math::manhattanDistance(glm::ivec2(0, 0), glm::ivec2(1, 1)));
}

// -1x-1 <-> 0x0 -> 2
TEST_F(MathTest, ManhattanDistance_Minus1xMinus1_0x0)
{
    EXPECT_EQ(2, Math::manhattanDistance(glm::ivec2(-1, -1), glm::ivec2(0, 0)));
}
