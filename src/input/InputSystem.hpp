#pragma once

enum class Key
{
    None = -1,
    Up = 'w',
    Down = 's',
    Left = 'a',
    Right = 'd',
    Use = 'e',
    Quit = 'q'
};

class InputSystem
{
public:
    virtual ~InputSystem() {}

    virtual void update() = 0;

    virtual bool isPressed(Key key) = 0;
};
