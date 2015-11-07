#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../src/logic/Entity.hpp"
#include "../mocks/MockNeed.hpp"

using ::testing::Return; 

using MockNeedType = ::testing::NiceMock<MockNeed>;

class EntityTest : public ::testing::Test
{
};

TEST_F(EntityTest, SelectNeed)
{
    Entity entity;
  
    {
        auto need = std::make_unique<MockNeedType>();
        ON_CALL(*need, getIntensity())
            .WillByDefault(Return(3));
        entity.add(std::move(need));
    }

    {
        auto need = std::make_unique<MockNeedType>();
        ON_CALL(*need, getIntensity())
            .WillByDefault(Return(4));
        entity.add(std::move(need));
    }

    {
        auto need = std::make_unique<MockNeedType>();
        ON_CALL(*need, getIntensity())
            .WillByDefault(Return(1));
        entity.add(std::move(need));
    }

    {
        auto need = std::make_unique<MockNeedType>();
        ON_CALL(*need, getIntensity())
            .WillByDefault(Return(2));
        entity.add(std::move(need));
    }   
    
    MockNeedType& selectedNeed = dynamic_cast<MockNeedType&>(entity.selectNeed());

    EXPECT_EQ(4, selectedNeed.getIntensity());
}

TEST_F(EntityTest, hasNeeds_NoNeeds)
{
    Entity entity;
  
    EXPECT_FALSE(entity.hasNeeds());
}

TEST_F(EntityTest, hasNeeds_OneNeed)
{
    Entity entity;

    auto need = std::make_unique<MockNeedType>();
    entity.add(std::move(need));
  
    EXPECT_TRUE(entity.hasNeeds());
}
