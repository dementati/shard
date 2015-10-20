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

TEST_F(ColorCacheTest, HasColorIdFalse)
{
    EXPECT_FALSE(cache.hasColorId(0, 0, 0));
}

TEST_F(ColorCacheTest, HasColorIdTrueOneColor)
{
    cache.getColorId(0, 0, 0);
    EXPECT_TRUE(cache.hasColorId(0, 0, 0));
}

TEST_F(ColorCacheTest, HasColorIdTrueFalseTwoColor)
{
    cache.getColorId(0, 0, 0);
    EXPECT_TRUE(cache.hasColorId(0, 0, 0));
    EXPECT_FALSE(cache.hasColorId(0, 0, 1));
}

TEST_F(ColorCacheTest, HasColorIdTrueTwoColor)
{
    cache.getColorId(0, 0, 0);
    cache.getColorId(0, 0, 1);
    EXPECT_TRUE(cache.hasColorId(0, 0, 0));
    EXPECT_TRUE(cache.hasColorId(0, 0, 1));
}

TEST_F(ColorCacheTest, GetColorPairIdOnePair)
{
    EXPECT_EQ(0, cache.getColorPairId(0, 1));
}

TEST_F(ColorCacheTest, GetColorPairIdTwoPairs)
{
    EXPECT_EQ(0, cache.getColorPairId(0, 1));
    EXPECT_EQ(1, cache.getColorPairId(1, 0));
}

TEST_F(ColorCacheTest, ColorPairIdIsRetainedOnePair)
{
    EXPECT_EQ(0, cache.getColorPairId(0, 1));
    EXPECT_EQ(0, cache.getColorPairId(0, 1));
}

TEST_F(ColorCacheTest, ColorPairIdIsRetainedTwoPairs)
{
    EXPECT_EQ(0, cache.getColorPairId(0, 1));
    EXPECT_EQ(1, cache.getColorPairId(1, 0));
    EXPECT_EQ(0, cache.getColorPairId(0, 1));
}

TEST_F(ColorCacheTest, HasColorPairIdFalse)
{
    EXPECT_FALSE(cache.hasColorPairId(0, 1));
}

TEST_F(ColorCacheTest, HasColorPairIdTrueOnePair)
{
    cache.getColorPairId(0, 1);
    EXPECT_TRUE(cache.hasColorPairId(0, 1));
}

TEST_F(ColorCacheTest, HasColorPairIdTrueFalseTwoPairs)
{
    cache.getColorPairId(0, 1);
    EXPECT_TRUE(cache.hasColorPairId(0, 1));
    EXPECT_FALSE(cache.hasColorPairId(1, 0));
}

TEST_F(ColorCacheTest, HasColorPairIdTrueTwoPairs)
{
    cache.getColorPairId(0, 1);
    cache.getColorPairId(1, 0);
    EXPECT_TRUE(cache.hasColorPairId(0, 1));
    EXPECT_TRUE(cache.hasColorPairId(1, 0));
}
