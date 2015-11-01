#include <glm/glm.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../../src/logic/jobs/Move.hpp"
#include "../../mocks/MockEntity.hpp"
#include "../../mocks/MockWorld.hpp"

using ::testing::Return; 
using ::testing::ReturnRef; 
using ::testing::StrEq; 

using MockEntityType = ::testing::NiceMock<MockEntity>;
using MockWorldType = ::testing::NiceMock<MockWorld>;

class MoveTest : public ::testing::Test
{
protected:
    MockWorldType mWorld;
    MockEntityType mOwner;

    Variant mOwnerPosition;
    Variant mOwnerPerception;
    glm::ivec2 mDefaultTarget;
    Variant mOwnerTimeSinceLastStep;
    Variant mOwnerSpeed;

    MoveTest()
    :
        mOwnerPosition(glm::ivec2(0, 0)),
        mOwnerPerception((unsigned int)1),
        mDefaultTarget(glm::ivec2(0, 1)),
        mOwnerTimeSinceLastStep((unsigned int)0),
        mOwnerSpeed(1.0f)
    {
        ON_CALL(mOwner, hasAttribute(StrEq("perception")))
            .WillByDefault(Return(true));
        ON_CALL(mOwner, getAttribute(StrEq("perception")))
            .WillByDefault(ReturnRef(mOwnerPerception));
        ON_CALL(mOwner, hasAttribute(StrEq("position")))
            .WillByDefault(Return(true));
        ON_CALL(mOwner, getAttribute(StrEq("position")))
            .WillByDefault(ReturnRef(mOwnerPosition));
        ON_CALL(mOwner, hasAttribute(StrEq("timeSinceLastStep")))
            .WillByDefault(Return(true));
        ON_CALL(mOwner, getAttribute(StrEq("timeSinceLastStep")))
            .WillByDefault(ReturnRef(mOwnerTimeSinceLastStep));
        ON_CALL(mOwner, hasAttribute(StrEq("speed")))
            .WillByDefault(Return(true));
        ON_CALL(mOwner, getAttribute(StrEq("speed")))
            .WillByDefault(ReturnRef(mOwnerSpeed));
    }

    void setOwnerSpeed(float speed)
    {
        mOwnerSpeed.set<float>(speed);
    }

    void setOwnerPerception(unsigned int perception)
    {
        mOwnerPerception.set<unsigned int>(perception);
    }
};

TEST_F(MoveTest, GetStepCount_TimeZero)
{
    Move move(mWorld, mOwner, mDefaultTarget);
   
    EXPECT_EQ(0, move.getStepCount(0));
    EXPECT_EQ(0, mOwnerTimeSinceLastStep.get<unsigned int>());
}

TEST_F(MoveTest, GetStepCount_TimeOneSecond)
{
    Move move(mWorld, mOwner, mDefaultTarget);
   
    EXPECT_EQ(1, move.getStepCount(1000));
    EXPECT_EQ(1000, mOwnerTimeSinceLastStep.get<unsigned int>());
}

TEST_F(MoveTest, GetStepCount_SpeedTwo_TimeHalfSecond)
{
    Move move(mWorld, mOwner, mDefaultTarget);
    setOwnerSpeed(2);
   
    EXPECT_EQ(1, move.getStepCount(500));
    EXPECT_EQ(500, mOwnerTimeSinceLastStep.get<unsigned int>());
}

TEST_F(MoveTest, GetStepCount_SpeedHalf_TimeTwoSeconds)
{
    Move move(mWorld, mOwner, mDefaultTarget);
    setOwnerSpeed(0.5);
   
    EXPECT_EQ(1, move.getStepCount(2000));
    EXPECT_EQ(2000, mOwnerTimeSinceLastStep.get<unsigned int>());
}

TEST_F(MoveTest, GetStepCount_SpeedHalf_TimeTwoSecondsMinusOneMs)
{
    Move move(mWorld, mOwner, mDefaultTarget);
    setOwnerSpeed(0.5);
   
    EXPECT_EQ(0, move.getStepCount(1999));
    EXPECT_EQ(1999, mOwnerTimeSinceLastStep.get<unsigned int>());
}

TEST_F(MoveTest, IsBlocked)
{
    Move move(mWorld, mOwner, mDefaultTarget);
   
    EXPECT_FALSE(move.isBlocked(glm::ivec2(0, 0)));
    EXPECT_FALSE(move.isBlocked(glm::ivec2(1, 0)));
    EXPECT_FALSE(move.isBlocked(glm::ivec2(0, 1)));
    EXPECT_FALSE(move.isBlocked(glm::ivec2(-1, 0)));
    EXPECT_FALSE(move.isBlocked(glm::ivec2(0, -1)));
}

TEST_F(MoveTest, Execute_TimeOneSecond_Target1x0)
{
    Move move(mWorld, mOwner, glm::ivec2(1, 0));
    move.execute(1000);
    EXPECT_EQ(glm::ivec2(1, 0), mOwnerPosition.get<glm::ivec2>());
    EXPECT_EQ(0, mOwnerTimeSinceLastStep.get<unsigned int>());
}

TEST_F(MoveTest, Execute_TimeOneSecondMinusOneMs_Target1x0)
{
    Move move(mWorld, mOwner, glm::ivec2(1, 0));
    move.execute(999);
    EXPECT_EQ(glm::ivec2(0, 0), mOwnerPosition.get<glm::ivec2>());
    EXPECT_EQ(999, mOwnerTimeSinceLastStep.get<unsigned int>());
}

TEST_F(MoveTest, ExecuteTwice_Time500MsEach_Target1x0)
{
    Move move(mWorld, mOwner, glm::ivec2(1, 0));
    move.execute(500);
    EXPECT_EQ(500, mOwnerTimeSinceLastStep.get<unsigned int>());
    move.execute(500);
    EXPECT_EQ(glm::ivec2(1, 0), mOwnerPosition.get<glm::ivec2>());
    EXPECT_EQ(0, mOwnerTimeSinceLastStep.get<unsigned int>());
}

TEST_F(MoveTest, Execute_TimeOneSecond_Target2x0)
{
    setOwnerPerception(2);
    Move move(mWorld, mOwner, glm::ivec2(2, 0));
    move.execute(1000);
    EXPECT_EQ(glm::ivec2(1, 0), mOwnerPosition.get<glm::ivec2>());
    EXPECT_EQ(0, mOwnerTimeSinceLastStep.get<unsigned int>());
}

TEST_F(MoveTest, ExecuteTwice_TimeOneSecond_Target2x0)
{
    setOwnerPerception(2);
    Move move(mWorld, mOwner, glm::ivec2(2, 0));
    move.execute(1000);
    EXPECT_EQ(glm::ivec2(1, 0), mOwnerPosition.get<glm::ivec2>());
    EXPECT_EQ(0, mOwnerTimeSinceLastStep.get<unsigned int>());
    move.execute(1000);
    EXPECT_EQ(glm::ivec2(2, 0), mOwnerPosition.get<glm::ivec2>());
    EXPECT_EQ(0, mOwnerTimeSinceLastStep.get<unsigned int>());
}

TEST_F(MoveTest, Execute_TimeTwoSeconds_Target2x0)
{
    setOwnerPerception(2);
    Move move(mWorld, mOwner, glm::ivec2(2, 0));
    move.execute(2000);
    EXPECT_EQ(glm::ivec2(2, 0), mOwnerPosition.get<glm::ivec2>());
    EXPECT_EQ(0, mOwnerTimeSinceLastStep.get<unsigned int>());
}

TEST_F(MoveTest, Execute_TimeTwoSeconds_TargetMinus1xMinus1)
{
    Move move(mWorld, mOwner, glm::ivec2(-1, -1));
    move.execute(2000);
    EXPECT_EQ(glm::ivec2(-1, -1), mOwnerPosition.get<glm::ivec2>());
    EXPECT_EQ(0, mOwnerTimeSinceLastStep.get<unsigned int>());
}
