#include "ASCIIRenderable.hpp"

// LCOV_EXCL_START
ASCIIRenderable::ASCIIRenderable(ASCIIRenderingSystem &renderingSystem)
: 
    mLogger(LoggerFactory::createLogger("ASCIIRenderable", Severity::DEBUG)),
    mPosition(glm::ivec2(0, 0)),
    mRenderingSystem(renderingSystem)
{
}
// LCOV_EXCL_STOP

void ASCIIRenderable::setPosition(glm::ivec2 position)
{
    mPosition = position;
}
