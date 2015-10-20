#include "NCursesException.hpp"

NCursesException::NCursesException(const std::string message)
    : message(message)
{
}

const char* NCursesException::what() const throw()
{
    return message.c_str();
}
