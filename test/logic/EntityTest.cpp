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
};

TEST_F(EntityTest, SelectNeed)
{
    Entity entity;
    
    entity.add(createNeed(3));
    entity.add(createNeed(4));
    entity.add(createNeed(1));
    entity.add(createNeed(2));
    
    WrappedMockNeed& selectedNeed = dynamic_cast<WrappedMockNeed&>(entity.selectNeed());

    EXPECT_EQ(4, selectedNeed.getIntensity());
}
