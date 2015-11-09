#pragma once

#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <sstream>

#define GLM_FORCE_RADIANS
#include <glm/gtx/string_cast.hpp>

#include "Logger.hpp"
#include "StreamLogger.hpp"

#if defined(LOG_LEVEL_DEBUG)
#   define LOG_DEBUG(logger, message) \
    do { \
        std::stringstream ss;\
        ss << message;\
        logger->debug(ss.str());\
    } while (false)
#else
#   define LOG_DEBUG(logger, message) do { } while (false)
#endif

#if defined(LOG_LEVEL_DEBUG) || defined(LOG_LEVEL_INFO)
#   define LOG_INFO(logger, message) \
    do { \
        std::stringstream ss;\
        ss << message;\
        logger->info(ss.str());\
    } while (false)
#else
#   define LOG_INFO(logger, message) do { } while (false)
#endif

#if defined(LOG_LEVEL_DEBUG) || defined(LOG_LEVEL_INFO) || defined(LOG_LEVEL_WARN)
#   define LOG_WARN(logger, message) \
    do { \
        std::stringstream ss;\
        ss << message;\
        logger->warn(ss.str());\
    } while (false)
#else
#   define LOG_WARN(logger, message) do { } while (false)
#endif

#if defined(LOG_LEVEL_DEBUG) || defined(LOG_LEVEL_INFO) || defined(LOG_LEVEL_WARN) || defined(LOG_LEVEL_ERROR)
#   define LOG_ERROR(logger, message) \
    do { \
        std::stringstream ss;\
        ss << message;\
        logger->error(ss.str());\
    } while (false)
#else
#   define LOG_ERROR(logger, message) do { } while (false)
#endif

using LoggerPtr = std::shared_ptr<Logger>;

class LoggerFactory
{
    static LoggerFactory cInstance;
    LoggerFactory();
    ~LoggerFactory();

    std::ofstream mLogStream;
public:
    static LoggerPtr createLogger(const std::string unit, const Severity severity);
};
