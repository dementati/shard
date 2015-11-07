#pragma once

#include <gmock/gmock.h>

#include "../../src/sdl/SDLTexture.hpp"

class MockSDLTexture : public SDLTexture
{
public:
    MockSDLTexture()
    :
        SDLTexture(nullptr)
    {
    }
};
