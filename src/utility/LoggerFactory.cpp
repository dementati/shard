#include "LoggerFactory.hpp"

LoggerFactory LoggerFactory::cInstance;

LoggerFactory::LoggerFactory()
:
    mLogStream()
{
    mLogStream.open(DateTime::getTimestampString(std::time(nullptr)) + ".log");
}

LoggerFactory::~LoggerFactory()
{
    mLogStream.close();
}

LoggerPtr LoggerFactory::createLogger(const std::string unit, 
    const Severity minSeverity)
{
    return std::make_shared<StreamLogger>(unit, cInstance.mLogStream, minSeverity);
    //return std::make_unique<StreamLogger>(unit, std::cout, minSeverity);
}
