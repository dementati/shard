#pragma once

#include <memory>

#include <glm/glm.hpp>
#include <SDL.h>
#include <SDL_ttf.h>

#include "../utility/Assert.hpp"
#include "../utility/LoggerFactory.hpp"
#include "SDLTexture.hpp"

enum class SDLEvent
{
    NONE,
    QUIT,
    KEY_UP_PRESSED,
    KEY_DOWN_PRESSED,
    KEY_LEFT_PRESSED,
    KEY_RIGHT_PRESSED,
    KEY_UP_RELEASED,
    KEY_DOWN_RELEASED,
    KEY_LEFT_RELEASED,
    KEY_RIGHT_RELEASED
};

class SDLInterface
{
    LoggerPtr mLogger;
    SDL_Event mEvent;
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    TTF_Font* mFont;

public:
    SDLInterface(std::string windowTitle, glm::uvec2 windowSize);

    ~SDLInterface();

    SDLEvent pollEvents();

    std::shared_ptr<SDLTexture> createTextureFromString(std::string, glm::u8vec4 color);

    void clear();

    void render(SDLTexture &texture, glm::ivec2 position, glm::ivec2 dimensions);

    void refresh();
};
