#pragma once 

#include <fstream>
#include <ostream>
#include <sstream>
#include <string>

#include "../core/InvalidArgumentException.hpp"
#include "../core/InvalidFormatException.hpp"
#include "../core/Object.hpp"
#include "../utility/StreamLogger.hpp"
#include "CharBitmap.hpp"

// LCOV_EXCL_START
class CharBitmapLoader : public Object
{
    StreamLogger mLogger;

    std::string trimCarriageReturn(std::string line) const;

public:
    CharBitmapLoader(std::ostream &logStream);

    const std::string unitName() const;

    CharBitmap load(const std::string filePath) const;
};
// LCOV_EXCL_STOP
