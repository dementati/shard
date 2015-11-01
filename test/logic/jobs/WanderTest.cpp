#include <glm/glm.hpp>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../../src/logic/jobs/Wander.hpp"
#include "../../mocks/MockEntity.hpp"
#include "../../mocks/MockRNG.hpp"
#include "../../mocks/MockWorld.hpp"

using ::testing::Return; 
using ::testing::ReturnRef; 
using ::testing::StrEq; 

using MockEntityType = ::testing::NiceMock<MockEntity>;
using MockWorldType = ::testing::NiceMock<MockWorld>;

class WanderTest : public ::testing::Test
{
protected:
    MockWorldType mWorld;
    MockEntityType mOwner;
    MockRNG mRng;

    Variant mOwnerPosition;
    Variant mOwnerPerception;
    glm::ivec2 mDefaultTarget;
    Variant mOwnerTimeSinceLastStep;
    Variant mOwnerSpeed;

    WanderTest()
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

    void setOwnerPosition(glm::ivec2 position)
    {
        mOwnerPosition.set<glm::ivec2>(position);
    }
};

TEST_F(WanderTest, CanMove_OneSecondMinusOneMs)
{
    Wander wander(mWorld, mOwner, mRng);

    EXPECT_FALSE(wander.canMove(999));
}

TEST_F(WanderTest, CanMove_OneSecond)
{
    Wander wander(mWorld, mOwner, mRng);

    EXPECT_TRUE(wander.canMove(1000));
}

TEST_F(WanderTest, CanMove_HalfSpeed_OneSecondMinusOneMs)
{
    Wander wander(mWorld, mOwner, mRng);
    setOwnerSpeed(0.5f);

    EXPECT_FALSE(wander.canMove(1999));
}

TEST_F(WanderTest, CanMove_HalfSpeed_OneSecond)
{
    Wander wander(mWorld, mOwner, mRng);
    setOwnerSpeed(0.5f);

    EXPECT_TRUE(wander.canMove(2000));
}

TEST_F(WanderTest, FindTargetUp)
{
    Wander wander(mWorld, mOwner, mRng);

    EXPECT_CALL(mRng, random(0, 3))
        .WillOnce(Return(0));

    auto target = wander.findTarget();
    ASSERT_NE(nullptr, target);
    EXPECT_EQ(glm::ivec2(0, -1), *target);
}

TEST_F(WanderTest, FindTargetDown)
{
    Wander wander(mWorld, mOwner, mRng);

    EXPECT_CALL(mRng, random(0, 3))
        .WillOnce(Return(1));

    auto target = wander.findTarget();
    ASSERT_NE(nullptr, target);
    EXPECT_EQ(glm::ivec2(0, 1), *target);
}

TEST_F(WanderTest, FindTargetLeft)
{
    Wander wander(mWorld, mOwner, mRng);

    EXPECT_CALL(mRng, random(0, 3))
        .WillOnce(Return(2));

    auto target = wander.findTarget();
    ASSERT_NE(nullptr, target);
    EXPECT_EQ(glm::ivec2(-1, 0), *target);
}

TEST_F(WanderTest, FindTargetRight)
{
    Wander wander(mWorld, mOwner, mRng);

    EXPECT_CALL(mRng, random(0, 3))
        .WillOnce(Return(3));

    auto target = wander.findTarget();
    ASSERT_NE(nullptr, target);
    EXPECT_EQ(glm::ivec2(1, 0), *target);
}

TEST_F(WanderTest, Execute_OneSecond_Up)
{
    Wander wander(mWorld, mOwner, mRng);

    EXPECT_CALL(mRng, random(0, 3))
        .WillOnce(Return(0));

    wander.execute(1000);

    EXPECT_EQ(glm::ivec2(0, -1), mOwnerPosition.get<glm::ivec2>());
}

TEST_F(WanderTest, Execute_HalfSecond_DoubleSpeed_Down)
{
    Wander wander(mWorld, mOwner, mRng);

    EXPECT_CALL(mRng, random(0, 3))
        .WillOnce(Return(1));

    setOwnerSpeed(2.0f);

    wander.execute(500);

    EXPECT_EQ(glm::ivec2(0, 1), mOwnerPosition.get<glm::ivec2>());
}

TEST_F(WanderTest, Execute_Start1x1_OneSecond_Left)
{
    Wander wander(mWorld, mOwner, mRng);

    EXPECT_CALL(mRng, random(0, 3))
        .WillOnce(Return(2));

    setOwnerPosition(glm::ivec2(1, 1));

    wander.execute(1000);

    EXPECT_EQ(glm::ivec2(0, 1), mOwnerPosition.get<glm::ivec2>());
}

TEST_F(WanderTest, Execute_StartMinus1xMinus1_HalfSecond)
{
    Wander wander(mWorld, mOwner, mRng);
    setOwnerPosition(glm::ivec2(-1, -1));
    wander.execute(500);
    EXPECT_EQ(glm::ivec2(-1, -1), mOwnerPosition.get<glm::ivec2>());
}
