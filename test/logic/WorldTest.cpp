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
protected:
    MockGameObjectType mObject;
    Variant mObjectSolid;
    Variant mObjectPosition;

    WorldTest()
    :
        mObjectSolid(true),
        mObjectPosition(glm::ivec2(0, 0))
    {
        ON_CALL(mObject, hasAttribute("solid"))
        .WillByDefault(Return(true));

        ON_CALL(mObject, getAttribute("solid"))
            .WillByDefault(ReturnRef(mObjectSolid));

        ON_CALL(mObject, hasAttribute("position"))
            .WillByDefault(Return(true));

        ON_CALL(mObject, getAttribute("position"))
            .WillByDefault(ReturnRef(mObjectPosition));
    }
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

TEST_F(WorldTest, isBlocked_emptyWorld)
{
    World world;

    EXPECT_FALSE(world.isBlocked(glm::ivec2(0, 0)));
    EXPECT_FALSE(world.isBlocked(glm::ivec2(1, 0)));
    EXPECT_FALSE(world.isBlocked(glm::ivec2(0, 1)));
    EXPECT_FALSE(world.isBlocked(glm::ivec2(-1, 0)));
    EXPECT_FALSE(world.isBlocked(glm::ivec2(0, -1)));
    EXPECT_FALSE(world.isBlocked(glm::ivec2(1, 1)));
    EXPECT_FALSE(world.isBlocked(glm::ivec2(-1, -1)));
    EXPECT_FALSE(world.isBlocked(glm::ivec2(1, -1)));
    EXPECT_FALSE(world.isBlocked(glm::ivec2(-1, 1)));
}

TEST_F(WorldTest, setObjectWithoutSolidAttributeAndCheckMap)
{
    World world;

    MockGameObjectType object;

    world.setBlockedMapIfSolid(object, true);

    EXPECT_FALSE(world.isBlocked(glm::ivec2(0, 0)));
    EXPECT_FALSE(world.isBlocked(glm::ivec2(1, 0)));
    EXPECT_FALSE(world.isBlocked(glm::ivec2(0, 1)));
    EXPECT_FALSE(world.isBlocked(glm::ivec2(-1, 0)));
    EXPECT_FALSE(world.isBlocked(glm::ivec2(0, -1)));
    EXPECT_FALSE(world.isBlocked(glm::ivec2(1, 1)));
    EXPECT_FALSE(world.isBlocked(glm::ivec2(-1, -1)));
    EXPECT_FALSE(world.isBlocked(glm::ivec2(1, -1)));
    EXPECT_FALSE(world.isBlocked(glm::ivec2(-1, 1)));
}

TEST_F(WorldTest, setNonSolidObjectAndCheckMap)
{
    World world;

    MockGameObjectType object;
    Variant objectSolid = false;

    ON_CALL(object, hasAttribute("solid"))
        .WillByDefault(Return(true));

    ON_CALL(object, getAttribute("solid"))
        .WillByDefault(ReturnRef(objectSolid));

    world.setBlockedMapIfSolid(object, true);

    EXPECT_FALSE(world.isBlocked(glm::ivec2(0, 0)));
    EXPECT_FALSE(world.isBlocked(glm::ivec2(1, 0)));
    EXPECT_FALSE(world.isBlocked(glm::ivec2(0, 1)));
    EXPECT_FALSE(world.isBlocked(glm::ivec2(-1, 0)));
    EXPECT_FALSE(world.isBlocked(glm::ivec2(0, -1)));
    EXPECT_FALSE(world.isBlocked(glm::ivec2(1, 1)));
    EXPECT_FALSE(world.isBlocked(glm::ivec2(-1, -1)));
    EXPECT_FALSE(world.isBlocked(glm::ivec2(1, -1)));
    EXPECT_FALSE(world.isBlocked(glm::ivec2(-1, 1)));
}

TEST_F(WorldTest, setSolidObjectAndCheckMap_position0x0)
{
    World world;

    world.setBlockedMapIfSolid(mObject, true);

    EXPECT_TRUE(world.isBlocked(glm::ivec2(0, 0)));
    EXPECT_FALSE(world.isBlocked(glm::ivec2(1, 0)));
    EXPECT_FALSE(world.isBlocked(glm::ivec2(0, 1)));
    EXPECT_FALSE(world.isBlocked(glm::ivec2(-1, 0)));
    EXPECT_FALSE(world.isBlocked(glm::ivec2(0, -1)));
    EXPECT_FALSE(world.isBlocked(glm::ivec2(1, 1)));
    EXPECT_FALSE(world.isBlocked(glm::ivec2(-1, -1)));
    EXPECT_FALSE(world.isBlocked(glm::ivec2(1, -1)));
    EXPECT_FALSE(world.isBlocked(glm::ivec2(-1, 1)));
}

TEST_F(WorldTest, setSolidObjectAndCheckMap_position1x0)
{
    World world;

    mObjectPosition.set<glm::ivec2>(glm::ivec2(1, 0));

    world.setBlockedMapIfSolid(mObject, true);

    EXPECT_FALSE(world.isBlocked(glm::ivec2(0, 0)));
    EXPECT_TRUE(world.isBlocked(glm::ivec2(1, 0)));
    EXPECT_FALSE(world.isBlocked(glm::ivec2(0, 1)));
    EXPECT_FALSE(world.isBlocked(glm::ivec2(-1, 0)));
    EXPECT_FALSE(world.isBlocked(glm::ivec2(0, -1)));
    EXPECT_FALSE(world.isBlocked(glm::ivec2(1, 1)));
    EXPECT_FALSE(world.isBlocked(glm::ivec2(-1, -1)));
    EXPECT_FALSE(world.isBlocked(glm::ivec2(1, -1)));
    EXPECT_FALSE(world.isBlocked(glm::ivec2(-1, 1)));
}
