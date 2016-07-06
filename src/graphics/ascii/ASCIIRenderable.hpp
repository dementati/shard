#pragma once

#include <ostream>
#include <string>

#include "../../utility/LoggerFactory.hpp"
#include "../Renderable.hpp"
#include "ASCIIRenderingSystem.hpp"

// LCOV_EXCL_START
class ASCIIRenderable : public Renderable
{
    LoggerPtr mLogger;

protected:
    glm::ivec2 mPosition;
    ASCIIRenderingSystem &mRenderingSystem;

public:
    ASCIIRenderable(ASCIIRenderingSystem &renderingSystem);

    virtual void setPosition(glm::ivec2 position);
};
// LCOV_EXCL_STOP
