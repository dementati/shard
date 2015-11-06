#pragma once

#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "../../utility/LoggerFactory.hpp"
#include "../CharBitmap.hpp"

// LCOV_EXCL_START
class ASCIIRenderingSystem
{
    LoggerPtr mLogger;
    glm::ivec2 mScreenPosition;

protected:
    glm::ivec2 getScreenCoordinates(glm::ivec2 worldCoordinates);

public:
    ASCIIRenderingSystem();

    virtual ~ASCIIRenderingSystem();

    virtual void drawBitmap(const CharBitmap &bitmap, const glm::ivec2 position) = 0;

    virtual void drawCharacter(const char character, const glm::ivec2 position) = 0;

    virtual void clear() = 0;

    virtual void refresh() = 0;

    void setScreenPosition(const glm::ivec2 position);

};
// LCOV_EXCL_STOP
