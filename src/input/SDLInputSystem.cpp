#include "SDLInputSystem.hpp"

// LCOV_EXCL_START
std::unordered_map<Key, SDLKey, EnumClassHash> SDLInputSystem::cKeyMap = 
{
    {Key::Up, SDLKey::W},
    {Key::Down, SDLKey::S},
    {Key::Left, SDLKey::A},
    {Key::Right, SDLKey::D},
    {Key::Use, SDLKey::E},
	{Key::DrinkBlood, SDLKey::Q},
    {Key::Quit, SDLKey::Escape}
};

SDLInputSystem::SDLInputSystem(SDLInterface &sdl)
:
    mLogger(LoggerFactory::createLogger("SDLInputSystem", Severity::DEBUG)),
    mSDL(sdl)
{
    LOG_INFO(mLogger, "Finished construction.");
}

void SDLInputSystem::update()
{
    LOG_DEBUG(mLogger, "Updating...");

    mSDL.pollEvents();
}

bool SDLInputSystem::isPressed(Key key)
{
    ASSERT(cKeyMap.count(key) == 1, "Key is not supported");

    return mSDL.isPressed(cKeyMap[key]);
}
// LCOV_EXCL_STOP
