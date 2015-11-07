#pragma once

#include <gmock/gmock.h>

#include "../../src/input/InputSystem.hpp"


class MockInputSystem : public InputSystem
{
public:
    MOCK_METHOD1(isPressed, bool(Key));
};
