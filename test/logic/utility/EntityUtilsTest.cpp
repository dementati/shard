#include <glm/glm.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../../src/logic/utility/EntityUtils.hpp"
#include "../LogicTestBase.hpp"

using ::testing::Return; 
using ::testing::ReturnRef; 
using ::testing::StrEq; 

class EntityUtilsTest : public LogicTestBase
{
protected:
    EntityUtilsTest()
    {
    }
};

TEST_F(EntityUtilsTest, updateStepTimer_Zero)
{
    EntityUtils utils;
    utils.updateStepTimer(mOwner, 0);

    EXPECT_EQ(0, mOwnerTimeSinceLastStep.get<unsigned int>());
}

TEST_F(EntityUtilsTest, updateStepTimer_One)
{
    EntityUtils utils;
    utils.updateStepTimer(mOwner, 1);

    EXPECT_EQ(1, mOwnerTimeSinceLastStep.get<unsigned int>());
}

TEST_F(EntityUtilsTest, updateStepTimer_OneTwo)
{
    EntityUtils utils;
    utils.updateStepTimer(mOwner, 1);
    utils.updateStepTimer(mOwner, 2);

    EXPECT_EQ(3, mOwnerTimeSinceLastStep.get<unsigned int>());
}

TEST_F(EntityUtilsTest, canMove_OneSecondMinusOneMs)
{
    mOwnerTimeSinceLastStep.set<unsigned int>(999);

    EntityUtils utils;

    EXPECT_FALSE(utils.canMove(mOwner));
}

TEST_F(EntityUtilsTest, canMove_OneSecond)
{
    mOwnerTimeSinceLastStep.set<unsigned int>(1000);

    EntityUtils utils;

    EXPECT_TRUE(utils.canMove(mOwner));
}

TEST_F(EntityUtilsTest, canMove_HalfSpeed_TwoSecondsMinusOneMs)
{
    mOwnerTimeSinceLastStep.set<unsigned int>(1999);
    mOwnerSpeed.set<float>(0.5f);

    EntityUtils utils;

    EXPECT_FALSE(utils.canMove(mOwner));
}

TEST_F(EntityUtilsTest, canMove_HalfSpeed_TwoSeconds)
{
    mOwnerTimeSinceLastStep.set<unsigned int>(2000);
    mOwnerSpeed.set<float>(0.5f);

    EntityUtils utils;

    EXPECT_TRUE(utils.canMove(mOwner));
}

TEST_F(EntityUtilsTest, move_position0x0_deltaPosition1x0)
{
    EntityUtils utils;

    utils.move(mWorld, mOwner, glm::ivec2(1, 0));

    EXPECT_EQ(glm::ivec2(1, 0), mOwnerPosition.get<glm::ivec2>());
}

TEST_F(EntityUtilsTest, move_position0x0_deltaPosition0xMinus1)
{
    EntityUtils utils;

    utils.move(mWorld, mOwner, glm::ivec2(0, -1));

    EXPECT_EQ(glm::ivec2(0, -1), mOwnerPosition.get<glm::ivec2>());
}

TEST_F(EntityUtilsTest, move_positionMinus1xMinus1_deltaPosition1x0)
{
    mOwnerPosition.set<glm::ivec2>(glm::ivec2(-1, -1));

    EntityUtils utils;

    utils.move(mWorld, mOwner, glm::ivec2(1, 0));

    EXPECT_EQ(glm::ivec2(0, -1), mOwnerPosition.get<glm::ivec2>());
}

TEST_F(EntityUtilsTest, move_position1x1_deltaPositionMinus1x0)
{
    mOwnerPosition.set<glm::ivec2>(glm::ivec2(1, 1));

    EntityUtils utils;

    utils.move(mWorld, mOwner, glm::ivec2(1, 0));

    EXPECT_EQ(glm::ivec2(2, 1), mOwnerPosition.get<glm::ivec2>());
}

TEST_F(EntityUtilsTest, move_resetTimeSinceLastStep)
{
    mOwnerTimeSinceLastStep.set<unsigned int>(1);

    EntityUtils utils;

    utils.move(mWorld, mOwner, glm::ivec2(1, 0));

    EXPECT_EQ(0, mOwnerTimeSinceLastStep.get<unsigned int>());
}
