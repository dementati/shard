#pragma once

#include "../../src/graphics/ascii/ASCIIRenderable.hpp"
#include "TestASCIIRenderingSystem.hpp"

class TestASCIIRenderable : public ASCIIRenderable
{
public:
    TestASCIIRenderingSystem renderingSystem;

    int id;
    bool drawCalled;
    TestASCIIRenderable(int id) : ASCIIRenderable(std::cout, renderingSystem), id(id), drawCalled(false) {}
    void draw() { drawCalled = true; }
    const std::string unitName() const { return std::string(); }
    void setPosition(glm::ivec2 position) {}
};
