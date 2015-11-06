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

    LoggerPtr mLogger;

public:
    ASCIISingleCharacterRenderable(ASCIIRenderingSystem &renderingSystem, char character);

    void draw();
};
// LCOV_EXCL_START
