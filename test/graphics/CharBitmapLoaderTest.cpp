#include <iostream>

#include <gtest/gtest.h>
#include <glm/glm.hpp>

#include "../../src/core/InvalidArgumentException.hpp"
#include "../../src/graphics/CharBitmap.hpp"
#include "../../src/graphics/CharBitmapLoader.hpp"

#define SIZE_1x1_FILE_PATH "../test/resources/charBitmaps/1x1.txt"
#define SIZE_2x2_FILE_PATH "../test/resources/charBitmaps/2x2.txt"
#define EMPTY_FILE_PATH "../test/resources/charBitmaps/empty.txt"
#define JAGGED_FILE_PATH "../test/resources/charBitmaps/jagged.txt"

class CharBitmapLoaderTest : public ::testing::Test
{
protected:
    CharBitmapLoader mLoader;

    CharBitmapLoaderTest()
        : mLoader(std::cout)
    {
    }
};

TEST_F(CharBitmapLoaderTest, LoadNonExistentFile)
{
    ASSERT_THROW(mLoader.load(" "), InvalidArgumentException);
}

TEST_F(CharBitmapLoaderTest, LoadEmptyFile)
{
    ASSERT_THROW(mLoader.load(EMPTY_FILE_PATH), InvalidFormatException);
}

TEST_F(CharBitmapLoaderTest, LoadJaggedFile)
{
    ASSERT_THROW(mLoader.load(JAGGED_FILE_PATH), InvalidFormatException);
}

TEST_F(CharBitmapLoaderTest, Load1x1File)
{
    CharBitmap bitmap = mLoader.load(SIZE_1x1_FILE_PATH);

    ASSERT_EQ(glm::uvec2(1, 1), bitmap.mDimensions);
    ASSERT_EQ('#', bitmap.get(glm::uvec2(0, 0)));
}

TEST_F(CharBitmapLoaderTest, Load2x2File)
{
    CharBitmap bitmap = mLoader.load(SIZE_2x2_FILE_PATH);

    ASSERT_EQ(glm::uvec2(2, 2), bitmap.mDimensions);
    ASSERT_EQ('#', bitmap.get(glm::uvec2(0, 0)));
    ASSERT_EQ('%', bitmap.get(glm::uvec2(1, 0)));
    ASSERT_EQ('C', bitmap.get(glm::uvec2(0, 1)));
    ASSERT_EQ('X', bitmap.get(glm::uvec2(1, 1)));
}
