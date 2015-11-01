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
    Variant mDefaultPerception;
    glm::ivec2 mDefaultTarget;
    Variant mDefaultTimeSinceLastStep;
    Variant mDefaultSpeed;

    WanderTest()
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

TEST_F(WanderTest, FindTarget)
{
    Wander wander(mWorld, mOwner, mRng);

    EXPECT_CALL(mRng, random(0, 3))
        .WillOnce(Return(0));

    auto target = wander.findTarget();
    ASSERT_NE(nullptr, target);
    EXPECT_EQ(glm::ivec2(0, -1), *target);
}
