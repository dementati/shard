#pragma once

#include <ctime>
#include <sstream>

class DateTime
{
public:
    static const std::string getTimestampString(const time_t time); 
};
