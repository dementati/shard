#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../../src/logic/jobs/Idle.hpp"
#include "../../../src/logic/needs/Thirst.hpp"
#include "../../mocks/MockEntity.hpp"
#include "../../mocks/MockWorld.hpp"

using ::testing::Return; 
using ::testing::ReturnRef; 
using ::testing::StrEq; 

using MockEntityType = ::testing::NiceMock<MockEntity>;

class ThirstTest : public ::testing::Test
{
};

TEST_F(ThirstTest, Create)
{
    MockWorld world;

    MockEntityType entity;
    ON_CALL(entity, hasAttribute(StrEq("thirst")))
        .WillByDefault(Return(true));
    Variant thirstVar = 0;
    ON_CALL(entity, getAttribute(StrEq("thirst")))
        .WillByDefault(ReturnRef(thirstVar));

    Thirst thirst(world, entity);

    EXPECT_EQ(0, thirst.getIntensity());
}

TEST_F(ThirstTest, GetIntensity)
{
    // Verify that intensity is computed correctly
}
