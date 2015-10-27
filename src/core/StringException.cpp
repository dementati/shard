#include "StringException.hpp"

// LCOV_EXCL_START
StringException::StringException(const std::string message)
    : exceptionMessage(message)
{
}

const char* StringException::what() const throw()
{
    return exceptionMessage.c_str();
}
// LCOV_EXCL_STOP
