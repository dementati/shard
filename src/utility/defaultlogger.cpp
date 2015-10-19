#include "defaultlogger.hpp"

// LCOV_EXCL_START
void DefaultLogger::log(std::string message) 
{
    log(std::time(nullptr), message);
}
// LCOV_EXCL_STOP

void DefaultLogger::log(time_t timestamp, std::string message)
{
    std::cout << getTimestampString(timestamp) << ": " << message << std::endl;
}

std::string DefaultLogger::getTimestampString(time_t time)
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
