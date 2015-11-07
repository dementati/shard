#include "../../../../src/logic/jobs/background/PlayerControl.hpp"
#include "../../../mocks/MockEntityUtils.hpp"
#include "../../../mocks/MockInputSystem.hpp"
#include "../JobTestBase.hpp"

using MockEntityUtilsType = ::testing::NiceMock<MockEntityUtils>;
using MockInputSystemType = ::testing::NiceMock<MockInputSystem>;

class PlayerControlTest : public JobTestBase
{
public:
    MockInputSystemType mInput;

    PlayerControlTest()
    {
    }
};

TEST_F(PlayerControlTest, Construct_SetWorldCameraPosition_PlayerPositionZero)
{
    PlayerControl playerControl(mInput, mWorld, mOwner);

    EXPECT_EQ(glm::ivec2(-32, -18), mWorldCameraPosition.get<glm::ivec2>());
}

TEST_F(PlayerControlTest, Construct_SetWorldCameraPosition_PlayerPosition1x1)
{
    mOwnerPosition.set<glm::ivec2>(glm::ivec2(1, 1));

    PlayerControl playerControl(mInput, mWorld, mOwner);

    EXPECT_EQ(glm::ivec2(-31, -17), mWorldCameraPosition.get<glm::ivec2>());
}

TEST_F(PlayerControlTest, Construct_SetWorldCameraPosition_PlayerPositionMinus1xMinus1)
{
    mOwnerPosition.set<glm::ivec2>(glm::ivec2(-1, -1));

    PlayerControl playerControl(mInput, mWorld, mOwner);

    EXPECT_EQ(glm::ivec2(-33, -19), mWorldCameraPosition.get<glm::ivec2>());
}
