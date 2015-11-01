#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../src/logic/WorldUpdater.hpp"
#include "../mocks/MockEntity.hpp"
#include "../mocks/MockJob.hpp"
#include "../mocks/MockNeed.hpp"
#include "../mocks/MockWorld.hpp"

using ::testing::Return; 
using ::testing::ReturnRef; 

using MockWorldType = ::testing::NiceMock<MockWorld>;
using MockEntityType = ::testing::NiceMock<MockEntity>;
using MockNeedType = ::testing::NiceMock<MockNeed>;
using MockJobType = ::testing::NiceMock<MockJob>;

class WorldUpdaterTest : public ::testing::Test
{
protected:
    MockWorldType mWorld;
    std::vector<std::unique_ptr<Entity>> mEntities;
    MockNeedType mNeed;
    WorldUpdater mUpdater;

    WorldUpdaterTest()
    :
        mUpdater(mWorld)
    {
        auto entity = std::make_unique<MockEntityType>();
        ON_CALL(*entity, selectNeed())
            .WillByDefault(ReturnRef(mNeed));
        mEntities.push_back(std::move(entity));

        ON_CALL(mWorld, getEntities())
            .WillByDefault(ReturnRef(mEntities));
    }
};

TEST_F(WorldUpdaterTest, SelectedNeedJobGetsExecuted)
{
    EXPECT_CALL(mNeed, execute(0))
        .Times(1);

    mUpdater.update(0);
}
