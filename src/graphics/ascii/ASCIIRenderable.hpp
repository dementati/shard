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

    const std::string unitName() const;

    virtual void setPosition(glm::ivec2 position) = 0;
};
