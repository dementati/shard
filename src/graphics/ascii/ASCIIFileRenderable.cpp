#include "ASCIIFileRenderable.hpp"

// LCOV_EXCL_START
ASCIIFileRenderable::ASCIIFileRenderable(std::ostream &logStream, 
    ASCIIRenderingSystem &renderingSystem, std::string filePath)
: 
    ASCIIRenderable(logStream, renderingSystem), 
    mBitmapLoader(logStream), 
    mBitmap(mBitmapLoader.load(filePath)),
    mPosition(glm::ivec2(0,0)),
    mLogger("ASCIIFileRenderable", logStream) 
{
    assert(filePath.length() > 0 && "File path cannot be empty");
}

void ASCIIFileRenderable::draw()
{
    mRenderingSystem.drawBitmap(mBitmap, mPosition);
}

void ASCIIFileRenderable::setPosition(glm::ivec2 position)
{
    mPosition = position;
}
// LCOV_EXCL_STOP

