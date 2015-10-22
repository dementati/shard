#include "TestRenderable.hpp"

// LCOV_EXCL_START
TestRenderable::TestRenderable(std::ostream &logStream, ASCIIRenderingSystem &renderingSystem)
    : ASCIIRenderable(logStream, renderingSystem), logger(*this, logStream), bitmap("/\\\\/", glm::uvec2(2, 2))
{
}

const std::string TestRenderable::unitName() const
{
    return std::string("TestRenderable");
}

void TestRenderable::draw()
{
    renderingSystem.drawBitmap(bitmap, position);
}

void TestRenderable::setPosition(glm::ivec2 position)
{
    this->position = position;
}
// LCOV_EXCL_STOP
