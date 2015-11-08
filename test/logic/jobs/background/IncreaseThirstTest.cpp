#include "../../../../src/logic/jobs/background/IncreaseThirst.hpp"
#include "../../LogicTestBase.hpp"

class IncreaseThirstTest : public LogicTestBase
{
public:
    Variant mTimer;
    
    IncreaseThirstTest()
    :
        mTimer((unsigned int)0)
    {
        ON_CALL(mOwner, hasAttribute("IncreaseThirst.timer"))
            .WillByDefault(Return(true));
        ON_CALL(mOwner, getAttribute("IncreaseThirst.timer"))
            .WillByDefault(ReturnRef(mTimer));
    }
};

TEST_F(IncreaseThirstTest, Execute_SetTimerIfNoTimerSet)
{
    ON_CALL(mOwner, hasAttribute("IncreaseThirst.timer"))
        .WillByDefault(Return(false));

    IncreaseThirst increaseThirst(mWorld, mOwner, 1);

    EXPECT_CALL(mOwner, addAttribute(std::string("IncreaseThirst.timer"), _))
        .Times(1);

    increaseThirst.execute(0);
}

TEST_F(IncreaseThirstTest, Execute_DontSetTimerIfTimerSet)
{
    IncreaseThirst increaseThirst(mWorld, mOwner, 1);

    EXPECT_CALL(mOwner, addAttribute(std::string("IncreaseThirst.timer"), _))
        .Times(0);

    increaseThirst.execute(0);
}

TEST_F(IncreaseThirstTest, Execute_IncreaseOne_ZeroTime)
{
    IncreaseThirst increaseThirst(mWorld, mOwner, 1);

    increaseThirst.execute(0);

    EXPECT_EQ(0, mTimer.get<unsigned int>());
    EXPECT_EQ(0, mOwnerThirst.get<unsigned int>());
}

TEST_F(IncreaseThirstTest, Execute_IncreaseOne_TimeOneMinusOneMs)
{
    IncreaseThirst increaseThirst(mWorld, mOwner, 1);

    increaseThirst.execute(999);

    EXPECT_EQ(999, mTimer.get<unsigned int>());
    EXPECT_EQ(0, mOwnerThirst.get<unsigned int>());
}

TEST_F(IncreaseThirstTest, Execute_IncreaseOne_TimeOneSecond)
{
    IncreaseThirst increaseThirst(mWorld, mOwner, 1);

    increaseThirst.execute(1000);

    EXPECT_EQ(0, mTimer.get<unsigned int>());
    EXPECT_EQ(1, mOwnerThirst.get<unsigned int>());
}

TEST_F(IncreaseThirstTest, Execute_TimerAddsUp)
{
    IncreaseThirst increaseThirst(mWorld, mOwner, 1);

    increaseThirst.execute(1);
    increaseThirst.execute(1);

    EXPECT_EQ(2, mTimer.get<unsigned int>());
    EXPECT_EQ(0, mOwnerThirst.get<unsigned int>());
}

TEST_F(IncreaseThirstTest, Execute_IncreaseTwo_TimeOneSecond)
{
    IncreaseThirst increaseThirst(mWorld, mOwner, 2);

    increaseThirst.execute(1000);

    EXPECT_EQ(0, mTimer.get<unsigned int>());
    EXPECT_EQ(2, mOwnerThirst.get<unsigned int>());
}

TEST_F(IncreaseThirstTest, Execute_IncreaseOneHalf_TimeOneSecond)
{
    IncreaseThirst increaseThirst(mWorld, mOwner, 0.5f);

    increaseThirst.execute(1000);

    EXPECT_EQ(1000, mTimer.get<unsigned int>());
    EXPECT_EQ(0, mOwnerThirst.get<unsigned int>());
}

TEST_F(IncreaseThirstTest, Execute_IncreaseOne_TimeOneSecondPlusOneMs)
{
    IncreaseThirst increaseThirst(mWorld, mOwner, 1);

    increaseThirst.execute(1001);

    EXPECT_EQ(1, mTimer.get<unsigned int>());
    EXPECT_EQ(1, mOwnerThirst.get<unsigned int>());
}

TEST_F(IncreaseThirstTest, Execute_OwnerDies_MaxThirst0_ThirstBecomes1)
{
    IncreaseThirst increaseThirst(mWorld, mOwner, 1);

    EXPECT_CALL(mOwner, addAttribute("dead", _));

    increaseThirst.execute(1000);
}

TEST_F(IncreaseThirstTest, Execute_OwnerDoesntDie_MaxThirst1_ThirstBecomes1)
{
    mOwnerMaxThirst.set<unsigned int>(1);

    IncreaseThirst increaseThirst(mWorld, mOwner, 1);

    EXPECT_CALL(mOwner, addAttribute("dead", _))
        .Times(0);

    increaseThirst.execute(1000);
}
