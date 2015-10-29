#include <vector>

#include <gtest/gtest.h>

#include "../../src/utility/Variant.hpp"

class VariantTest : public ::testing::Test
{
};

TEST_F(VariantTest, TestInt)
{
    Variant v = 1;
    EXPECT_EQ(1, v.get<int>());
}
