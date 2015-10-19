#include "defaultlogger.hpp"

DefaultLogger::DefaultLogger(const Object &unit)
    : DefaultLogger(unit, std::cout)
{
}

DefaultLogger::DefaultLogger(const Object &unit, std::ostream &logStream)
    : unit(unit), logStream(logStream)
{
}

// LCOV_EXCL_START
void DefaultLogger::log(const Severity &severity, const std::string &message) const
{
    log(severity, std::time(nullptr), message);
}

void DefaultLogger::debug(const std::string &message) const 
{
    #if defined(LOG_LEVEL_DEBUG)
    log(Severity::DEBUG, message);
    #endif 
}

void DefaultLogger::info(const std::string &message) const 
{
    #if defined(LOG_LEVEL_DEBUG) || defined(LOG_LEVEL_INFO)
    log(Severity::INFO, message);
    #endif
}

void DefaultLogger::warn(const std::string &message) const 
{
    #if defined(LOG_LEVEL_DEBUG) || defined(LOG_LEVEL_INFO) || defined(LOG_LEVEL_WARN)
    log(Severity::WARN, message);
    #endif
}

void DefaultLogger::error(const std::string &message) const 
{
    #if defined(LOG_LEVEL_DEBUG) || defined(LOG_LEVEL_INFO) || defined(LOG_LEVEL_WARN) || defined(LOG_LEVEL_ERROR)
    log(Severity::ERROR, message);
    #endif
}
// LCOV_EXCL_STOP

void DefaultLogger::log(const Severity &severity, const time_t timestamp, 
    const std::string &message) const
{
    logStream << getTimestampString(timestamp) << "|" 
              << unit.unitName() << "|"
              << severityToString(severity) << ": "
              << message << std::endl;
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

std::string DefaultLogger::severityToString(const Severity &severity)
{
    switch(severity)
    {
        case Severity::DEBUG: return std::string("DEBUG");
        case Severity::INFO: return std::string("INFO");
        case Severity::WARN: return std::string("WARN");
        case Severity::ERROR: return std::string("ERROR");
    }
}
