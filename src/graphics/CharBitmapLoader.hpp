#pragma once 

#include <fstream>
#include <ostream>
#include <sstream>
#include <string>

#include "../core/InvalidArgumentException.hpp"
#include "../core/InvalidFormatException.hpp"
#include "../utility/LoggerFactory.hpp"
#include "CharBitmap.hpp"

// LCOV_EXCL_START
class CharBitmapLoader
{
    std::unique_ptr<Logger> mLogger;

    std::string trimCarriageReturn(std::string line) const;

public:
    CharBitmapLoader();

    CharBitmap load(const std::string filePath) const;
};
// LCOV_EXCL_STOP
