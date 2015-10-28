#include "NCursesRenderingSystem.hpp"

// LCOV_EXCL_START <- Manual testing required
NCursesRenderingSystem::NCursesRenderingSystem(std::ostream& logStream, 
    NCursesInterface& ncurses)
        : mLogger(*this, logStream), mNcurses(ncurses)
{
}

const std::string NCursesRenderingSystem::unitName() const
{
    return std::string("NCursesRenderingSystem");
}

void NCursesRenderingSystem::drawBitmap(const CharBitmap &bitmap, const glm::ivec2 position)
{
    glm::ivec2 screenPosition = getScreenCoordinates(position);

    for(unsigned int ry = 0; ry < bitmap.mDimensions.y; ry++)
    {
        for(unsigned int rx = 0; rx < bitmap.mDimensions.x; rx++)
        {
            mNcurses.draw(bitmap.get(glm::uvec2(rx, ry)), 
                screenPosition.x + rx, screenPosition.y + ry); 
        }
    }
}
// LCOV_EXCL_STOP
