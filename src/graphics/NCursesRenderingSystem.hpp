#pragma once

#include <ostream>
#include <string>

#include <glm/glm.hpp>

#include "../ncurses/NCursesInterface.hpp"
#include "../utility/StreamLogger.hpp"
#include "ASCIIRenderingSystem.hpp"

class NCursesRenderingSystem : public ASCIIRenderingSystem
{
    StreamLogger logger;
    NCursesInterface& ncurses;

public:
    NCursesRenderingSystem(std::ostream& logStream, NCursesInterface& ncurses);

    const std::string unitName() const;

    void drawBitmap(const CharBitmap &bitmap, const glm::ivec2 position);
};
