#include "ASCIIRenderable.hpp"

// LCOV_EXCL_START
ASCIIRenderable::ASCIIRenderable(ASCIIRenderingSystem &renderingSystem)
: 
    mLogger(LoggerFactory::createLogger("ASCIIRenderable", Severity::DEBUG)), 
    mRenderingSystem(renderingSystem)
{
}

const std::string ASCIIRenderable::unitName() const
{
    return std::string("ASCIIRenderable");
}
// LCOV_EXCL_STOP
