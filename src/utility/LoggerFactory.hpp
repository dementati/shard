#pragma once

#include <fstream>
#include <iostream>
#include <memory>
#include <string>

#define GLM_FORCE_RADIANS
#include <glm/gtx/string_cast.hpp>

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
