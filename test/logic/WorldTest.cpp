#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../src/logic/World.hpp"
#include "../mocks/MockEntity.hpp"

using ::testing::Return; 
using ::testing::ReturnRef; 

using MockEntityType = ::testing::NiceMock<MockEntity>;

class WorldTest : public ::testing::Test
{
};

TEST_F(WorldTest, AddAndGetEntity)
{
    World world;

    {
        auto entity = std::make_unique<MockEntityType>();
        ON_CALL(*entity, getRenderableId())
            .WillByDefault(Return(std::string("test")));
        world.add(std::move(entity));
    }

    {
        auto &entities = world.getEntities();
        auto &entity = dynamic_cast<MockEntityType&>(*entities[0]); 

        EXPECT_EQ(std::string("test"), entity.getRenderableId());
    }
}
