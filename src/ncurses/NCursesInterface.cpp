#include "NCursesInterface.hpp"

char NCursesInterface::NoInput = ERR;

// LCOV_EXCL_START
NCursesInterface::NCursesInterface()
: 
    mLogger(LoggerFactory::createLogger("NCursesInterface", Severity::DEBUG)),
    mColorCache(ColorCache())
{
    mLogger->info("Initializing NCurses engine");

    if(!has_colors())
    {
        // TODO: Can't get this to work on mintty and this is too unimportant to waste time on 
        //       right now, but should be fixed later.
        // throw NCursesException("Terminal does not support colors.");
        mLogger->warn("Terminal does not support colors.");
    }

    initscr();
    raw();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    timeout(0);
}

NCursesInterface::~NCursesInterface()
{
    mLogger->info("Destroying NCurses engine");
    endwin();
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
    
    ASSERT(false, "This method hasn't been properly tested.");

    ASSERT(fr >= 0 && fr <= 1000, "NCurses color values must be in the range [0, 1000]");
    ASSERT(fg >= 0 && fg <= 1000, "NCurses color values must be in the range [0, 1000]");
    ASSERT(fb >= 0 && fb <= 1000, "NCurses color values must be in the range [0, 1000]");
    ASSERT(br >= 0 && br <= 1000, "NCurses color values must be in the range [0, 1000]");
    ASSERT(bg >= 0 && bg <= 1000, "NCurses color values must be in the range [0, 1000]");
    ASSERT(bb >= 0 && bb <= 1000, "NCurses color values must be in the range [0, 1000]");

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

void NCursesInterface::clearScreen()
{
    erase();
}

int NCursesInterface::getInput()
{
    return getch();
}

short NCursesInterface::getColorId(const short r, const short g, const short b)
{
    ASSERT(r >= 0 && r <= 1000, "NCurses color values must be in the range [0, 1000]");
    ASSERT(g >= 0 && g <= 1000, "NCurses color values must be in the range [0, 1000]");
    ASSERT(b >= 0 && b <= 1000, "NCurses color values must be in the range [0, 1000]");

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
    ASSERT(colorId1 >= 0, "Color IDs must be non-negative");
    ASSERT(colorId2 >= 0, "Color IDs must be non-negative");

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
