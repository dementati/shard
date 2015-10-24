#include "NCursesRenderingSystem.hpp"

// LCOV_EXCL_START <- Manual testing required
NCursesRenderingSystem::NCursesRenderingSystem(std::ostream& logStream, NCursesInterface& ncurses)
    : logger(*this, logStream), ncurses(ncurses)
{
}

const std::string NCursesRenderingSystem::unitName() const
{
    return std::string("NCursesRenderingSystem");
}

void NCursesRenderingSystem::drawBitmap(const CharBitmap &bitmap, const glm::ivec2 position)
{
    glm::ivec2 screenPosition = getScreenCoordinates(position);

    for(int ry = 0; ry < bitmap.dimensions.y; ry++)
    {
        for(int rx = 0; rx < bitmap.dimensions.x; rx++)
        {
            ncurses.draw(bitmap.get(glm::uvec2(rx, ry)), screenPosition.x + rx, screenPosition.y + ry); 
        }
    }
}
// LCOV_EXCL_STOP
