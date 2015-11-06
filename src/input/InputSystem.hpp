#pragma once

#include "Keymap.hpp"

class InputSystem
{
public:
    virtual ~InputSystem() {}

    virtual bool isPressed(Key key) = 0;
};
