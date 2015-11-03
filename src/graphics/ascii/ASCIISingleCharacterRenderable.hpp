#pragma once 

#include <sstream>
#include <string>

#include "../../core/InvalidArgumentException.hpp"
#include "../../core/InvalidFormatException.hpp"
#include "../../utility/Assert.hpp"
#include "../../utility/LoggerFactory.hpp"
#include "../CharBitmap.hpp"
#include "../CharBitmapLoader.hpp"
#include "ASCIIRenderingSystem.hpp"
#include "ASCIIRenderable.hpp"

// LCOV_EXCL_START
class ASCIISingleCharacterRenderable : public ASCIIRenderable
{
    char mCharacter;

    glm::ivec2 mPosition;

    LoggerPtr mLogger;

public:
    ASCIISingleCharacterRenderable(ASCIIRenderingSystem &renderingSystem, char character);

    void draw();

    void setPosition(glm::ivec2 position);
};
// LCOV_EXCL_START
