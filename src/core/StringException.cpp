#include "StringException.hpp"

// LCOV_EXCL_START
StringException::StringException(const std::string message)
    : message(message)
{
}

const char* StringException::what() const throw()
{
    return message.c_str();
}
// LCOV_EXCL_STOP
