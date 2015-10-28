#pragma once

#pragma GCC diagnostic ignored "-Weffc++"

#include <iostream>

#include <gmock/gmock.h>

#include "../../src/graphics/ascii/ASCIIRenderable.hpp"
#include "../../src/graphics/ascii/ASCIIRenderingSystem.hpp"
#include "MockASCIIRenderingSystem.hpp"

class MockASCIIRenderable : public ASCIIRenderable
{
    static MockASCIIRenderingSystem cRenderingSystem;

public:
    MockASCIIRenderable()
: 
    ASCIIRenderable(cRenderingSystem)
{}

    MOCK_METHOD0(draw, void());

    MOCK_CONST_METHOD0(unitName, const std::string());

    MOCK_METHOD1(setPosition, void(glm::ivec2));
};

MockASCIIRenderingSystem MockASCIIRenderable::cRenderingSystem;
