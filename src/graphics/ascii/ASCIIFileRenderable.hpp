#pragma once 

#include <fstream>
#include <ostream>
#include <sstream>
#include <string>

#include "../../core/InvalidArgumentException.hpp"
#include "../../core/InvalidFormatException.hpp"
#include "../../utility/LoggerFactory.hpp"
#include "../CharBitmap.hpp"
#include "../CharBitmapLoader.hpp"
#include "ASCIIRenderingSystem.hpp"
#include "ASCIIRenderable.hpp"

// LCOV_EXCL_START
class ASCIIFileRenderable : public ASCIIRenderable
{
    CharBitmapLoader mBitmapLoader;

    CharBitmap mBitmap;

    glm::ivec2 mPosition;

    std::unique_ptr<Logger> mLogger;

public:
    ASCIIFileRenderable(ASCIIRenderingSystem &renderingSystem, std::string filePath);

    void draw();

    void setPosition(glm::ivec2 position);
};
// LCOV_EXCL_START
