#include "ASCIIRenderable.hpp"

// LCOV_EXCL_START
ASCIIRenderable::ASCIIRenderable(std::ostream &logStream, ASCIIRenderingSystem &renderingSystem)
    : logger(*this, logStream), mRenderingSystem(renderingSystem)
{
}

const std::string ASCIIRenderable::unitName() const
{
    return std::string("ASCIIRenderable");
}
// LCOV_EXCL_STOP
