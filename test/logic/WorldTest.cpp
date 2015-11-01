#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../src/logic/World.hpp"
#include "../mocks/MockEntity.hpp"

using ::testing::Return; 
using ::testing::ReturnRef; 
using ::testing::StrEq; 

using MockEntityType = ::testing::NiceMock<MockEntity>;

class WorldTest : public ::testing::Test
{
};

TEST_F(WorldTest, AddAndGetEntity)
{
    World world;
    Variant mTestRenderableId(std::string("test"));

    {
        auto entity = std::make_unique<MockEntityType>();
        ON_CALL(*entity, getAttribute(StrEq("renderableId")))
            .WillByDefault(ReturnRef(mTestRenderableId));
        world.addEntity(std::move(entity));
    }

    {
        auto &entities = world.getEntities();
        auto &entity = dynamic_cast<MockEntityType&>(*entities[0]); 

        EXPECT_EQ(std::string("test"), entity["renderableId"].get<std::string>());
    }
}
