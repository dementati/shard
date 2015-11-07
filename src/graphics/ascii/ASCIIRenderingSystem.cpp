#include "ASCIIRenderingSystem.hpp"

ASCIIRenderingSystem::ASCIIRenderingSystem()
:
    mLogger(LoggerFactory::createLogger("ASCIIRenderingSystem", Severity::DEBUG)),
    mScreenPosition(glm::ivec2(0, 0))
{
    mLogger->info("Finished construction");
}

// LCOV_EXCL_START
ASCIIRenderingSystem::~ASCIIRenderingSystem()
{
    mLogger->info("Destroyed");
}
// LCOV_EXCL_STOP

glm::ivec2 ASCIIRenderingSystem::getScreenCoordinates(glm::ivec2 worldCoordinates)
{
    return worldCoordinates - mScreenPosition;
}

void ASCIIRenderingSystem::setScreenPosition(const glm::ivec2 position)
{
    mLogger->info("Setting screen position to " + glm::to_string(position));
    mScreenPosition = position;
}
