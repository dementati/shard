#pragma once 

#include <fstream>
#include <ostream>
#include <sstream>
#include <string>

#include "../../core/InvalidArgumentException.hpp"
#include "../../core/InvalidFormatException.hpp"
#include "../../utility/StreamLogger.hpp"
#include "../CharBitmap.hpp"
#include "../CharBitmapLoader.hpp"
#include "ASCIIRenderingSystem.hpp"
#include "ASCIIRenderable.hpp"

// LCOV_EXCL_START
class ASCIIFileRenderable : public ASCIIRenderable
{
    CharBitmapLoader bitmapLoader;

    CharBitmap bitmap;

    glm::ivec2 mPosition;

    StreamLogger logger;

public:
    ASCIIFileRenderable(std::ostream &logStream, ASCIIRenderingSystem &renderingSystem, std::string filePath);

    void draw();

    void setPosition(glm::ivec2 position);
};
// LCOV_EXCL_START
