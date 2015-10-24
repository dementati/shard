#pragma once

#include "../../src/graphics/ascii/ASCIIRenderingSystem.hpp"

class TestASCIIRenderingSystem : public ASCIIRenderingSystem
{
    void drawBitmap(const CharBitmap &bitmap, const glm::ivec2 position) {};
};
