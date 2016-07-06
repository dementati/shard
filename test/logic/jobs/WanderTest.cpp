#include "../../../src/logic/jobs/Wander.hpp"
#include "../LogicTestBase.hpp"

class WanderTest : public LogicTestBase
{
};

TEST_F(WanderTest, FindDirectionUp)
{
    Wander wander(mJobStack, mWorld, mOwner, mRng);

    EXPECT_CALL(mRng, random(0, 3))
        .WillOnce(Return(0));

    auto direction = wander.findDirection();
    ASSERT_NE(nullptr, direction);
    EXPECT_EQ(glm::ivec2(0, -1), *direction);
}

TEST_F(WanderTest, FindDirectionDown)
{
    Wander wander(mJobStack, mWorld, mOwner, mRng);

    EXPECT_CALL(mRng, random(0, 3))
        .WillOnce(Return(1));

    auto direction = wander.findDirection();
    ASSERT_NE(nullptr, direction);
    EXPECT_EQ(glm::ivec2(0, 1), *direction);
}

TEST_F(WanderTest, FindDirectionLeft)
{
    Wander wander(mJobStack, mWorld, mOwner, mRng);

    EXPECT_CALL(mRng, random(0, 3))
        .WillOnce(Return(2));

    auto direction = wander.findDirection();
    ASSERT_NE(nullptr, direction);
    EXPECT_EQ(glm::ivec2(-1, 0), *direction);
}

TEST_F(WanderTest, FindDirectionRight)
{
    Wander wander(mJobStack, mWorld, mOwner, mRng);

    EXPECT_CALL(mRng, random(0, 3))
        .WillOnce(Return(3));

    auto direction = wander.findDirection();
    ASSERT_NE(nullptr, direction);
    EXPECT_EQ(glm::ivec2(1, 0), *direction);
}

TEST_F(WanderTest, Execute_JobStackPopped)
{
    auto wander = std::make_shared<Wander>(mJobStack, mWorld, mOwner, mRng);
    mJobStack.push_back(wander);

    wander->execute(0);

    EXPECT_EQ(0, mJobStack.size());
}

TEST_F(WanderTest, Execute_OneSecond_Up)
{
    auto wander = std::make_shared<Wander>(mJobStack, mWorld, mOwner, mRng);
    mJobStack.push_back(wander);

    EXPECT_CALL(mRng, random(0, 3))
        .WillOnce(Return(0));

    wander->execute(1000);

    EXPECT_EQ(glm::ivec2(0, -1), mOwnerPosition.get<glm::ivec2>());
    EXPECT_EQ(0, mOwnerTimeSinceLastStep.get<unsigned int>());
}

TEST_F(WanderTest, Execute_HalfSecond_DoubleSpeed_Down)
{
    auto wander = std::make_shared<Wander>(mJobStack, mWorld, mOwner, mRng);
    mJobStack.push_back(wander);

    EXPECT_CALL(mRng, random(0, 3))
        .WillOnce(Return(1));

    mOwnerSpeed.set<float>(2.0f);

    wander->execute(500);

    EXPECT_EQ(glm::ivec2(0, 1), mOwnerPosition.get<glm::ivec2>());
    EXPECT_EQ(0, mOwnerTimeSinceLastStep.get<unsigned int>());
}

TEST_F(WanderTest, Execute_Start1x1_OneSecond_Left)
{
    auto wander = std::make_shared<Wander>(mJobStack, mWorld, mOwner, mRng);
    mJobStack.push_back(wander);

    EXPECT_CALL(mRng, random(0, 3))
        .WillOnce(Return(2));

    mOwnerPosition.set<glm::ivec2>(glm::ivec2(1, 1));

    wander->execute(1000);

    EXPECT_EQ(glm::ivec2(0, 1), mOwnerPosition.get<glm::ivec2>());
    EXPECT_EQ(0, mOwnerTimeSinceLastStep.get<unsigned int>());
}

TEST_F(WanderTest, Execute_StartMinus1xMinus1_HalfSecond)
{
    auto wander = std::make_shared<Wander>(mJobStack, mWorld, mOwner, mRng);
    mJobStack.push_back(wander);

    mOwnerPosition.set<glm::ivec2>(glm::ivec2(-1, -1));

    wander->execute(500);

    EXPECT_EQ(glm::ivec2(-1, -1), mOwnerPosition.get<glm::ivec2>());
    EXPECT_EQ(500, mOwnerTimeSinceLastStep.get<unsigned int>());
}
