#pragma once

#include <ostream>
#include <string>

#include "../../utility/StreamLogger.hpp"
#include "../Renderable.hpp"
#include "ASCIIRenderingSystem.hpp"

class ASCIIRenderable : public Renderable
{
    StreamLogger logger;

protected:
    ASCIIRenderingSystem &renderingSystem;

public:
    ASCIIRenderable(std::ostream &logStream, ASCIIRenderingSystem &renderingSystem);

    const std::string unitName() const;

    virtual void setPosition(glm::ivec2 position) = 0;
};
