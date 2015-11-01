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
    Variant mDefaultPerception;
    glm::ivec2 mDefaultTarget;
    Variant mDefaultTimeSinceLastStep;
    Variant mDefaultSpeed;

    MoveTest()
    :
        mOwnerPosition(glm::ivec2(0, 0)),
        mDefaultPerception((unsigned int)1),
        mDefaultTarget(glm::ivec2(0, 1)),
        mDefaultTimeSinceLastStep((unsigned int)0),
        mDefaultSpeed(1.0f)
    {
        ON_CALL(mOwner, hasAttribute(StrEq("perception")))
            .WillByDefault(Return(true));
        ON_CALL(mOwner, getAttribute(StrEq("perception")))
            .WillByDefault(ReturnRef(mDefaultPerception));
        ON_CALL(mOwner, hasAttribute(StrEq("position")))
            .WillByDefault(Return(true));
        ON_CALL(mOwner, getAttribute(StrEq("position")))
            .WillByDefault(ReturnRef(mOwnerPosition));
        ON_CALL(mOwner, hasAttribute(StrEq("timeSinceLastStep")))
            .WillByDefault(Return(true));
        ON_CALL(mOwner, getAttribute(StrEq("timeSinceLastStep")))
            .WillByDefault(ReturnRef(mDefaultTimeSinceLastStep));
        ON_CALL(mOwner, hasAttribute(StrEq("speed")))
            .WillByDefault(Return(true));
        ON_CALL(mOwner, getAttribute(StrEq("speed")))
            .WillByDefault(ReturnRef(mDefaultSpeed));
    }

    void setOwnerSpeed(float speed)
    {
        mDefaultSpeed.set<float>(speed);
    }

    void setOwnerPerception(unsigned int perception)
    {
        mDefaultPerception.set<unsigned int>(perception);
    }
};

TEST_F(MoveTest, GetPerceptionBox_Perception1)
{
    Move move(mWorld, mOwner, mDefaultTarget);
    Box box = move.getPerceptionBox();

    EXPECT_EQ(glm::ivec2(-1, -1), box.getPosition());
    EXPECT_EQ(glm::uvec2(3, 3), box.getDimensions());
}

TEST_F(MoveTest, GetPerceptionBox_Perception2)
{
    Move move(mWorld, mOwner, mDefaultTarget);
    setOwnerPerception(2);

    Box box = move.getPerceptionBox();

    EXPECT_EQ(glm::ivec2(-2, -2), box.getPosition());
    EXPECT_EQ(glm::uvec2(5, 5), box.getDimensions());
}

TEST_F(MoveTest, GetStepCount_TimeZero)
{
    Move move(mWorld, mOwner, mDefaultTarget);
   
    EXPECT_EQ(0, move.getStepCount(0));
}

TEST_F(MoveTest, GetStepCount_TimeOneSecond)
{
    Move move(mWorld, mOwner, mDefaultTarget);
   
    EXPECT_EQ(1, move.getStepCount(1000));
}

TEST_F(MoveTest, GetStepCount_SpeedTwo_TimeHalfSecond)
{
    Move move(mWorld, mOwner, mDefaultTarget);
    setOwnerSpeed(2);
   
    EXPECT_EQ(1, move.getStepCount(500));
}

TEST_F(MoveTest, GetStepCount_SpeedHalf_TimeTwoSeconds)
{
    Move move(mWorld, mOwner, mDefaultTarget);
    setOwnerSpeed(0.5);
   
    EXPECT_EQ(1, move.getStepCount(2000));
}

TEST_F(MoveTest, GetStepCount_SpeedHalf_TimeTwoSecondsMinusOneMs)
{
    Move move(mWorld, mOwner, mDefaultTarget);
    setOwnerSpeed(0.5);
   
    EXPECT_EQ(0, move.getStepCount(1999));
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
}

TEST_F(MoveTest, Execute_TimeOneSecondMinusOneMs_Target1x0)
{
    Move move(mWorld, mOwner, glm::ivec2(1, 0));
    move.execute(999);
    EXPECT_EQ(glm::ivec2(0, 0), mOwnerPosition.get<glm::ivec2>());
}

TEST_F(MoveTest, ExecuteTwice_Time500MsEach_Target1x0)
{
    Move move(mWorld, mOwner, glm::ivec2(1, 0));
    move.execute(500);
    move.execute(500);
    EXPECT_EQ(glm::ivec2(1, 0), mOwnerPosition.get<glm::ivec2>());
}

TEST_F(MoveTest, Execute_TimeOneSecond_Target2x0)
{
    setOwnerPerception(2);
    Move move(mWorld, mOwner, glm::ivec2(2, 0));
    move.execute(1000);
    EXPECT_EQ(glm::ivec2(1, 0), mOwnerPosition.get<glm::ivec2>());
}

TEST_F(MoveTest, ExecuteTwice_TimeOneSecond_Target2x0)
{
    setOwnerPerception(2);
    Move move(mWorld, mOwner, glm::ivec2(2, 0));
    move.execute(1000);
    EXPECT_EQ(glm::ivec2(1, 0), mOwnerPosition.get<glm::ivec2>());
    move.execute(1000);
    EXPECT_EQ(glm::ivec2(2, 0), mOwnerPosition.get<glm::ivec2>());
}

TEST_F(MoveTest, Execute_TimeTwoSeconds_Target2x0)
{
    setOwnerPerception(2);
    Move move(mWorld, mOwner, glm::ivec2(2, 0));
    move.execute(2000);
    EXPECT_EQ(glm::ivec2(2, 0), mOwnerPosition.get<glm::ivec2>());
}

TEST_F(MoveTest, Execute_TimeTwoSeconds_TargetMinus1xMinus1)
{
    Move move(mWorld, mOwner, glm::ivec2(-1, -1));
    move.execute(2000);
    EXPECT_EQ(glm::ivec2(-1, -1), mOwnerPosition.get<glm::ivec2>());
}
