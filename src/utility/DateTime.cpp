#include "DateTime.hpp"

const std::string DateTime::getTimestampString(const time_t time)
{
    struct tm *timeStruct = localtime(&time);
    std::stringstream ss;
    ss << (timeStruct->tm_year + 1900) 
       << "-" 
       << (timeStruct->tm_mon + 1)
       << "-" 
       << (timeStruct->tm_mday)
       << " "
       << (timeStruct->tm_hour)
       << ":"
       << (timeStruct->tm_min)
       << ":"
       << (timeStruct->tm_sec);

    return ss.str();
}
