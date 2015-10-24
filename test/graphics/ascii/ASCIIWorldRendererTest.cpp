#include <memory>

#include <glm/glm.hpp>
#include <gtest/gtest.h>

#include "../../../src/graphics/ascii/ASCIIWorldRenderer.hpp"
#include "../../../src/graphics/ascii/ASCIIRenderable.hpp"
#include "../../../src/graphics/CharBitmap.hpp"
#include "../../../src/graphics/RenderableStore.hpp"
#include "../../../src/logic/Entity.hpp"
#include "../../../src/logic/World.hpp"
#include "../../mocks/TestASCIIRenderable.hpp"

#define SIZE_2x2_FILE_PATH "../test/resources/charBitmaps/2x2.txt"

class ASCIIWorldRendererTest : public ::testing::Test
{
protected:
    RenderableStore<ASCIIRenderable> store;

    ASCIIWorldRendererTest()
    {
        store.add("test", std::make_unique<TestASCIIRenderable>(1));
    }
};

TEST_F(ASCIIWorldRendererTest, SingleEntityWorld)
{
    World world;
    Entity entity("test");
    world.add(entity);
   
    ASCIIWorldRenderer renderer(store, world);
    renderer.render();

    TestASCIIRenderable& renderable = dynamic_cast<TestASCIIRenderable&>(store.get("test"));
    EXPECT_TRUE(renderable.drawCalled);
}
