#pragma once

#include <iostream>

#include <gmock/gmock.h>

#include "../../src/graphics/ascii/ASCIIRenderingSystem.hpp"

class MockASCIIRenderingSystem : public ASCIIRenderingSystem
{
public:
    MOCK_METHOD2(drawBitmap, void(const CharBitmap&, const glm::ivec2));

    MOCK_CONST_METHOD0(unitName, const std::string());
};
