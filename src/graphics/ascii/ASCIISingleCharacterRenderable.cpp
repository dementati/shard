#include "ASCIISingleCharacterRenderable.hpp"

// LCOV_EXCL_START
ASCIISingleCharacterRenderable::ASCIISingleCharacterRenderable(ASCIIRenderingSystem &renderingSystem, char character)
: 
    ASCIIRenderable(renderingSystem),
    mCharacter(character),
    mLogger(LoggerFactory::createLogger("ASCIISingleCharacterRenderable", Severity::DEBUG)) 
{
}

void ASCIISingleCharacterRenderable::draw()
{
    mRenderingSystem.drawCharacter(mCharacter, mPosition);
}
// LCOV_EXCL_STOP

