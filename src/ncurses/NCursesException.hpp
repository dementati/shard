#pragma once

#include <exception>
#include <string>

class NCursesException : public std::exception
{
    const std::string message;

public:
    NCursesException(const std::string message);

    virtual const char* what() const throw();
};
