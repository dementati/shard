#include "NCursesInputSystem.hpp"

NCursesInputSystem::NCursesInputSystem(NCursesInterface &ncurses)
:
    mNcurses(ncurses),
    mLastKeyPressed((int)Key::None)
{
}

NCursesInputSystem::~NCursesInputSystem()
{
}

void NCursesInputSystem::update()
{
    mLastKeyPressed = mNcurses.getInput();

    if(mLastKeyPressed == NCursesInterface::NoInput)
    {
        mLastKeyPressed = (int)Key::None;
    }
}

bool NCursesInputSystem::isPressed(Key key)
{
    return (int)key == mLastKeyPressed;
}
