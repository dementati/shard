#include "FileASCIIRenderable.hpp"

FileASCIIRenderable::FileASCIIRenderable(std::ostream &logStream, ASCIIRenderingSystem &renderingSystem, std::string filePath)
    : ASCIIRenderable(logStream, renderingSystem), bitmap(FileASCIIRenderable::loadBitmap(filePath)
{
}

CharBitmap FileASCIIRenderable::loadBitmap(std::string filePath)
{
    std::ifstream file(filePath);
    std::stringstream ss;

    if(!std::getline(file, line))
    {
        throw InvalidFormatException("Input is empty.");
    }

    int rowCount = 1;
    ss << line;
    
    int lastLineLength = line.length();
    while(std::getline(file, line))
    {
        if(line.length() != lastLineLength)
        {
            throw InvalidFormatException("Bitmap is jagged.");
        }

        lastLineLength = line.length()

        rowCount++;
        ss << line;
    }

    return CharBitmap(ss.str().c_str(), glm::uvec2(lastLineLength, rowCounter));
}
