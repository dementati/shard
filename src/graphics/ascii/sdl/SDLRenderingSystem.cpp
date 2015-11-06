#include "SDLRenderingSystem.hpp"

SDLRenderingSystem::SDLRenderingSystem(SDLInterface &sdl)
:
    mLogger(LoggerFactory::createLogger("SDLRenderingSystem", Severity::DEBUG)),
    mSDL(sdl),
    mCharTextureMap()
{
    mLogger->debug("Finished construction");
}

void SDLRenderingSystem::drawBitmap(const CharBitmap &bitmap, const glm::ivec2 position)
{
    ASSERT(false, "Not yet implemented");

    // Bullshit to get rid of unused warning
    ASSERT((int)bitmap.getDimensions().x == position.y, ""); 
}

void SDLRenderingSystem::drawCharacter(const char character, const glm::ivec2 position)
{
    mLogger->debug(std::string("Drawing ") + character + " at " + glm::to_string(position));

    // If character is not in character -> texture map
    if(mCharTextureMap.count(character) == 0)
    {
        mCharTextureMap[character] = 
            mSDL.createTextureFromString(std::string() + character, glm::u8vec4(255, 255, 255, 255));
    }

    // Render texture the character maps to
    glm::ivec2 dimensions(10, 13);
    mSDL.render(*mCharTextureMap[character], position * dimensions, dimensions);
}

void SDLRenderingSystem::clear()
{
    mLogger->debug("Clearing");
    mSDL.clear();
}

void SDLRenderingSystem::refresh()
{
    mLogger->debug("Refreshing");
    mSDL.refresh();
}
