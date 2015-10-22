#include <glm/glm.hpp>
#include <gtest/gtest.h>

#include "../../src/graphics/CharBitmap.hpp"

class CharBitmapTest : public ::testing::Test
{
};

TEST_F(CharBitmapTest, WidthHeight)
{
    CharBitmap bitmap("@", glm::uvec2(1, 1));

    EXPECT_EQ(1, bitmap.dimensions.x);
    EXPECT_EQ(1, bitmap.dimensions.y);
}

TEST_F(CharBitmapTest, Get_1x1)
{
    CharBitmap bitmap("@", glm::uvec2(1, 1));

    EXPECT_EQ('@', bitmap.get(glm::uvec2(0, 0)));
}

TEST_F(CharBitmapTest, Get_2x1)
{
    CharBitmap bitmap("@#", glm::uvec2(2, 1));

    EXPECT_EQ('@', bitmap.get(glm::uvec2(0, 0)));
    EXPECT_EQ('#', bitmap.get(glm::uvec2(1, 0)));
}

TEST_F(CharBitmapTest, Get_1x2)
{
    CharBitmap bitmap("@#", glm::uvec2(1, 2));

    EXPECT_EQ('@', bitmap.get(glm::uvec2(0, 0)));
    EXPECT_EQ('#', bitmap.get(glm::uvec2(0, 1)));
}

TEST_F(CharBitmapTest, Get_2x2)
{
    CharBitmap bitmap("@#XC", glm::uvec2(2, 2));

    EXPECT_EQ('@', bitmap.get(glm::uvec2(0, 0)));
    EXPECT_EQ('#', bitmap.get(glm::uvec2(1, 0)));
    EXPECT_EQ('X', bitmap.get(glm::uvec2(0, 1)));
    EXPECT_EQ('C', bitmap.get(glm::uvec2(1, 1)));
}
