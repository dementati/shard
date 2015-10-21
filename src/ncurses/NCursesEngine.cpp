#include "NCursesEngine.hpp"

NCursesEngine::NCursesEngine()
    : NCursesEngine(std::cout)
{
}

NCursesEngine::NCursesEngine(std::ostream &logStream)
    : defaultLogger(*this, logStream)
{
    defaultLogger.info("Initializing NCurses engine");

    if(!has_colors())
    {
        // TODO: Can't get this to work on mintty and this is too unimportant to waste time on 
        //       right now, but should be fixed later.
        // throw NCursesException("Terminal does not support colors.");
        defaultLogger.warn("Terminal does not support colors.");
    }

    initscr();
    raw();
    noecho();
    keypad(stdscr, TRUE);
}

NCursesEngine::~NCursesEngine()
{
    defaultLogger.info("Destroying NCurses engine");
    endwin();
}

const Logger& NCursesEngine::logger() const
{
    return defaultLogger;
}

const std::string NCursesEngine::unitName() const
{
    return "NCursesEngine";
}

void NCursesEngine::refreshScreen()
{
    refresh();
}

void NCursesEngine::draw(const char character, const int x, const int y, 
                         const short fr, const short fg, const short fb, 
                         const short br, const short bg, const short bb)
{
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

void NCursesEngine::draw(const char character, const int x, const int y)
{
    mvaddch(y, x, character);
}

const short NCursesEngine::getColorId(const short r, const short g, const short b)
{
    assert(r >= 0 && r <= 1000 && "NCurses color values must be in the range [0, 1000]");
    assert(g >= 0 && g <= 1000 && "NCurses color values must be in the range [0, 1000]");
    assert(b >= 0 && b <= 1000 && "NCurses color values must be in the range [0, 1000]");

    if(!colorCache.hasColorId(r, g, b))
    {
        short colorId = colorCache.getColorId(r, g, b);
        init_color(colorId, r, g, b);
        return colorId;
    } 
    else 
    {
        return colorCache.getColorId(r, g, b);
    }
}

const short NCursesEngine::getColorPairId(const short colorId1, const short colorId2)
{
    assert(colorId1 >= 0 && "Color IDs must be non-negative");
    assert(colorId2 >= 0 && "Color IDs must be non-negative");

    if(!colorCache.hasColorPairId(colorId1, colorId2))
    {
        short pairId = colorCache.getColorPairId(colorId1, colorId2);
        init_pair(pairId, colorId1, colorId2);
        return pairId;
    } 
    else
    {
        return colorCache.getColorPairId(colorId1, colorId2);
    }
}
