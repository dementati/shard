#pragma once

#include <cassert>
#include <iostream>
#include <ostream>
#include <string>

#include <ncurses.h>

#include "../core/Object.hpp"
#include "../utility/BitPattern.hpp"
#include "../utility/StreamLogger.hpp"
#include "ColorCache.hpp"
#include "NCursesException.hpp"

class NCursesInterface : public Object
{
private:
    StreamLogger mLogger;

    ColorCache mColorCache;    

    short getColorId(const short r, const short g, const short b);

    short getColorPairId(const short colorId1, const short colorId2);

public:
    NCursesInterface();

    NCursesInterface(std::ostream &logStream);

    virtual ~NCursesInterface();

    const std::string unitName() const;

    void refreshScreen();

    /* TODO: Look into when adding colors
    void draw(const char character, const int x, const int y, 
              const short fr, const short fg, const short fb,
              const short br, const short bg, const short bb);
    */

    void draw(const char character, const int x, const int y);
};
