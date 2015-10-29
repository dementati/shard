#include "ASCIIRenderable.hpp"

// LCOV_EXCL_START
ASCIIRenderable::ASCIIRenderable(ASCIIRenderingSystem &renderingSystem)
: 
    mLogger(LoggerFactory::createLogger("ASCIIRenderable", Severity::DEBUG)), 
    mRenderingSystem(renderingSystem)
{
}
// LCOV_EXCL_STOP
