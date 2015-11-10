#pragma once

enum class Key
{
    None,
    Up,
    Down,
    Left,
    Right,
    Use,
	DrinkBlood,
    Quit
};

// LCOV_EXCL_START
class InputSystem
{
public:
    virtual ~InputSystem() {}

    virtual bool isPressed(Key key) = 0;
};
// LCOV_EXCL_STOP
