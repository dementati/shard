#include "ASCIIFileRenderable.hpp"

// LCOV_EXCL_START
ASCIIFileRenderable::ASCIIFileRenderable(std::ostream &logStream, 
    ASCIIRenderingSystem &renderingSystem, std::string filePath)
: 
    ASCIIRenderable(logStream, renderingSystem), 
    bitmapLoader(logStream), 
    bitmap(bitmapLoader.load(filePath)),
    mPosition(glm::ivec2(0,0)),
    logger(*this, logStream) 
{
    assert(filePath.length() > 0 && "File path cannot be empty");
}

void ASCIIFileRenderable::draw()
{
    mRenderingSystem.drawBitmap(bitmap, mPosition);
}

void ASCIIFileRenderable::setPosition(glm::ivec2 position)
{
    mPosition = position;
}
// LCOV_EXCL_STOP

