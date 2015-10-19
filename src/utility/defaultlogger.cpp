#include "defaultlogger.hpp"

DefaultLogger::DefaultLogger(const Object &unit)
    : unit(unit)
{
}

// LCOV_EXCL_START
void DefaultLogger::log(const std::string message) const 
{
    log(std::time(nullptr), message);
}
// LCOV_EXCL_STOP

void DefaultLogger::log(const time_t timestamp, const std::string &message) const
{
    std::cout << getTimestampString(timestamp) << "|" << unit.unitName() << ": " << message << std::endl;
}

const std::string DefaultLogger::getTimestampString(const time_t time) const
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
