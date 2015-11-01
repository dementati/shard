#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../../src/logic/jobs/Idle.hpp"
#include "../../../src/logic/needs/Thirst.hpp"
#include "../../mocks/MockEntity.hpp"
#include "../../mocks/MockWorld.hpp"

using ::testing::Return; 
using ::testing::ReturnRef; 
using ::testing::StrEq; 

using MockEntityType = ::testing::NiceMock<MockEntity>;
using MockWorldType = ::testing::NiceMock<MockWorld>;

class ThirstTest : public ::testing::Test
{
protected:
    MockWorldType mWorld;
    MockEntityType mOwner;

    Variant mOwnerThirst;
    Variant mOwnerPosition;
    Variant mOwnerPerception;

    ThirstTest()
    :
        mOwnerThirst((unsigned int)0),
        mOwnerPosition(glm::ivec2(0, 0)),
        mOwnerPerception((unsigned int)1)
    {
        ON_CALL(mOwner, hasAttribute(StrEq("thirst")))
            .WillByDefault(Return(true));
        ON_CALL(mOwner, getAttribute(StrEq("thirst")))
            .WillByDefault(ReturnRef(mOwnerThirst));
        ON_CALL(mOwner, hasAttribute(StrEq("perception")))
            .WillByDefault(Return(true));
        ON_CALL(mOwner, getAttribute(StrEq("perception")))
            .WillByDefault(ReturnRef(mOwnerPerception));
        ON_CALL(mOwner, hasAttribute(StrEq("position")))
            .WillByDefault(Return(true));
        ON_CALL(mOwner, getAttribute(StrEq("position")))
            .WillByDefault(ReturnRef(mOwnerPosition));
    }

    void setOwnerThirst(unsigned int thirst)
    {
        mOwnerThirst.set<unsigned int>(thirst);
    }
};

TEST_F(ThirstTest, GetIntensity_Zero)
{
    Thirst thirst(mWorld, mOwner);

    EXPECT_EQ(0, thirst.getIntensity());
}

TEST_F(ThirstTest, GetIntensity_One)
{
    Thirst thirst(mWorld, mOwner);

    setOwnerThirst(1);

    EXPECT_EQ(1, thirst.getIntensity());
}

TEST_F(ThirstTest, GetJob_Idle)
{
    Thirst thirst(mWorld, mOwner);

    setOwnerThirst(0);

    dynamic_cast<Idle&>(*thirst.getJob());
}

TEST_F(ThirstTest, GetJob_FindWater)
{
    Thirst thirst(mWorld, mOwner);

    setOwnerThirst(1);

    dynamic_cast<FindWater&>(*thirst.getJob());
}

