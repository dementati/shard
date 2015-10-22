#pragma once

#include <ostream>
#include <string>

#include "../utility/StreamLogger.hpp"
#include "ASCIIRenderingSystem.hpp"
#include "Renderable.hpp"

class ASCIIRenderable : public Renderable
{
    StreamLogger logger;

protected:
    ASCIIRenderingSystem &renderingSystem;

public:
    ASCIIRenderable(std::ostream &logStream, ASCIIRenderingSystem &renderingSystem);

    const std::string unitName() const;
};
