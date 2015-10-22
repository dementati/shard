#pragma once

#include "../core/StringException.hpp"

// LCOV_EXCL_START
class NCursesException : public StringException 
{
    NCursesException(const std::string message);
};
// LCOV_EXCL_STOP
