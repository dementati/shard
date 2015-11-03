#include "../../../src/logic/jobs/Wander.hpp"
#include "JobTestBase.hpp"

class WanderTest : public JobTestBase
{
};

TEST_F(WanderTest, CanMove_OneSecondMinusOneMs)
{
    Wander wander(mWorld, mOwner, mRng);

    EXPECT_FALSE(wander.canMove(999));
    EXPECT_EQ(999, mOwnerTimeSinceLastStep.get<unsigned int>());
}

TEST_F(WanderTest, CanMove_OneSecond)
{
    Wander wander(mWorld, mOwner, mRng);

    EXPECT_TRUE(wander.canMove(1000));
    EXPECT_EQ(1000, mOwnerTimeSinceLastStep.get<unsigned int>());
}

TEST_F(WanderTest, CanMove_HalfSpeed_OneSecondMinusOneMs)
{
    Wander wander(mWorld, mOwner, mRng);
    setOwnerSpeed(0.5f);

    EXPECT_FALSE(wander.canMove(1999));
    EXPECT_EQ(1999, mOwnerTimeSinceLastStep.get<unsigned int>());
}

TEST_F(WanderTest, CanMove_HalfSpeed_OneSecond)
{
    Wander wander(mWorld, mOwner, mRng);
    setOwnerSpeed(0.5f);

    EXPECT_TRUE(wander.canMove(2000));
    EXPECT_EQ(2000, mOwnerTimeSinceLastStep.get<unsigned int>());
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
    EXPECT_EQ(0, mOwnerTimeSinceLastStep.get<unsigned int>());
}

TEST_F(WanderTest, Execute_HalfSecond_DoubleSpeed_Down)
{
    Wander wander(mWorld, mOwner, mRng);

    EXPECT_CALL(mRng, random(0, 3))
        .WillOnce(Return(1));

    setOwnerSpeed(2.0f);

    wander.execute(500);

    EXPECT_EQ(glm::ivec2(0, 1), mOwnerPosition.get<glm::ivec2>());
    EXPECT_EQ(0, mOwnerTimeSinceLastStep.get<unsigned int>());
}

TEST_F(WanderTest, Execute_Start1x1_OneSecond_Left)
{
    Wander wander(mWorld, mOwner, mRng);

    EXPECT_CALL(mRng, random(0, 3))
        .WillOnce(Return(2));

    setOwnerPosition(glm::ivec2(1, 1));

    wander.execute(1000);

    EXPECT_EQ(glm::ivec2(0, 1), mOwnerPosition.get<glm::ivec2>());
    EXPECT_EQ(0, mOwnerTimeSinceLastStep.get<unsigned int>());
}

TEST_F(WanderTest, Execute_StartMinus1xMinus1_HalfSecond)
{
    Wander wander(mWorld, mOwner, mRng);
    setOwnerPosition(glm::ivec2(-1, -1));
    wander.execute(500);
    EXPECT_EQ(glm::ivec2(-1, -1), mOwnerPosition.get<glm::ivec2>());
    EXPECT_EQ(500, mOwnerTimeSinceLastStep.get<unsigned int>());
}
