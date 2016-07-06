#include "../../../src/logic/jobs/Move.hpp"
#include "../LogicTestBase.hpp"

class MoveTest : public LogicTestBase
{
};

TEST_F(MoveTest, IsBlocked)
{
    Move move(mJobStack, mWorld, mOwner, mDefaultTarget);
   
    EXPECT_FALSE(move.isBlocked(glm::ivec2(0, 0)));
    EXPECT_FALSE(move.isBlocked(glm::ivec2(1, 0)));
    EXPECT_FALSE(move.isBlocked(glm::ivec2(0, 1)));
    EXPECT_FALSE(move.isBlocked(glm::ivec2(-1, 0)));
    EXPECT_FALSE(move.isBlocked(glm::ivec2(0, -1)));
}

TEST_F(MoveTest, Execute_TimeOneSecond_Target1x0)
{
    auto move = std::make_shared<Move>(mJobStack, mWorld, mOwner, glm::ivec2(1, 0));
    mJobStack.push_back(move);

    move->execute(1000);
    EXPECT_EQ(glm::ivec2(1, 0), mOwnerPosition.get<glm::ivec2>());
    EXPECT_EQ(0, mOwnerTimeSinceLastStep.get<unsigned int>());
}

TEST_F(MoveTest, Execute_TimeOneSecondMinusOneMs_Target1x0)
{
    auto move = std::make_shared<Move>(mJobStack, mWorld, mOwner, glm::ivec2(1, 0));
    mJobStack.push_back(move);

    move->execute(999);
    EXPECT_EQ(glm::ivec2(0, 0), mOwnerPosition.get<glm::ivec2>());
    EXPECT_EQ(999, mOwnerTimeSinceLastStep.get<unsigned int>());
}

TEST_F(MoveTest, ExecuteTwice_Time500MsEach_Target1x0)
{
    auto move = std::make_shared<Move>(mJobStack, mWorld, mOwner, glm::ivec2(1, 0));
    mJobStack.push_back(move);

    move->execute(500);
    EXPECT_EQ(500, mOwnerTimeSinceLastStep.get<unsigned int>());
    move->execute(500);
    EXPECT_EQ(glm::ivec2(1, 0), mOwnerPosition.get<glm::ivec2>());
    EXPECT_EQ(0, mOwnerTimeSinceLastStep.get<unsigned int>());
}

TEST_F(MoveTest, Execute_TimeOneSecond_Target2x0)
{
    mOwnerPerception.set<unsigned int>(2);
    auto move = std::make_shared<Move>(mJobStack, mWorld, mOwner, glm::ivec2(2, 0));
    mJobStack.push_back(move);

    move->execute(1000);
    EXPECT_EQ(glm::ivec2(1, 0), mOwnerPosition.get<glm::ivec2>());
    EXPECT_EQ(0, mOwnerTimeSinceLastStep.get<unsigned int>());
}

TEST_F(MoveTest, ExecuteTwice_TimeOneSecond_Target2x0)
{
    mOwnerPerception.set<unsigned int>(2);
    auto move = std::make_shared<Move>(mJobStack, mWorld, mOwner, glm::ivec2(2, 0));
    mJobStack.push_back(move);

    move->execute(1000);
    EXPECT_EQ(glm::ivec2(1, 0), mOwnerPosition.get<glm::ivec2>());
    EXPECT_EQ(0, mOwnerTimeSinceLastStep.get<unsigned int>());
    move->execute(1000);
    EXPECT_EQ(glm::ivec2(2, 0), mOwnerPosition.get<glm::ivec2>());
    EXPECT_EQ(0, mOwnerTimeSinceLastStep.get<unsigned int>());
}

TEST_F(MoveTest, Execute_TimeTwoSeconds_Target2x0)
{
    mOwnerPerception.set<unsigned int>(2);
    auto move = std::make_shared<Move>(mJobStack, mWorld, mOwner, glm::ivec2(2, 0));
    mJobStack.push_back(move);

    move->execute(1000);
    move->execute(1000);
    EXPECT_EQ(glm::ivec2(2, 0), mOwnerPosition.get<glm::ivec2>());
    EXPECT_EQ(0, mOwnerTimeSinceLastStep.get<unsigned int>());
}

TEST_F(MoveTest, Execute_TimeTwoSeconds_TargetMinus1xMinus1)
{
    auto move = std::make_shared<Move>(mJobStack, mWorld, mOwner, glm::ivec2(-1, -1));
    mJobStack.push_back(move);

    move->execute(1000);
    move->execute(1000);
    EXPECT_EQ(glm::ivec2(-1, -1), mOwnerPosition.get<glm::ivec2>());
    EXPECT_EQ(0, mOwnerTimeSinceLastStep.get<unsigned int>());
}

TEST_F(MoveTest, Execute_TargetIsBlocked)
{
    ON_CALL(mWorld, isBlocked(glm::ivec2(1, 0)))
        .WillByDefault(Return(true));

    auto move = std::make_shared<Move>(mJobStack, mWorld, mOwner, glm::ivec2(1, 0));
    mJobStack.push_back(move);

    move->execute(1000);
    EXPECT_EQ(glm::ivec2(0, 0), mOwnerPosition.get<glm::ivec2>());
}
