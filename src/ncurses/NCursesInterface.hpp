#pragma once

#include <iostream>
#include <ostream>
#include <string>

#include <ncurses.h>

#include "../utility/Assert.hpp"
#include "../utility/BitPattern.hpp"
#include "../utility/LoggerFactory.hpp"
#include "ColorCache.hpp"
#include "NCursesException.hpp"

class NCursesInterface
{
private:
    std::unique_ptr<Logger> mLogger;

    ColorCache mColorCache;    

    short getColorId(const short r, const short g, const short b);

    short getColorPairId(const short colorId1, const short colorId2);

public:
    NCursesInterface();

    virtual ~NCursesInterface();

    void refreshScreen();

    /* TODO: Look into when adding colors
    void draw(const char character, const int x, const int y, 
              const short fr, const short fg, const short fb,
              const short br, const short bg, const short bb);
    */

    void draw(const char character, const int x, const int y);
};
