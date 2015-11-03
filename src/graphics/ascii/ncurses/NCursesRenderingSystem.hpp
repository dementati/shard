#pragma once

#include <ostream>
#include <string>

#include <glm/glm.hpp>

#include "../../../ncurses/NCursesInterface.hpp"
#include "../../../utility/LoggerFactory.hpp"
#include "../ASCIIRenderingSystem.hpp"

// LCOV_EXCL_START
class NCursesRenderingSystem : public ASCIIRenderingSystem
{
    LoggerPtr mLogger;
    NCursesInterface& mNcurses;

public:
    NCursesRenderingSystem(NCursesInterface& ncurses);

    void drawBitmap(const CharBitmap &bitmap, const glm::ivec2 position);

    void drawCharacter(const char character, const glm::ivec2 position);

    void clear();

    void refresh();
};
// LCOV_EXCL_STOP
