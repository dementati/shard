#include <glm/glm.hpp>
#include <gtest/gtest.h>

#include "../../../../src/graphics/ascii/sdl/SDLRenderingSystem.hpp"
#include "../../../mocks/MockSDLInterface.hpp"
#include "../../../mocks/MockSDLTexture.hpp"

using ::testing::_; 
using ::testing::Return; 

using MockSDLInterfaceType = ::testing::NiceMock<MockSDLInterface>;

class SDLRenderingSystemTest : public ::testing::Test
{
protected:
    MockSDLInterfaceType mSDL;
    std::shared_ptr<MockSDLTexture> mTexture;
    char mCharacter;
    glm::u8vec4 mColor;
    glm::ivec2 mCharDimensions;
    
    SDLRenderingSystemTest()
    :
        mSDL(),
        mTexture(std::make_shared<MockSDLTexture>()),
        mCharacter(' '),
        mColor(glm::u8vec4(255, 255, 255, 255)),
        mCharDimensions(10, 13)
    {
    }

    void testDrawCharacterRender(glm::ivec2 position, glm::ivec2 screenPosition, 
        glm::ivec2 expectedPosition)
    {
        SDLRenderingSystem system(mSDL);
        system.setScreenPosition(screenPosition);

        ON_CALL(mSDL, createTextureFromString(_, mColor))
            .WillByDefault(Return(mTexture));

        EXPECT_CALL(mSDL, render(_, expectedPosition * mCharDimensions, mCharDimensions))
            .Times(1);

        system.drawCharacter(mCharacter, position);
    }
};

TEST_F(SDLRenderingSystemTest, drawCharacter_createTexture)
{
    SDLRenderingSystem system(mSDL);

    EXPECT_CALL(mSDL, createTextureFromString(std::string() + mCharacter, mColor))
        .Times(1)
        .WillOnce(Return(mTexture));

    system.drawCharacter(mCharacter, glm::ivec2(0, 0));
}

TEST_F(SDLRenderingSystemTest, drawCharacter_render_positionZero_screenPositionZero)
{
    testDrawCharacterRender(glm::ivec2(0, 0), glm::ivec2(0, 0), glm::ivec2(0, 0));
}

TEST_F(SDLRenderingSystemTest, drawCharacter_render_position1x1_screenPositionZero)
{
    testDrawCharacterRender(glm::ivec2(1, 1), glm::ivec2(0, 0), glm::ivec2(1, 1));
}

TEST_F(SDLRenderingSystemTest, drawCharacter_render_positionMinus1xMinus1_screenPositionZero)
{
    testDrawCharacterRender(glm::ivec2(-1, -1), glm::ivec2(0, 0), glm::ivec2(-1, -1));
}

TEST_F(SDLRenderingSystemTest, drawCharacter_render_positionZero_screenPosition1x1)
{
    testDrawCharacterRender(glm::ivec2(0, 0), glm::ivec2(1, 1), glm::ivec2(-1, -1));
}

TEST_F(SDLRenderingSystemTest, drawCharacter_render_positionZero_screenPositionMinus1xMinus1)
{
    testDrawCharacterRender(glm::ivec2(0, 0), glm::ivec2(-1, -1), glm::ivec2(1, 1));
}

TEST_F(SDLRenderingSystemTest, drawCharacter_render_position1x1_screenPosition1x1)
{
    testDrawCharacterRender(glm::ivec2(1, 1), glm::ivec2(1, 1), glm::ivec2(0, 0));
}

TEST_F(SDLRenderingSystemTest, drawCharacter_render_positionMinus1xMinus1_screenPosition1x1)
{
    testDrawCharacterRender(glm::ivec2(-1, -1), glm::ivec2(1, 1), glm::ivec2(-2, -2));
}

TEST_F(SDLRenderingSystemTest, drawCharacter_render_position1x1_screenPositionMinus1xMinus1)
{
    testDrawCharacterRender(glm::ivec2(1, 1), glm::ivec2(-1, -1), glm::ivec2(2, 2));
}
