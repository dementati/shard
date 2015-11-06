#pragma once

enum class Key
{
    None,
    Up,
    Down,
    Left,
    Right,
    Use,
    Quit
};

class InputSystem
{
public:
    virtual ~InputSystem() {}

    virtual bool isPressed(Key key) = 0;
};
