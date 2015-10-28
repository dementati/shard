#pragma once

#include <fstream>
#include <memory>
#include <string>

#include "Logger.hpp"
#include "StreamLogger.hpp"

class LoggerFactory
{
    static LoggerFactory cInstance;
    LoggerFactory();
    ~LoggerFactory();

    std::ofstream mLogStream;
public:
    static std::unique_ptr<Logger> createLogger(const std::string unit, const Severity severity);
};
