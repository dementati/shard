#include <memory>

#include <gtest/gtest.h>

#include "../../src/graphics/Renderable.hpp"
#include "../../src/graphics/RenderableStore.hpp"
#include "../mocks/TestASCIIRenderable.hpp"

#define SIZE_2x2_FILE_PATH "../test/resources/charBitmaps/2x2.txt"

class RenderableStoreTest : public ::testing::Test
{
};

class TestRenderable : public Renderable
{
public:
    int id;
    TestRenderable(int id) : id(id) {}
    void draw() {}
    const std::string unitName() const { return std::string(); } 
};

TEST_F(RenderableStoreTest, AddAndGetRenderable)
{
    RenderableStore<Renderable> store;
    std::unique_ptr<TestRenderable> renderable = std::make_unique<TestRenderable>(1);
    store.add("test", std::move(renderable));
    TestRenderable& acquiredRenderable = 
        dynamic_cast<TestRenderable&>(store.get("test"));

    EXPECT_EQ(1, acquiredRenderable.id);
}
