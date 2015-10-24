#include <gtest/gtest.h>

#include <glm/glm.hpp>

#include "../../../src/graphics/ascii/ASCIIRenderingSystem.hpp"
#include "../../../src/graphics/CharBitmap.hpp"

class TestRenderingSystem : public ASCIIRenderingSystem
{
public:
    void drawBitmap(const CharBitmap &bitmap, const glm::ivec2 position) {}

    glm::ivec2 getScreenCoordinates(glm::ivec2 worldCoordinates)
    {
        return ASCIIRenderingSystem::getScreenCoordinates(worldCoordinates);
    }
};

class ASCIIRenderingSystemTest : public ::testing::Test
{
};

TEST_F(ASCIIRenderingSystemTest, GetScreenCoordinatesWithScreenAt0x0)
{
    TestRenderingSystem system;
    system.setScreenPosition(glm::ivec2(0, 0));

    EXPECT_EQ(glm::ivec2(0, 0), system.getScreenCoordinates(glm::ivec2(0, 0)));
    EXPECT_EQ(glm::ivec2(1, 0), system.getScreenCoordinates(glm::ivec2(1, 0)));
    EXPECT_EQ(glm::ivec2(0, 1), system.getScreenCoordinates(glm::ivec2(0, 1)));
}

TEST_F(ASCIIRenderingSystemTest, GetScreenCoordinatesWithScreenAt1x0)
{
    TestRenderingSystem system;
    system.setScreenPosition(glm::ivec2(1, 0));

    EXPECT_EQ(glm::ivec2(-1, 0), system.getScreenCoordinates(glm::ivec2(0, 0)));
    EXPECT_EQ(glm::ivec2(0, 0), system.getScreenCoordinates(glm::ivec2(1, 0)));
    EXPECT_EQ(glm::ivec2(-1, 1), system.getScreenCoordinates(glm::ivec2(0, 1)));
}

TEST_F(ASCIIRenderingSystemTest, GetScreenCoordinatesWithScreenAtMinus1x0)
{
    TestRenderingSystem system;
    system.setScreenPosition(glm::ivec2(-1, 0));

    EXPECT_EQ(glm::ivec2(1, 0), system.getScreenCoordinates(glm::ivec2(0, 0)));
    EXPECT_EQ(glm::ivec2(2, 0), system.getScreenCoordinates(glm::ivec2(1, 0)));
    EXPECT_EQ(glm::ivec2(1, 1), system.getScreenCoordinates(glm::ivec2(0, 1)));
}

TEST_F(ASCIIRenderingSystemTest, GetScreenCoordinatesWithScreenAt0x1)
{
    TestRenderingSystem system;
    system.setScreenPosition(glm::ivec2(0, 1));

    EXPECT_EQ(glm::ivec2(0, -1), system.getScreenCoordinates(glm::ivec2(0, 0)));
    EXPECT_EQ(glm::ivec2(1, -1), system.getScreenCoordinates(glm::ivec2(1, 0)));
    EXPECT_EQ(glm::ivec2(0, 0), system.getScreenCoordinates(glm::ivec2(0, 1)));
}

TEST_F(ASCIIRenderingSystemTest, GetScreenCoordinatesWithScreenAt0xMinus0)
{
    TestRenderingSystem system;
    system.setScreenPosition(glm::ivec2(0, -1));

    EXPECT_EQ(glm::ivec2(0, 1), system.getScreenCoordinates(glm::ivec2(0, 0)));
    EXPECT_EQ(glm::ivec2(1, 1), system.getScreenCoordinates(glm::ivec2(1, 0)));
    EXPECT_EQ(glm::ivec2(0, 2), system.getScreenCoordinates(glm::ivec2(0, 1)));
}
