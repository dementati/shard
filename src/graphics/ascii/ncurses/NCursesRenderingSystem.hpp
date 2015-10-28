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
    std::unique_ptr<Logger> mLogger;
    NCursesInterface& mNcurses;

public:
    NCursesRenderingSystem(NCursesInterface& ncurses);

    const std::string unitName() const;

    void drawBitmap(const CharBitmap &bitmap, const glm::ivec2 position);
};
// LCOV_EXCL_STOP
