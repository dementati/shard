#include <gtest/gtest.h>

#include "../../src/logic/GameObject.hpp"

class GameObjectTest : public ::testing::Test
{
};

TEST_F(GameObjectTest, HasAttributeFalse)
{
    GameObject object;

    EXPECT_FALSE(object.hasAttribute(""));
}

TEST_F(GameObjectTest, SetAndHasAttribute)
{
    GameObject object;
    object.addAttribute("", 0);

    EXPECT_TRUE(object.hasAttribute(""));
}

TEST_F(GameObjectTest, SetAndGetAttribute)
{
    GameObject object;
    object.addAttribute("", 0);

    EXPECT_EQ(0, object.getAttribute("").get<int>());
}

TEST_F(GameObjectTest, SetAndSubscriptOperator)
{
    GameObject object;
    object.addAttribute("", 0);

    EXPECT_EQ(0, object[""].get<int>());
}
