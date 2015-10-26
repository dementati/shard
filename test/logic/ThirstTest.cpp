#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../src/logic/needs/Thirst.hpp"
#include "../mocks/MockEntity.hpp"
#include "../mocks/MockWorld.hpp"

class ThirstTest : public ::testing::Test
{
};

TEST_F(ThirstTest, Create)
{
    /*
    MockWorld world;
    MockEntity entity("test");

    EXPECT_CALL(world, add(entity));

    world.add(entity);
    */
}

TEST_F(ThirstTest, GetIntensity)
{
    // Verify that intensity is computed correctly
}
