#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../src/logic/Entity.hpp"
#include "../mocks/MockNeed.hpp"

using ::testing::Return; 

using WrappedMockNeed = MockNeedWrapper<::testing::NiceMock<MockNeed>>;

class EntityTest : public ::testing::Test
{
public:
    WrappedMockNeed createNeed(int intensity)
    {
        WrappedMockNeed need;
        ON_CALL(need.get(), getIntensity())
            .WillByDefault(Return(intensity));
        return need;
    }

    void testPosition(glm::ivec2 position)
    {
        Entity entity("");
        entity.setPosition(position);
        EXPECT_EQ(position, entity.getPosition());
    }
};

TEST_F(EntityTest, SelectNeed)
{
    Entity entity("");
    
    entity.add(createNeed(3));
    entity.add(createNeed(4));
    entity.add(createNeed(1));
    entity.add(createNeed(2));
    
    WrappedMockNeed& selectedNeed = dynamic_cast<WrappedMockNeed&>(entity.selectNeed());

    EXPECT_EQ(4, selectedNeed.getIntensity());
}

TEST_F(EntityTest, SetAndGetPosition0x0)
{
    testPosition(glm::ivec2(0, 0));
}

TEST_F(EntityTest, SetAndGetPosition1x1)
{
    testPosition(glm::ivec2(1, 1));
}

TEST_F(EntityTest, SetAndGetPositionMinus1xMinus1)
{
    testPosition(glm::ivec2(-1, -1));
}
