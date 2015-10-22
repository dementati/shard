#pragma once

#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "../core/object.hpp"
#include "CharBitmap.hpp"

// LCOV_EXCL_START
class ASCIIRenderingSystem : public Object
{
    glm::ivec2 screenPosition;

protected:
    glm::ivec2 getScreenCoordinates(glm::ivec2 worldCoordinates);

public:
    const std::string unitName() const;

    virtual void drawBitmap(const CharBitmap &bitmap, const glm::ivec2 position) = 0;

    void setScreenPosition(const glm::ivec2 position);

};
// LCOV_EXCL_STOP
