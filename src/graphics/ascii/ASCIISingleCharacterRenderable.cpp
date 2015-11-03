#include "ASCIISingleCharacterRenderable.hpp"

// LCOV_EXCL_START
ASCIISingleCharacterRenderable::ASCIISingleCharacterRenderable(ASCIIRenderingSystem &renderingSystem, char character)
: 
    ASCIIRenderable(renderingSystem),
    mCharacter(character),
    mPosition(glm::ivec2(0,0)),
    mLogger(LoggerFactory::createLogger("ASCIISingleCharacterRenderable", Severity::DEBUG)) 
{
}

void ASCIISingleCharacterRenderable::draw()
{
    mRenderingSystem.drawCharacter(mCharacter, mPosition);
}

void ASCIISingleCharacterRenderable::setPosition(glm::ivec2 position)
{
    mPosition = position;
}
// LCOV_EXCL_STOP

