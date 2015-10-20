#pragma once

#include <cassert>
#include <iostream>
#include <ostream>
#include <string>

#include <ncurses.h>

#include "../core/object.hpp"
#include "../utility/BitPattern.hpp"
#include "../utility/DefaultLogger.hpp"
#include "ColorCache.hpp"
#include "NCursesException.hpp"

class NCursesEngine : public Object
{
public:
    NCursesEngine();

    NCursesEngine(std::ostream &logStream);

    virtual ~NCursesEngine();

    const Logger& logger() const;

    const std::string unitName() const;

    void redraw();

    void addCharacter(const char character, const short fr, const short fg, const short fb,
        const short br, const short bg, const short bb);

private:
    DefaultLogger defaultLogger;

    ColorCache colorCache;    

    const short getColorId(const short r, const short g, const short b);

    const short getColorPairId(const short colorId1, const short colorId2);
};
