#include "../../../src/logic/needs/Thirst.hpp"
#include "../LogicTestBase.hpp"

class ThirstTest : public LogicTestBase
{
};

TEST_F(ThirstTest, GetIntensity_Zero)
{
    Thirst thirst(mWorld, mOwner);

    EXPECT_EQ(0, thirst.getIntensity());
}

TEST_F(ThirstTest, GetIntensity_One)
{
    Thirst thirst(mWorld, mOwner);

    mOwnerThirst.set<unsigned int>(1);

    EXPECT_EQ(1, thirst.getIntensity());
}

TEST_F(ThirstTest, GetJob_Idle)
{
    Thirst thirst(mWorld, mOwner);

    mOwnerThirst.set<unsigned int>(0);

    EXPECT_EQ(0, thirst.getJobStack().size());
}

TEST_F(ThirstTest, GetJob_FindWater)
{
    Thirst thirst(mWorld, mOwner);

    mOwnerThirst.set<unsigned int>(1);

    thirst.execute(0);

    EXPECT_EQ(1, thirst.getJobStack().size());
    dynamic_cast<FindWater*>(thirst.getJobStack().back().get());
}
