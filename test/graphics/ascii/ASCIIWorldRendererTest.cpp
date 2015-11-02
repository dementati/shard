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
#include "../../mocks/MockASCIIRenderingSystem.hpp"
#include "../../mocks/MockEntity.hpp"
#include "../../mocks/MockRenderableStore.hpp"
#include "../../mocks/MockWorld.hpp"

using ::testing::Return; 
using ::testing::ReturnRef; 
using ::testing::StrEq; 

using MockRenderableType = ::testing::NiceMock<MockASCIIRenderable>;
using MockRenderableStoreType = ::testing::NiceMock<MockRenderableStore<ASCIIRenderable>>;
using MockRenderingSystemType = ::testing::NiceMock<MockASCIIRenderingSystem>;
using MockWorldType = ::testing::NiceMock<MockWorld>;
using MockEntityType = ::testing::NiceMock<MockEntity>;

class ASCIIWorldRendererTest : public ::testing::Test
{
protected:
    MockRenderableType mRenderable;
    MockRenderingSystemType mRenderingSystem;
    MockRenderableStoreType mStore;
    MockWorldType mWorld;
    Variant mTestRenderableId;
    Variant mTestPosition;
    std::vector<std::unique_ptr<Entity>> mEntities;
    std::vector<std::unique_ptr<GameObject>> mObjects;
    ASCIIWorldRenderer mRenderer;

    ASCIIWorldRendererTest()
    : 
        mTestRenderableId(std::string("test")),
        mTestPosition(glm::ivec2(1, 1)),
        mRenderer(mRenderingSystem, mStore, mWorld)
    {
        ON_CALL(mStore, get(StrEq("test")))
            .WillByDefault(ReturnRef(mRenderable));

        auto entity = std::make_unique<MockEntityType>();
        ON_CALL(*entity, hasAttribute(StrEq("renderableId")))
            .WillByDefault(Return(true));
        ON_CALL(*entity, getAttribute(StrEq("renderableId")))
            .WillByDefault(ReturnRef(mTestRenderableId));
        ON_CALL(*entity, hasAttribute(StrEq("position")))
            .WillByDefault(Return(true));
        ON_CALL(*entity, getAttribute(StrEq("position")))
            .WillByDefault(ReturnRef(mTestPosition));
        mEntities.push_back(std::move(entity));

        ON_CALL(mWorld, getEntities())
            .WillByDefault(ReturnRef(mEntities));

        ON_CALL(mWorld, getObjects())
            .WillByDefault(ReturnRef(mObjects));
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
