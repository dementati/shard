#include "NCursesException.hpp"

// LCOV_EXCL_START
NCursesException::NCursesException(const std::string message)
    : message(message)
{
}

const char* NCursesException::what() const throw()
{
    return message.c_str();
}
// LCOV_EXCL_STOP
