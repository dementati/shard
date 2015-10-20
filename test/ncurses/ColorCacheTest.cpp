#include <gtest/gtest.h>

#include "../../src/ncurses/ColorCache.hpp"

class ColorCacheTest : public ::testing::Test
{
protected:
    ColorCache cache;
};

TEST_F(ColorCacheTest, GetSingleColorId)
{
    EXPECT_EQ(0, cache.getColorId(0, 0, 0));
}

TEST_F(ColorCacheTest, GetTwoColorIds)
{
    EXPECT_EQ(0, cache.getColorId(0, 0, 0));
    EXPECT_EQ(1, cache.getColorId(0, 0, 1));
}

TEST_F(ColorCacheTest, ColorIdIsRetainedSingleColor)
{
    EXPECT_EQ(0, cache.getColorId(0, 0, 0));
    EXPECT_EQ(0, cache.getColorId(0, 0, 0));
}

TEST_F(ColorCacheTest, ColorIdIsRetainedTwoColors)
{
    EXPECT_EQ(0, cache.getColorId(0, 0, 0));
    EXPECT_EQ(1, cache.getColorId(0, 0, 1));
    EXPECT_EQ(0, cache.getColorId(0, 0, 0));
}
