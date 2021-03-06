#include "SDLRenderingSystem.hpp"

SDLRenderingSystem::SDLRenderingSystem(SDLInterface &sdl)
:
    mLogger(LoggerFactory::createLogger("SDLRenderingSystem", Severity::DEBUG)),
    mSDL(sdl),
    mCharTextureMap()
{
    LOG_DEBUG(mLogger, "Finished construction");
}

// LCOV_EXCL_START
void SDLRenderingSystem::drawBitmap(const CharBitmap &bitmap, const glm::ivec2 position)
{
    ASSERT(false, "Not yet implemented");

    // Bullshit to get rid of unused warning
    ASSERT((int)bitmap.getDimensions().x == position.y, ""); 
}
// LCOV_EXCL_STOP

void SDLRenderingSystem::drawCharacter(const char character, const glm::ivec2 position)
{
    auto screenPosition = getScreenCoordinates(position);

    LOG_DEBUG(mLogger, "Drawing " << character << " at " << glm::to_string(screenPosition));

    if(mCharTextureMap.count(character) == 0)
    {
        LOG_DEBUG(mLogger, "Creating texture for " << character);
        mCharTextureMap[character] = 
            mSDL.createTextureFromString(std::string() + character, glm::u8vec4(255, 255, 255, 255));
        if(mCharTextureMap[character]->get() == nullptr)
        {
            LOG_ERROR(mLogger, "Failed to create character texture for " << character);
        }
    }

    glm::ivec2 dimensions(10, 13);
    mSDL.render(*mCharTextureMap[character], screenPosition * dimensions, dimensions);
}

// LCOV_EXCL_START
void SDLRenderingSystem::clear()
{
    LOG_DEBUG(mLogger, "Clearing");
    mSDL.clear();
}

void SDLRenderingSystem::refresh()
{
    LOG_DEBUG(mLogger, "Refreshing");
    mSDL.refresh();
}
// LCOV_EXCL_STOP
