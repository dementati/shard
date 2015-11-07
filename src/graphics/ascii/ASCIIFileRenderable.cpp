#include "ASCIIFileRenderable.hpp"

// LCOV_EXCL_START
ASCIIFileRenderable::ASCIIFileRenderable(ASCIIRenderingSystem &renderingSystem, 
    std::string filePath)
: 
    ASCIIRenderable(renderingSystem), 
    mBitmapLoader(), 
    mBitmap(mBitmapLoader.load(filePath)),
    mLogger(LoggerFactory::createLogger("ASCIIFileRenderable", Severity::DEBUG)) 
{
    ASSERT(filePath.length() > 0, "File path cannot be empty");
}

void ASCIIFileRenderable::draw()
{
    mRenderingSystem.drawBitmap(mBitmap, mPosition);
}
