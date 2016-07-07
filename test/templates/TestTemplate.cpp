#include <gmock/gmock.h>
#include <gtest/gtest.h>

class TestTemplate : public ::testing::Test
{
protected: 
    // Add shared variables

    TestTemplate()
    :
    {
    }
};

TEST_F(TestTemplate, TestMethod)
{
}
