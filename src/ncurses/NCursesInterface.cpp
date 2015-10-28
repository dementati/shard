#include "NCursesInterface.hpp"

// LCOV_EXCL_START
NCursesInterface::NCursesInterface()
:
    NCursesInterface(std::cout)
{
}

NCursesInterface::NCursesInterface(std::ostream &logStream)
: 
    mLogger(*this, logStream),
    mColorCache(ColorCache())
{
    mLogger.info("Initializing NCurses engine");

    if(!has_colors())
    {
        // TODO: Can't get this to work on mintty and this is too unimportant to waste time on 
        //       right now, but should be fixed later.
        // throw NCursesException("Terminal does not support colors.");
        mLogger.warn("Terminal does not support colors.");
    }

    initscr();
    raw();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
}

NCursesInterface::~NCursesInterface()
{
    mLogger.info("Destroying NCurses engine");
    endwin();
}

const std::string NCursesInterface::unitName() const
{
    return "NCursesInterface";
}

void NCursesInterface::refreshScreen()
{
    refresh();
}

/*
void NCursesInterface::draw(const char character, const int x, const int y, 
                         const short fr, const short fg, const short fb, 
                         const short br, const short bg, const short bb)
{
    
    assert(false && "This method hasn't been properly tested.");

    assert(fr >= 0 && fr <= 1000 && "NCurses color values must be in the range [0, 1000]");
    assert(fg >= 0 && fg <= 1000 && "NCurses color values must be in the range [0, 1000]");
    assert(fb >= 0 && fb <= 1000 && "NCurses color values must be in the range [0, 1000]");
    assert(br >= 0 && br <= 1000 && "NCurses color values must be in the range [0, 1000]");
    assert(bg >= 0 && bg <= 1000 && "NCurses color values must be in the range [0, 1000]");
    assert(bb >= 0 && bb <= 1000 && "NCurses color values must be in the range [0, 1000]");

    short frontColorId = getColorId(fr, fg, fb);
    short backColorId = getColorId(br, bg, bb);
    short colorPair = getColorPairId(frontColorId, backColorId);

    mvaddch(y, x, character | COLOR_PAIR(colorPair));
}
*/

void NCursesInterface::draw(const char character, const int x, const int y)
{
    mvaddch(y, x, character);
}

short NCursesInterface::getColorId(const short r, const short g, const short b)
{
    assert(r >= 0 && r <= 1000 && "NCurses color values must be in the range [0, 1000]");
    assert(g >= 0 && g <= 1000 && "NCurses color values must be in the range [0, 1000]");
    assert(b >= 0 && b <= 1000 && "NCurses color values must be in the range [0, 1000]");

    if(!mColorCache.hasColorId(r, g, b))
    {
        short colorId = mColorCache.getColorId(r, g, b);
        init_color(colorId, r, g, b);
        return colorId;
    } 
    else 
    {
        return mColorCache.getColorId(r, g, b);
    }
}

short NCursesInterface::getColorPairId(const short colorId1, const short colorId2)
{
    assert(colorId1 >= 0 && "Color IDs must be non-negative");
    assert(colorId2 >= 0 && "Color IDs must be non-negative");

    if(!mColorCache.hasColorPairId(colorId1, colorId2))
    {
        short pairId = mColorCache.getColorPairId(colorId1, colorId2);
        init_pair(pairId, colorId1, colorId2);
        return pairId;
    } 
    else
    {
        return mColorCache.getColorPairId(colorId1, colorId2);
    }
}
// LCOV_EXCL_STOP
