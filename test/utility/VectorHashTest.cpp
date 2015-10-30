#include <gtest/gtest.h>

#include "../../src/utility/VectorHash.hpp"

class VectorHashTest : public ::testing::Test
{
};

TEST_F(VectorHashTest, HashTwoEqual)
{
    EXPECT_EQ(VectorHash::hash(glm::ivec2(0, 0)), VectorHash::hash(glm::ivec2(0, 0)));
}

TEST_F(VectorHashTest, HashTwoUnequal)
{
    EXPECT_NE(VectorHash::hash(glm::ivec2(0, 1)), VectorHash::hash(glm::ivec2(0, 0)));
}
