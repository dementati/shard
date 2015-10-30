#include "NCursesRenderingSystem.hpp"

// LCOV_EXCL_START <- Manual testing required
NCursesRenderingSystem::NCursesRenderingSystem(NCursesInterface& ncurses)
: 
    mLogger(LoggerFactory::createLogger("NCursesRenderingSystem", Severity::DEBUG)), 
    mNcurses(ncurses)
{
}

void NCursesRenderingSystem::drawBitmap(const CharBitmap &bitmap, const glm::ivec2 position)
{
    glm::ivec2 screenPosition = getScreenCoordinates(position);

    for(unsigned int ry = 0; ry < bitmap.getDimensions().y; ry++)
    {
        for(unsigned int rx = 0; rx < bitmap.getDimensions().x; rx++)
        {
            mNcurses.draw(bitmap.get(glm::uvec2(rx, ry)), 
                screenPosition.x + rx, screenPosition.y + ry); 
        }
    }
}
// LCOV_EXCL_STOP
