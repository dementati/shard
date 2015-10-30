#include "StreamLogger.hpp"

StreamLogger::StreamLogger(const std::string unit, std::ostream &logStream, const Severity minSeverity)
: 
    mUnit(unit), 
    mLogStream(logStream),
    mMinSeverity(minSeverity)
{
}

// LCOV_EXCL_START
void StreamLogger::log(const Severity &severity, const std::string &message) const
{
    log(severity, std::time(nullptr), message);
}

void StreamLogger::debug(const std::string &message) const 
{
    #if defined(LOG_LEVEL_DEBUG)
    log(Severity::DEBUG, message);
    #endif 
}

void StreamLogger::info(const std::string &message) const 
{
    #if defined(LOG_LEVEL_DEBUG) || defined(LOG_LEVEL_INFO)
    log(Severity::INFO, message);
    #endif
}

void StreamLogger::warn(const std::string &message) const 
{
    #if defined(LOG_LEVEL_DEBUG) || defined(LOG_LEVEL_INFO) || defined(LOG_LEVEL_WARN)
    log(Severity::WARN, message);
    #endif
}

void StreamLogger::error(const std::string &message) const 
{
    #if defined(LOG_LEVEL_DEBUG) || defined(LOG_LEVEL_INFO) || defined(LOG_LEVEL_WARN) || defined(LOG_LEVEL_ERROR)
    log(Severity::ERROR, message);
    #endif
}
// LCOV_EXCL_STOP

void StreamLogger::log(const Severity &severity, const time_t timestamp, 
    const std::string &message) const
{
    if(severity >= mMinSeverity)
    {
        mLogStream << DateTime::getTimestampString(timestamp) << "|" 
                   << mUnit << "|"
                   << severityToString(severity) << ": "
                   << message << std::endl;
    }
}

std::string StreamLogger::severityToString(const Severity &severity)
{
    switch(severity)
    {
        case Severity::DEBUG: return std::string("DEBUG");
        case Severity::INFO: return std::string("INFO");
        case Severity::WARN: return std::string("WARN");
        case Severity::ERROR: return std::string("ERROR");

        // LCOV_EXCL_START
        default: assert(false && "Severity not handled");
        // LCOV_EXCL_STOP
    }
}
