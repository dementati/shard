#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../src/logic/World.hpp"
#include "../mocks/MockEntity.hpp"
#include "../mocks/MockGameObject.hpp"

using ::testing::Return; 
using ::testing::ReturnRef; 
using ::testing::StrEq; 

using MockEntityType = ::testing::NiceMock<MockEntity>;
using MockGameObjectType = ::testing::NiceMock<MockGameObject>;

class WorldTest : public ::testing::Test
{
};

TEST_F(WorldTest, AddAndGetEntity)
{
    World world;
    Variant id(std::string("test"));

    auto entity = std::make_unique<MockEntityType>();
    ON_CALL(*entity, getAttribute(StrEq("id")))
        .WillByDefault(ReturnRef(id));
    world.addEntity(std::move(entity));

    auto &entities = world.getEntities();
    EXPECT_EQ(1, entities.size());
    EXPECT_EQ(std::string("test"), (*entities[0])["id"].get<std::string>());
}

TEST_F(WorldTest, AddAndGetObject)
{
    World world;
    Variant id(std::string("test"));

    auto object = std::make_unique<MockGameObjectType>();
    ON_CALL(*object, getAttribute(StrEq("id")))
        .WillByDefault(ReturnRef(id));
    world.addObject(std::move(object));

    auto &objects = world.getObjects();
    EXPECT_EQ(1, objects.size());
    EXPECT_EQ(std::string("test"), (*objects[0])["id"].get<std::string>());
}

TEST_F(WorldTest, AddAndRemoveObject)
{
    World world;

    world.addObject(std::make_unique<MockGameObjectType>());
    auto &object = *world.getObjects()[0];
    world.removeObject(object);

    EXPECT_EQ(0, world.getObjects().size());
}
