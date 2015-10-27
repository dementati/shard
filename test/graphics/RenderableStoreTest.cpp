#include <memory>

#include <gtest/gtest.h>

#include "../../src/graphics/Renderable.hpp"
#include "../../src/graphics/RenderableStore.hpp"
#include "../mocks/MockRenderable.hpp"

using ::testing::Return; 

using NiceRenderable = ::testing::NiceMock<MockRenderable>;

class RenderableStoreTest : public ::testing::Test
{
};

TEST_F(RenderableStoreTest, AddAndGetRenderable)
{
    RenderableStore<Renderable> store;
    std::unique_ptr<NiceRenderable> renderable = std::make_unique<NiceRenderable>();
    ON_CALL(*renderable, getId())
        .WillByDefault(Return(1));

    store.add("test", std::move(renderable));
    NiceRenderable& acquiredRenderable = dynamic_cast<NiceRenderable&>(store.get("test"));

    EXPECT_EQ(1, acquiredRenderable.getId());
}
