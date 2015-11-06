#pragma once

#pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"

#include <unordered_map>

#include <glm/glm.hpp>

#include "../../../sdl/SDLInterface.hpp"
#include "../../../utility/LoggerFactory.hpp"
#include "../ASCIIRenderingSystem.hpp"

class SDLRenderingSystem : public ASCIIRenderingSystem
{
    LoggerPtr mLogger;
    SDLInterface &mSDL;
    std::unordered_map<char, std::shared_ptr<SDLTexture>> mCharTextureMap;

public:
    SDLRenderingSystem(SDLInterface &sdl);

    virtual void drawBitmap(const CharBitmap &bitmap, const glm::ivec2 position);

    virtual void drawCharacter(const char character, const glm::ivec2 position);

    void clear();

    void refresh();
};
