#pragma once

#include <unordered_map>

#include "../ncurses/NCursesInterface.hpp"
#include "InputSystem.hpp"

class NCursesInputSystem : public InputSystem
{
    NCursesInterface &mNcurses;
    int mLastKeyPressed;

public:
    NCursesInputSystem(NCursesInterface &ncurses);

    virtual ~NCursesInputSystem();

    virtual void update();

    virtual bool isPressed(Key key);
};
