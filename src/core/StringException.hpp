#pragma once

#include <exception>
#include <string>

// LCOV_EXCL_START
class StringException : public std::exception
{
    const std::string message;

public:
    StringException(const std::string message);

    virtual const char* what() const throw();
};
// LCOV_EXCL_STOP
