#include <gtest/gtest.h>

#include "../../src/logic/Entity.hpp"
#include "../mocks/MockNeed.hpp"

class EntityTest : public ::testing::Test
{
};

TEST_F(EntityTest, Create)
{
    Entity entity("");
}

TEST_F(EntityTest, Move)
{
    Entity entity("");
    std::move(entity);
}

TEST_F(EntityTest, AddNeed)
{
    Entity entity("");
    entity.addNeed(std::make_unique<MockNeed>());
}
