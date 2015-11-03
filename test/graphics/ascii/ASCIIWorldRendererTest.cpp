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
#include "../../mocks/MockGameObject.hpp"
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
using MockGameObjectType = ::testing::NiceMock<MockGameObject>;

class ASCIIWorldRendererTest : public ::testing::Test
{
protected:
    MockRenderableType mEntityRenderable;
    MockRenderableType mObjectRenderable;
    MockRenderingSystemType mRenderingSystem;
    MockRenderableStoreType mStore;
    MockWorldType mWorld;
    Variant mEntityRenderableId;
    Variant mObjectRenderableId;
    Variant mEntityPosition;
    Variant mObjectPosition;
    std::vector<std::unique_ptr<Entity>> mEntities;
    std::vector<std::unique_ptr<GameObject>> mObjects;
    ASCIIWorldRenderer mRenderer;

    ASCIIWorldRendererTest()
    : 
        mEntityRenderableId(std::string("entity")),
        mObjectRenderableId(std::string("object")),
        mEntityPosition(glm::ivec2(1, 1)),
        mObjectPosition(glm::ivec2(1, 1)),
        mRenderer(mRenderingSystem, mStore, mWorld)
    {
        ON_CALL(mStore, get(StrEq(mEntityRenderableId.get<std::string>())))
            .WillByDefault(ReturnRef(mEntityRenderable));
        ON_CALL(mStore, get(StrEq(mObjectRenderableId.get<std::string>())))
            .WillByDefault(ReturnRef(mObjectRenderable));

        auto entity = std::make_unique<MockEntityType>();
        ON_CALL(*entity, hasAttribute(StrEq("renderableId")))
            .WillByDefault(Return(true));
        ON_CALL(*entity, getAttribute(StrEq("renderableId")))
            .WillByDefault(ReturnRef(mEntityRenderableId));
        ON_CALL(*entity, hasAttribute(StrEq("position")))
            .WillByDefault(Return(true));
        ON_CALL(*entity, getAttribute(StrEq("position")))
            .WillByDefault(ReturnRef(mEntityPosition));
        mEntities.push_back(std::move(entity));

        auto object = std::make_unique<MockGameObjectType>();
        ON_CALL(*object, hasAttribute(StrEq("renderableId")))
            .WillByDefault(Return(true));
        ON_CALL(*object, getAttribute(StrEq("renderableId")))
            .WillByDefault(ReturnRef(mObjectRenderableId));
        ON_CALL(*object, hasAttribute(StrEq("position")))
            .WillByDefault(Return(true));
        ON_CALL(*object, getAttribute(StrEq("position")))
            .WillByDefault(ReturnRef(mObjectPosition));
        mObjects.push_back(std::move(object)); 

        ON_CALL(mWorld, getEntities())
            .WillByDefault(ReturnRef(mEntities));

        ON_CALL(mWorld, getObjects())
            .WillByDefault(ReturnRef(mObjects));
    }
};

TEST_F(ASCIIWorldRendererTest, ObjectRenderableGetsDrawn)
{
    EXPECT_CALL(mObjectRenderable, draw())
        .Times(1);

    mRenderer.render();
}

TEST_F(ASCIIWorldRendererTest, ObjectRenderableHasPositionSet)
{
    EXPECT_CALL(mObjectRenderable, setPosition(glm::ivec2(1,1)))
        .Times(1);

    mRenderer.render();
}

TEST_F(ASCIIWorldRendererTest, EntityRenderableGetsDrawn)
{
    EXPECT_CALL(mEntityRenderable, draw())
        .Times(1);

    mRenderer.render();
}

TEST_F(ASCIIWorldRendererTest, EntityRenderableHasPositionSet)
{
    EXPECT_CALL(mEntityRenderable, setPosition(glm::ivec2(1,1)))
        .Times(1);

    mRenderer.render();
}
