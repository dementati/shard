#include <gtest/gtest.h>

#include "../../../../src/utility/math/geometry/Box.hpp"

class BoxTest : public ::testing::Test
{
};

TEST_F(BoxTest, GetZeroPosition)
{
    Box box(glm::ivec2(0, 0), glm::uvec2(1, 1));

    EXPECT_EQ(glm::ivec2(0, 0), box.getPosition());
}

TEST_F(BoxTest, GetNonZeroPosition)
{
    Box box(glm::ivec2(0, 1), glm::uvec2(1, 1));

    EXPECT_EQ(glm::ivec2(0, 1), box.getPosition());
}

TEST_F(BoxTest, GetDimensions)
{
    Box box(glm::ivec2(0, 0), glm::uvec2(1, 1));

    EXPECT_EQ(glm::uvec2(1, 1), box.getDimensions());
}

TEST_F(BoxTest, DoesContain_T0x0_P0x0_D1x1)
{
    Box box(glm::ivec2(0, 0), glm::uvec2(1, 1));

    EXPECT_TRUE(box.contains(glm::ivec2(0, 0)));
}

TEST_F(BoxTest, DoesNotContain_TMinus1x0_P0x0_D1x1)
{
    Box box(glm::ivec2(0, 0), glm::uvec2(1, 1));

    EXPECT_FALSE(box.contains(glm::ivec2(-1, 0)));
}

TEST_F(BoxTest, DoesNotContain_T0xMinus1_P0x0_D1x1)
{
    Box box(glm::ivec2(0, 0), glm::uvec2(1, 1));

    EXPECT_FALSE(box.contains(glm::ivec2(0, -1)));
}

TEST_F(BoxTest, DoesNotContain_T1x0_P0x0_D1x1)
{
    Box box(glm::ivec2(0, 0), glm::uvec2(1, 1));

    EXPECT_FALSE(box.contains(glm::ivec2(1, 0)));
}

TEST_F(BoxTest, DoesNotContain_T0x1_P0x0_D1x1)
{
    Box box(glm::ivec2(0, 0), glm::uvec2(1, 1));

    EXPECT_FALSE(box.contains(glm::ivec2(0, 1)));
}

TEST_F(BoxTest, DoesContain_T1x0_P0x0_D2x1)
{
    Box box(glm::ivec2(0, 0), glm::uvec2(2, 1));

    EXPECT_TRUE(box.contains(glm::ivec2(1, 0)));
}

TEST_F(BoxTest, DoesNotContain_T2x0_P0x0_D2x1)
{
    Box box(glm::ivec2(0, 0), glm::uvec2(2, 1));

    EXPECT_FALSE(box.contains(glm::ivec2(2, 0)));
}

TEST_F(BoxTest, GetVolume_D1x1)
{
    Box box(glm::ivec2(0, 0), glm::uvec2(1, 1));

    EXPECT_EQ(1, box.getVolume());
}

TEST_F(BoxTest, GetVolume_D2x1)
{
    Box box(glm::ivec2(0, 0), glm::uvec2(2, 1));

    EXPECT_EQ(2, box.getVolume());
}

TEST_F(BoxTest, GetVolume_D2x2)
{
    Box box(glm::ivec2(0, 0), glm::uvec2(2, 2));

    EXPECT_EQ(4, box.getVolume());
}
