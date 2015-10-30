#include <gtest/gtest.h>

#include "../../src/ncurses/ColorCache.hpp"

class ColorCacheTest : public ::testing::Test
{
protected:
    ColorCacheTest()
    :
        mCache(ColorCache())
    {
    }

    ColorCache mCache;
};

TEST_F(ColorCacheTest, GetSingleColorId)
{
    EXPECT_EQ(0, mCache.getColorId(0, 0, 0));
}

TEST_F(ColorCacheTest, GetTwoColorIds)
{
    EXPECT_EQ(0, mCache.getColorId(0, 0, 0));
    EXPECT_EQ(1, mCache.getColorId(0, 0, 1));
}

TEST_F(ColorCacheTest, ColorIdIsRetainedSingleColor)
{
    EXPECT_EQ(0, mCache.getColorId(0, 0, 0));
    EXPECT_EQ(0, mCache.getColorId(0, 0, 0));
}

TEST_F(ColorCacheTest, ColorIdIsRetainedTwoColors)
{
    EXPECT_EQ(0, mCache.getColorId(0, 0, 0));
    EXPECT_EQ(1, mCache.getColorId(0, 0, 1));
    EXPECT_EQ(0, mCache.getColorId(0, 0, 0));
}

TEST_F(ColorCacheTest, HasColorIdFalse)
{
    EXPECT_FALSE(mCache.hasColorId(0, 0, 0));
}

TEST_F(ColorCacheTest, HasColorIdTrueOneColor)
{
    mCache.getColorId(0, 0, 0);
    EXPECT_TRUE(mCache.hasColorId(0, 0, 0));
}

TEST_F(ColorCacheTest, HasColorIdTrueFalseTwoColor)
{
    mCache.getColorId(0, 0, 0);
    EXPECT_TRUE(mCache.hasColorId(0, 0, 0));
    EXPECT_FALSE(mCache.hasColorId(0, 0, 1));
}

TEST_F(ColorCacheTest, HasColorIdTrueTwoColor)
{
    mCache.getColorId(0, 0, 0);
    mCache.getColorId(0, 0, 1);
    EXPECT_TRUE(mCache.hasColorId(0, 0, 0));
    EXPECT_TRUE(mCache.hasColorId(0, 0, 1));
}

TEST_F(ColorCacheTest, GetColorPairIdOnePair)
{
    EXPECT_EQ(0, mCache.getColorPairId(0, 1));
}

TEST_F(ColorCacheTest, GetColorPairIdTwoPairs)
{
    EXPECT_EQ(0, mCache.getColorPairId(0, 1));
    EXPECT_EQ(1, mCache.getColorPairId(1, 0));
}

TEST_F(ColorCacheTest, ColorPairIdIsRetainedOnePair)
{
    EXPECT_EQ(0, mCache.getColorPairId(0, 1));
    EXPECT_EQ(0, mCache.getColorPairId(0, 1));
}

TEST_F(ColorCacheTest, ColorPairIdIsRetainedTwoPairs)
{
    EXPECT_EQ(0, mCache.getColorPairId(0, 1));
    EXPECT_EQ(1, mCache.getColorPairId(1, 0));
    EXPECT_EQ(0, mCache.getColorPairId(0, 1));
}

TEST_F(ColorCacheTest, HasColorPairIdFalse)
{
    EXPECT_FALSE(mCache.hasColorPairId(0, 1));
}

TEST_F(ColorCacheTest, HasColorPairIdTrueOnePair)
{
    mCache.getColorPairId(0, 1);
    EXPECT_TRUE(mCache.hasColorPairId(0, 1));
}

TEST_F(ColorCacheTest, HasColorPairIdTrueFalseTwoPairs)
{
    mCache.getColorPairId(0, 1);
    EXPECT_TRUE(mCache.hasColorPairId(0, 1));
    EXPECT_FALSE(mCache.hasColorPairId(1, 0));
}

TEST_F(ColorCacheTest, HasColorPairIdTrueTwoPairs)
{
    mCache.getColorPairId(0, 1);
    mCache.getColorPairId(1, 0);
    EXPECT_TRUE(mCache.hasColorPairId(0, 1));
    EXPECT_TRUE(mCache.hasColorPairId(1, 0));
}
