#include <vector>

#include <gtest/gtest.h>

#include "../../src/utility/Variant.hpp"

class VariantTest : public ::testing::Test
{
};

TEST_F(VariantTest, Int)
{
    Variant v = 1;
    EXPECT_TRUE(v.isOfType<int>());
    EXPECT_EQ(1, v.get<int>());
}

TEST_F(VariantTest, InitializeWithoutType)
{
    Variant v;
    EXPECT_TRUE(v.isOfType<void>());
}

TEST_F(VariantTest, MoveConstructor)
{
    Variant v = 1;
    Variant v2 = std::move(v);
    EXPECT_TRUE(v.isOfType<void>());
    EXPECT_TRUE(v2.isOfType<int>());
    EXPECT_EQ(1, v2.get<int>());
}

TEST_F(VariantTest, MoveAssignmentVoidInt)
{
    Variant v = 1;
    Variant v2;
    v2 = std::move(v);
    EXPECT_TRUE(v2.isOfType<int>());
    EXPECT_EQ(1, v2.get<int>());
}

TEST_F(VariantTest, Copy)
{
    Variant v = 1;
    Variant v2 = v;
    EXPECT_TRUE(v.isOfType<int>());
    EXPECT_TRUE(v2.isOfType<int>());
    EXPECT_EQ(1, v.get<int>());
    EXPECT_EQ(1, v2.get<int>());
}

TEST_F(VariantTest, CopyAssignment)
{
    Variant v = 1;
    Variant v2;
    v2 = v;
    EXPECT_TRUE(v.isOfType<int>());
    EXPECT_TRUE(v2.isOfType<int>());
    EXPECT_EQ(1, v.get<int>());
    EXPECT_EQ(1, v2.get<int>());
}

TEST_F(VariantTest, IsSameType_VoidInt)
{
    Variant v = 1;
    Variant v2;
    EXPECT_FALSE(v.isSameTypeAs(v2));
}

TEST_F(VariantTest, IsSameType_IntInt)
{
    Variant v = 1;
    Variant v2 = 2;
    EXPECT_TRUE(v.isSameTypeAs(v2));
}
