#pragma once

#include <ostream>
#include <string>

#include "../../utility/LoggerFactory.hpp"
#include "../Renderable.hpp"
#include "ASCIIRenderingSystem.hpp"

class ASCIIRenderable : public Renderable
{
    std::unique_ptr<Logger> mLogger;

protected:
    ASCIIRenderingSystem &mRenderingSystem;

public:
    ASCIIRenderable(ASCIIRenderingSystem &renderingSystem);

    virtual void setPosition(glm::ivec2 position) = 0;
};
