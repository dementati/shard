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

void NCursesRenderingSystem::drawBitmap(const CharBitmap &bitmap, const int x, const int y)
{
    for(int ry = 0; ry < bitmap.height; ry++)
    {
        for(int rx = 0; rx < bitmap.width; rx++)
        {
            ncurses.draw(bitmap.get(rx, ry), x + rx, y + ry); 
        }
    }
}
// LCOV_EXCL_STOP
