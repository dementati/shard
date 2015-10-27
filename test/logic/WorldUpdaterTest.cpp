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
    MockWorldType world;
    std::vector<std::unique_ptr<Entity>> entities;
    MockNeedType need;
    MockJobType job;
    WorldUpdater updater;

    WorldUpdaterTest()
    :
        updater(world)
    {
        ON_CALL(need, getJob())
            .WillByDefault(ReturnRef(job));

        auto entity = std::make_unique<MockEntityType>();
        ON_CALL(*entity, selectNeed())
            .WillByDefault(ReturnRef(need));
        entities.push_back(std::move(entity));

        ON_CALL(world, getEntities())
            .WillByDefault(ReturnRef(entities));
    }
};

TEST_F(WorldUpdaterTest, SelectedNeedJobGetsExecuted)
{
    EXPECT_CALL(job, execute(0))
        .Times(1);

    updater.update(0);
}
