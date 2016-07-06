#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../src/logic/WorldUpdater.hpp"
#include "../mocks/MockEntity.hpp"
#include "../mocks/MockGameObject.hpp"
#include "../mocks/MockJob.hpp"
#include "../mocks/MockNeed.hpp"
#include "../mocks/MockWorld.hpp"

using ::testing::Return; 
using ::testing::ReturnRef; 

using MockWorldType = ::testing::NiceMock<MockWorld>;
using MockEntityType = ::testing::NiceMock<MockEntity>;
using MockNeedType = ::testing::NiceMock<MockNeed>;
using MockJobType = ::testing::NiceMock<MockJob>;
using MockGameObjectType = ::testing::NiceMock<MockGameObject>;

class WorldUpdaterTest : public ::testing::Test
{
protected:
    MockWorldType mWorld;
    std::vector<std::unique_ptr<Entity>> mEntities;
    std::vector<std::unique_ptr<GameObject>> mObjects;
    MockNeedType mNeed;
    std::shared_ptr<MockJobType> mJob;
    WorldUpdater mUpdater;
    std::shared_ptr<JobStack> mEntityBackgroundJobStack;
    Variant mEntityBackgroundJobStacks;
    Variant mObjectBackgroundJobs;
    JobStack mJobStack;

    WorldUpdaterTest()
    :
        mJob(std::make_shared<MockJobType>()),
        mUpdater(mWorld),
        mEntityBackgroundJobStack(std::make_shared<JobStack>()),
        mEntityBackgroundJobStacks(std::vector<std::shared_ptr<JobStack>>()),
        mObjectBackgroundJobs(std::vector<std::shared_ptr<Job>>())
    {
        mEntityBackgroundJobStacks.get<std::vector<std::shared_ptr<JobStack>>>()
            .push_back(mEntityBackgroundJobStack);

        ON_CALL(mNeed, getJobStack())
            .WillByDefault(ReturnRef(mJobStack));

        auto entity = std::make_unique<MockEntityType>();
        ON_CALL(*entity, selectNeed())
            .WillByDefault(ReturnRef(mNeed));
        ON_CALL(*entity, hasAttribute("backgroundJobStacks"))
            .WillByDefault(Return(true));
        ON_CALL(*entity, getAttribute("backgroundJobStacks"))
            .WillByDefault(ReturnRef(mEntityBackgroundJobStacks));
        ON_CALL(*entity, hasNeeds())
            .WillByDefault(Return(true));
        mEntities.push_back(std::move(entity));

        ON_CALL(mWorld, getEntities())
            .WillByDefault(ReturnRef(mEntities));

        auto object = std::make_unique<MockGameObjectType>(); 
        ON_CALL(*object, hasAttribute("backgroundJobs"))
            .WillByDefault(Return(true));
        ON_CALL(*object, getAttribute("backgroundJobs"))
            .WillByDefault(ReturnRef(mObjectBackgroundJobs));
        mObjects.push_back(std::move(object));

        ON_CALL(mWorld, getObjects())
            .WillByDefault(ReturnRef(mObjects));
    }

    
};

TEST_F(WorldUpdaterTest, SelectedNeedGetsExecuted)
{
    ON_CALL(dynamic_cast<MockEntityType&>(*mEntities[0]), hasAttribute("backgroundJobStacks"))
        .WillByDefault(Return(false));

    EXPECT_CALL(mNeed, execute(0))
        .Times(1);

    mUpdater.update(0);
}

TEST_F(WorldUpdaterTest, SelectedNeedJobStackTopGetsExecuted)
{
    ON_CALL(dynamic_cast<MockEntityType&>(*mEntities[0]), hasAttribute("backgroundJobStacks"))
        .WillByDefault(Return(false));

    mJobStack.push_back(mJob);

    EXPECT_CALL(*mJob, execute(0))
        .Times(1);

    mUpdater.update(0);
}

TEST_F(WorldUpdaterTest, EntityBackgroundJobGetsExecuted)
{
    auto backgroundJob = std::make_shared<MockJobType>();
    EXPECT_CALL(*backgroundJob, execute(0))
        .Times(1);
    mEntityBackgroundJobStack->push_back(backgroundJob);

    EXPECT_CALL(mNeed, execute(0))
        .Times(1);

    mUpdater.update(0);
}

TEST_F(WorldUpdaterTest, ObjectBackgroundJobGetsExecuted)
{
    auto backgroundJob = std::make_shared<MockJobType>();
    EXPECT_CALL(*backgroundJob, execute(0))
        .Times(1);
    mObjectBackgroundJobs.get<std::vector<std::shared_ptr<Job>>>()
        .push_back(backgroundJob);

    mUpdater.update(0);
}
