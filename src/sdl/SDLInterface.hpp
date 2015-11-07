#pragma once

#include <memory>
#include <unordered_map>

#include <glm/glm.hpp>
#include <SDL.h>
#include <SDL_ttf.h>

#include "../utility/Assert.hpp"
#include "../utility/EnumClassHash.hpp"
#include "../utility/LoggerFactory.hpp"
#include "SDLTexture.hpp"

enum class SDLKey
{
    W,
    A,
    S,
    D,
    E,
    Escape
};

class SDLInterface
{
    static std::unordered_map<SDLKey, SDL_Scancode, EnumClassHash> cScanCodeMap;

    LoggerPtr mLogger;
    SDL_Event mEvent;
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    TTF_Font* mFont;
    const Uint8* mKeyStates;

public:
    SDLInterface(std::string windowTitle, glm::uvec2 windowSize);

    virtual ~SDLInterface();

    virtual void pollEvents();

    virtual bool isPressed(SDLKey key);

    virtual std::shared_ptr<SDLTexture> createTextureFromString(std::string, glm::u8vec4 color);

    virtual void clear();

    virtual void render(SDLTexture &texture, glm::ivec2 position, glm::ivec2 dimensions);

    virtual void refresh();
};
