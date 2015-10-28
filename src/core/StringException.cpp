#include "StringException.hpp"

// LCOV_EXCL_START
StringException::StringException(const std::string message)
    : mMessage(message)
{
}

const char* StringException::what() const throw()
{
    return mMessage.c_str();
}
// LCOV_EXCL_STOP
