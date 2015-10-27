#include "ASCIIRenderingSystem.hpp"

// LCOV_EXCL_START
const std::string ASCIIRenderingSystem::unitName() const
{
    return std::string("ASCIIRenderingSystem");
}
// LCOV_EXCL_STOP

glm::ivec2 ASCIIRenderingSystem::getScreenCoordinates(glm::ivec2 worldCoordinates)
{
    return worldCoordinates - mScreenPosition;
}

void ASCIIRenderingSystem::setScreenPosition(const glm::ivec2 position)
{
    mScreenPosition = position;
}
