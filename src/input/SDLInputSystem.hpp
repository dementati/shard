#pragma once

#include <mutex>
#include <unordered_map>

#include "../sdl/SDLInterface.hpp"
#include "../utility/LoggerFactory.hpp"
#include "InputSystem.hpp"
#include "Keymap.hpp"

class SDLInputSystem : public InputSystem
{
    LoggerPtr mLogger;
    std::mutex mKeyPressedLock;
    std::unordered_map<Key, bool, KeyHash> mKeyPressed;
    SDLInterface &mSDL;

public:
    SDLInputSystem(SDLInterface &sdl);

    virtual void update();

    virtual bool isPressed(Key key);

    virtual void setKeyPressed(Key key, bool pressed);
};
