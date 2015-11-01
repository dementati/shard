#include <glm/glm.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../../src/logic/utility/GameObjectUtils.hpp"
#include "../../mocks/MockGameObject.hpp"

using ::testing::Return; 
using ::testing::ReturnRef; 
using ::testing::StrEq; 

using MockGameObjectType = ::testing::NiceMock<MockGameObject>;

class GameObjectUtilsTest : public ::testing::Test
{
protected:
    MockGameObjectType mObject;

    Variant mObjectPosition;
    Variant mObjectPerception;

    GameObjectUtilsTest()
    :
        mObjectPosition(glm::ivec2(0, 0)),
        mObjectPerception((unsigned int)1)
    {
        ON_CALL(mObject, hasAttribute(StrEq("perception")))
            .WillByDefault(Return(true));
        ON_CALL(mObject, getAttribute(StrEq("perception")))
            .WillByDefault(ReturnRef(mObjectPerception));
        ON_CALL(mObject, hasAttribute(StrEq("position")))
            .WillByDefault(Return(true));
        ON_CALL(mObject, getAttribute(StrEq("position")))
            .WillByDefault(ReturnRef(mObjectPosition));
    }

    void setObjectPosition(glm::ivec2 position)
    {
        mObjectPosition.set<glm::ivec2>(position);
    }

    void setObjectPerception(unsigned int perception)
    {
        mObjectPerception.set<unsigned int>(perception);
    }
};

TEST_F(GameObjectUtilsTest, GetPerceptionBox_Perception1)
{
    Box box = GameObjectUtils::getPerceptionBox(mObject);

    EXPECT_EQ(glm::ivec2(-1, -1), box.getPosition());
    EXPECT_EQ(glm::uvec2(3, 3), box.getDimensions());
}

TEST_F(GameObjectUtilsTest, GetPerceptionBox_Perception2)
{
    setObjectPerception(2);

    Box box = GameObjectUtils::getPerceptionBox(mObject);

    EXPECT_EQ(glm::ivec2(-2, -2), box.getPosition());
    EXPECT_EQ(glm::uvec2(5, 5), box.getDimensions());
}
