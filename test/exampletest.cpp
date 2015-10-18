#include <gtest/gtest.h>

class ExampleTest : public ::testing::Test 
{
};

TEST_F(ExampleTest, Test)
{
    EXPECT_EQ(1, 1);
}
