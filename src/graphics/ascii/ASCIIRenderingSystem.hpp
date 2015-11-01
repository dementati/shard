#pragma once

#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "../CharBitmap.hpp"

// LCOV_EXCL_START
class ASCIIRenderingSystem
{
    glm::ivec2 mScreenPosition = glm::ivec2(0,0);

protected:
    glm::ivec2 getScreenCoordinates(glm::ivec2 worldCoordinates);

public:
    virtual ~ASCIIRenderingSystem();

    virtual void drawBitmap(const CharBitmap &bitmap, const glm::ivec2 position) = 0;

    virtual void drawCharacter(const char character, const glm::ivec2 position) = 0;

    void setScreenPosition(const glm::ivec2 position);

};
// LCOV_EXCL_STOP
