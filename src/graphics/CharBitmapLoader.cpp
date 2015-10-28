#include "CharBitmapLoader.hpp"

std::string CharBitmapLoader::trimCarriageReturn(std::string line) const
{
    if(line[line.length() - 1] == '\r')
    {
        line.erase(line.length() - 1);
    }

    return line;
}

CharBitmapLoader::CharBitmapLoader(std::ostream &logStream)
    : mLogger(*this, logStream)
{
}

const std::string CharBitmapLoader::unitName() const
{
    return std::string("CharBitmapLoader");
}

CharBitmap CharBitmapLoader::load(std::string filePath) const
{
    assert(filePath.length() > 0 && "File path cannot be empty");

    mLogger.info(std::string("Loading ") + filePath);

    std::ifstream file(filePath);
    if(!file.good())
    {
        throw InvalidArgumentException("File does not exist.");
    }

    std::stringstream ss;

    std::string line;
    if(!std::getline(file, line))
    {
        throw InvalidFormatException("Input is empty.");
    }
    line = trimCarriageReturn(line);

    int rowCount = 1;
    ss << line;
    
    auto lastLineLength = line.length();
    while(std::getline(file, line))
    {
        line = trimCarriageReturn(line);

        if(line.length() != lastLineLength)
        {
            throw InvalidFormatException("Bitmap is jagged.");
        }

        lastLineLength = line.length();

        rowCount++;
        ss << line;
    }

    return CharBitmap(ss.str().c_str(), glm::uvec2(lastLineLength, rowCount));
}
