#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../src/logic/jobs/Idle.hpp"
#include "../../src/logic/needs/Thirst.hpp"
#include "../mocks/MockEntity.hpp"
#include "../mocks/MockWorld.hpp"

class ThirstTest : public ::testing::Test
{
};

TEST_F(ThirstTest, Create)
{
    MockWorld world;
    MockEntity entity;

    Thirst thirst(world, entity);

    EXPECT_EQ(&world, &thirst.getWorld());
    EXPECT_EQ(&entity, &thirst.getOwner());
    EXPECT_EQ(0, thirst.getIntensity());
    dynamic_cast<Idle&>(thirst.getJob());
}

TEST_F(ThirstTest, GetIntensity)
{
    // Verify that intensity is computed correctly
}
