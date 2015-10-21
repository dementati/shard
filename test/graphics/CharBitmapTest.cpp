#include <gtest/gtest.h>

#include "../../src/graphics/CharBitmap.hpp"

class CharBitmapTest : public ::testing::Test
{
};

TEST_F(CharBitmapTest, WidthHeight)
{
    CharBitmap bitmap("@", 1, 1);

    EXPECT_EQ(1, bitmap.width);
    EXPECT_EQ(1, bitmap.height);
}

TEST_F(CharBitmapTest, Get_1x1)
{
    CharBitmap bitmap("@", 1, 1);

    EXPECT_EQ('@', bitmap.get(0, 0));
}

TEST_F(CharBitmapTest, Get_2x1)
{
    CharBitmap bitmap("@#", 2, 1);

    EXPECT_EQ('@', bitmap.get(0, 0));
    EXPECT_EQ('#', bitmap.get(1, 0));
}

TEST_F(CharBitmapTest, Get_1x2)
{
    CharBitmap bitmap("@#", 1, 2);

    EXPECT_EQ('@', bitmap.get(0, 0));
    EXPECT_EQ('#', bitmap.get(0, 1));
}

TEST_F(CharBitmapTest, Get_2x2)
{
    CharBitmap bitmap("@#XC", 2, 2);

    EXPECT_EQ('@', bitmap.get(0, 0));
    EXPECT_EQ('#', bitmap.get(1, 0));
    EXPECT_EQ('X', bitmap.get(0, 1));
    EXPECT_EQ('C', bitmap.get(1, 1));
}
