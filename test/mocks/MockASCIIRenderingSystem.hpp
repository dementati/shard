#pragma once

#include <iostream>

#include <gmock/gmock.h>

#include "../../src/graphics/ascii/ASCIIRenderingSystem.hpp"

class MockASCIIRenderingSystem : public ASCIIRenderingSystem
{
public:
    MOCK_METHOD2(drawBitmap, void(const CharBitmap&, const glm::ivec2));

    MOCK_METHOD2(drawCharacter, void(const char, const glm::ivec2));

    MOCK_METHOD0(clear, void());

    MOCK_METHOD0(refresh, void());
};
