#include <memory>

#include <glm/glm.hpp>
#include <gtest/gtest.h>

#include "../../../src/graphics/ascii/ASCIIWorldRenderer.hpp"
#include "../../../src/graphics/ascii/ASCIIRenderable.hpp"
#include "../../../src/graphics/CharBitmap.hpp"
#include "../../../src/graphics/RenderableStore.hpp"
#include "../../../src/logic/Entity.hpp"
#include "../../../src/logic/World.hpp"
#include "../../mocks/MockASCIIRenderable.hpp"
#include "../../mocks/MockEntity.hpp"
#include "../../mocks/MockRenderableStore.hpp"
#include "../../mocks/MockWorld.hpp"

using ::testing::Return; 
using ::testing::ReturnRef; 
using ::testing::StrEq; 

using MockRenderableType = ::testing::NiceMock<MockASCIIRenderable>;
using MockRenderableStoreType = ::testing::NiceMock<MockRenderableStore<ASCIIRenderable>>;
using MockWorldType = ::testing::NiceMock<MockWorld>;
using MockEntityType = ::testing::NiceMock<MockEntity>;

class ASCIIWorldRendererTest : public ::testing::Test
{
protected:
    MockRenderableType mRenderable;
    MockRenderableStoreType mStore;
    MockWorldType mWorld;
    std::vector<std::unique_ptr<Entity>> mEntities;
    ASCIIWorldRenderer mRenderer;

    ASCIIWorldRendererTest()
    : 
        mRenderer(mStore, mWorld)
    {
        ON_CALL(mStore, get(StrEq("test")))
            .WillByDefault(ReturnRef(mRenderable));

        auto entity = std::make_unique<MockEntityType>();
        ON_CALL(*entity, getRenderableId())
            .WillByDefault(Return(std::string("test")));
        ON_CALL(*entity, getPosition())
            .WillByDefault(Return(glm::ivec2(1, 1)));
        mEntities.push_back(std::move(entity));

        ON_CALL(mWorld, getEntities())
            .WillByDefault(ReturnRef(mEntities));
    }
};

TEST_F(ASCIIWorldRendererTest, SingleEntityWorld_RenderableGetsDrawn)
{
    EXPECT_CALL(mRenderable, draw())
        .Times(1);

    mRenderer.render();
}

TEST_F(ASCIIWorldRendererTest, SingleEntityWorld_RenderableHasPositionSet)
{
    EXPECT_CALL(mRenderable, setPosition(glm::ivec2(1,1)))
        .Times(1);

    mRenderer.render();
}
