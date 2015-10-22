#pragma once

#include <ostream>
#include <string>

#include <glm/glm.hpp>

#include "../utility/StreamLogger.hpp"
#include "ASCIIRenderable.hpp"
#include "CharBitmap.hpp"

class TestRenderable : public ASCIIRenderable
{
    StreamLogger logger;

    CharBitmap bitmap;

    glm::ivec2 position;

public:
    TestRenderable(std::ostream &logStream, ASCIIRenderingSystem &renderingSystem);

    const std::string unitName() const;

    void draw();

    void setPosition(glm::ivec2 position);
};
