#include "FileASCIIRenderable.hpp"

// LCOV_EXCL_START
FileASCIIRenderable::FileASCIIRenderable(std::ostream &logStream, ASCIIRenderingSystem &renderingSystem, std::string filePath)
    : ASCIIRenderable(logStream, renderingSystem), 
      bitmapLoader(logStream), 
      logger(*this, logStream), 
      bitmap(bitmapLoader.load(filePath))
{
    assert(filePath.length() > 0 && "File path cannot be empty");
}

void FileASCIIRenderable::draw()
{
    renderingSystem.drawBitmap(bitmap, position);
}

void FileASCIIRenderable::setPosition(glm::ivec2 position)
{
    this->position = position;
}
// LCOV_EXCL_STOP

