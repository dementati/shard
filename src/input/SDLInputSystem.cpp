#include "SDLInputSystem.hpp"

SDLInputSystem::SDLInputSystem(SDLInterface &sdl)
:
    mLogger(LoggerFactory::createLogger("SDLInputSystem", Severity::DEBUG)),
    mKeyPressedLock(),
    mKeyPressed(),
    mSDL(sdl)
{
    mLogger->info("Finished construction.");
}

void SDLInputSystem::update()
{
    mLogger->debug("Updating...");

    SDLEvent event = mSDL.pollEvents();

    if(event != SDLEvent::NONE)
    {
        if(event == SDLEvent::KEY_UP_PRESSED) { setKeyPressed(Key::Up, true); } 
        else if(event == SDLEvent::KEY_DOWN_PRESSED) { setKeyPressed(Key::Down, true); } 
        else if(event == SDLEvent::KEY_LEFT_PRESSED) { setKeyPressed(Key::Left, true); } 
        else if(event == SDLEvent::KEY_RIGHT_PRESSED) { setKeyPressed(Key::Right, true); } 
        else if(event == SDLEvent::KEY_UP_RELEASED) { setKeyPressed(Key::Up, false); } 
        else if(event == SDLEvent::KEY_DOWN_RELEASED) { setKeyPressed(Key::Down, false); } 
        else if(event == SDLEvent::KEY_LEFT_RELEASED) { setKeyPressed(Key::Left, false); } 
        else if(event == SDLEvent::KEY_RIGHT_RELEASED) 
            { setKeyPressed(Key::Right, false); } 
    }
}

bool SDLInputSystem::isPressed(Key key)
{
    mKeyPressedLock.lock();
    bool pressed = mKeyPressed[key]; 
    mKeyPressedLock.unlock();
    return pressed;
}

void SDLInputSystem::setKeyPressed(Key key, bool pressed)
{
    mLogger->debug(std::string("Setting ") + glm::to_string((int)key) + " to " + (pressed ? "PRESSED" : "RELEASED"));
    mKeyPressedLock.lock();
    mKeyPressed[key] = pressed;
    mKeyPressedLock.unlock();
}
