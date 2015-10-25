#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../src/logic/Entity.hpp"
#include "../mocks/MockNeed.hpp"

using ::testing::Return; 

typedef ::testing::NiceMock<MockNeed> NiceNeed;

class EntityTest : public ::testing::Test
{
protected:
    std::unique_ptr<Need> createNeed(int intensity)
    {
        std::unique_ptr<NiceNeed> need = std::make_unique<NiceNeed>();
        ON_CALL(*need, getIntensity())
            .WillByDefault(Return(intensity));

        return std::move(need);
    }
};

TEST_F(EntityTest, SelectNeed)
{
    Entity entity("");
    entity.addNeed(createNeed(2));
    entity.addNeed(createNeed(0));
    entity.addNeed(createNeed(3));
    entity.addNeed(createNeed(1));

    EXPECT_EQ(3, entity.selectNeed().getIntensity());
}
