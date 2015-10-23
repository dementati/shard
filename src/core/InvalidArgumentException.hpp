#pragma once

#include "StringException.hpp"

// LCOV_EXCL_START
class InvalidArgumentException : public StringException 
{
public:
    InvalidArgumentException(const std::string message);
};
// LCOV_EXCL_STOP
