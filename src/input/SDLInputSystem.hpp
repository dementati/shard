#pragma once

#include <unordered_map>

#include "../sdl/SDLInterface.hpp"
#include "../utility/Assert.hpp"
#include "../utility/EnumClassHash.hpp"
#include "../utility/LoggerFactory.hpp"
#include "InputSystem.hpp"
#include "Keymap.hpp"

class SDLInputSystem : public InputSystem
{
    static std::unordered_map<Key, SDLKey, EnumClassHash> cKeyMap;

    LoggerPtr mLogger;
    SDLInterface &mSDL;

public:
    SDLInputSystem(SDLInterface &sdl);

    virtual void update();

    virtual bool isPressed(Key key);
};
