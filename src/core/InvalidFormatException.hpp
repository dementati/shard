#pragma once

#include "StringException.hpp"

// LCOV_EXCL_START
class InvalidFormatException : public StringException 
{
public:
    InvalidFormatException(const std::string message);
};
// LCOV_EXCL_STOP
