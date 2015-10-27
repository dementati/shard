#pragma GCC diagnostic ignored "-Weffc++"

#include <ctime>
#include <fstream>
#include <sstream>
#include <streambuf>
#include <string>

#include <gtest/gtest.h>

#include "../../src/core/Object.hpp"
#include "../../src/utility/StreamLogger.hpp"

#define DEFAULT_TIMESTAMP 1445253011
#define DEFAULT_TIMESTAMP_STRING "2015-10-19 13:10:11"
#define DEFAULT_TEST_UNIT_NAME "TestUnit"
#define DEFAULT_MESSAGE "Test message"

class TestUnit : public Object
{
    StreamLogger defaultLogger;

public:
    TestUnit() : defaultLogger(*this) {}

    const Logger& logger() const { return defaultLogger; }

    const std::string unitName() const { return std::string(DEFAULT_TEST_UNIT_NAME); }
};

class StreamLoggerTest : public ::testing::Test
{
protected:
    std::streambuf *stdoutBuffer;
    const TestUnit unit;
    const StreamLogger logger;
    const std::stringstream stdoutStream;

    StreamLoggerTest()
        : logger(unit)
    {
        // Capture stdout
        stdoutBuffer = std::cout.rdbuf();
        std::cout.rdbuf(stdoutStream.rdbuf());    
    }

    ~StreamLoggerTest()
    {
        // Release stdout
        std::cout.rdbuf(stdoutBuffer);
    }

    void testLog(const Severity &severity)
    {
        logger.log(severity, DEFAULT_TIMESTAMP, DEFAULT_MESSAGE);
    }

    void testLog(const std::string &expectedSeverityString, const Severity &severity)
    {
        std::string expectedLogEntry = buildExpectedEntry(expectedSeverityString);

        testLog(severity);

        EXPECT_EQ(expectedLogEntry, stdoutStream.str());   
    }

    static const std::string buildExpectedEntry(const std::string &timestamp, const std::string &unit, const std::string &severity, const std::string &message)
    {
        std::stringstream expectedMessageStream;
        expectedMessageStream << timestamp << "|" 
            << unit << "|" 
            << severity << ": " 
            << message << std::endl;
        return expectedMessageStream.str();
    }

    static const std::string buildExpectedEntry(const std::string &severity)
    {
        return buildExpectedEntry(DEFAULT_TIMESTAMP_STRING, DEFAULT_TEST_UNIT_NAME, severity, DEFAULT_MESSAGE);
    }
};

TEST_F(StreamLoggerTest, LogDebug)
{
    testLog("DEBUG", Severity::DEBUG);
}

TEST_F(StreamLoggerTest, LogInfo)
{
    testLog("INFO", Severity::INFO);
}

TEST_F(StreamLoggerTest, LogWarn)
{
    testLog("WARN", Severity::WARN);
}

TEST_F(StreamLoggerTest, LogError)
{
    testLog("ERROR", Severity::ERROR);
}

TEST_F(StreamLoggerTest, GetTimestampString)
{
    EXPECT_EQ(DEFAULT_TIMESTAMP_STRING, logger.getTimestampString(DEFAULT_TIMESTAMP));
}

TEST_F(StreamLoggerTest, DebugSeverityToString)
{
    EXPECT_EQ(std::string("DEBUG"), StreamLogger::severityToString(Severity::DEBUG));
}

TEST_F(StreamLoggerTest, InfoSeverityToString)
{
    EXPECT_EQ(std::string("INFO"), StreamLogger::severityToString(Severity::INFO));
}

TEST_F(StreamLoggerTest, WarnSeverityToString)
{
    EXPECT_EQ(std::string("WARN"), StreamLogger::severityToString(Severity::WARN));
}

TEST_F(StreamLoggerTest, ErrorSeverityToString)
{
    EXPECT_EQ(std::string("ERROR"), StreamLogger::severityToString(Severity::ERROR));
}

TEST_F(StreamLoggerTest, ManualLogPrint)
{
    std::cout.rdbuf(stdoutBuffer);

    logger.debug(DEFAULT_MESSAGE);
    logger.info(DEFAULT_MESSAGE);
    logger.warn(DEFAULT_MESSAGE);
    logger.error(DEFAULT_MESSAGE);
}

TEST_F(StreamLoggerTest, LogToString)
{
    std::stringstream logStream;
    std::string expectedEntry(buildExpectedEntry("DEBUG"));

    StreamLogger stringLogger(unit, logStream);

    stringLogger.log(Severity::DEBUG, DEFAULT_TIMESTAMP, DEFAULT_MESSAGE);

    EXPECT_EQ(expectedEntry, logStream.str());
}

TEST_F(StreamLoggerTest, LogToFile)
{
    std::string expectedEntry(buildExpectedEntry("DEBUG"));

    std::ofstream outFile;
    outFile.open("test.log");

    StreamLogger fileLogger(unit, outFile);

    fileLogger.log(Severity::DEBUG, DEFAULT_TIMESTAMP, DEFAULT_MESSAGE);

    outFile.close();

    std::ifstream inFile;
    inFile.open("test.log");
    std::string logFileContents((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
    inFile.close();

    EXPECT_EQ(expectedEntry, logFileContents);
}
