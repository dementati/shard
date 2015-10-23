#pragma once 

#include <fstream>
#include <ostream>
#include <sstream>
#include <string>

#include "../core/InvalidArgumentException.hpp"
#include "../core/InvalidFormatException.hpp"
#include "../utility/StreamLogger.hpp"
#include "ASCIIRenderingSystem.hpp"
#include "ASCIIRenderable.hpp"
#include "CharBitmap.hpp"
#include "CharBitmapLoader.hpp"

class FileASCIIRenderable : public ASCIIRenderable
{
    CharBitmapLoader bitmapLoader;

    CharBitmap bitmap;

    glm::ivec2 position;

    StreamLogger logger;

public:
    FileASCIIRenderable(std::ostream &logStream, ASCIIRenderingSystem &renderingSystem, std::string filePath);

    void draw();

    void setPosition(glm::ivec2 position);
};
