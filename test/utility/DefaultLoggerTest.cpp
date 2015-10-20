#include <ctime>
#include <fstream>
#include <sstream>
#include <streambuf>
#include <string>

#include <gtest/gtest.h>

#include "../../src/core/Object.hpp"
#include "../../src/utility/DefaultLogger.hpp"

#define DEFAULT_TIMESTAMP 1445253011
#define DEFAULT_TIMESTAMP_STRING "2015-10-19 13:10:11"
#define DEFAULT_TEST_UNIT_NAME "TestUnit"
#define DEFAULT_MESSAGE "Test message"

class TestUnit : public Object
{
    DefaultLogger defaultLogger;

public:
    TestUnit() : defaultLogger(*this) {}

    const Logger& logger() const { return defaultLogger; }

    const std::string unitName() const { return std::string(DEFAULT_TEST_UNIT_NAME); }
};

class DefaultLoggerTest : public ::testing::Test
{
protected:
    std::streambuf *stdoutBuffer;
    const TestUnit unit;
    const DefaultLogger logger;
    const std::stringstream stdoutStream;

    DefaultLoggerTest()
        : logger(unit)
    {
        // Capture stdout
        stdoutBuffer = std::cout.rdbuf();
        std::cout.rdbuf(stdoutStream.rdbuf());    
    }

    ~DefaultLoggerTest()
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

TEST_F(DefaultLoggerTest, LogDebug)
{
    testLog("DEBUG", Severity::DEBUG);
}

TEST_F(DefaultLoggerTest, LogInfo)
{
    testLog("INFO", Severity::INFO);
}

TEST_F(DefaultLoggerTest, LogWarn)
{
    testLog("WARN", Severity::WARN);
}

TEST_F(DefaultLoggerTest, LogError)
{
    testLog("ERROR", Severity::ERROR);
}

TEST_F(DefaultLoggerTest, GetTimestampString)
{
    EXPECT_EQ(DEFAULT_TIMESTAMP_STRING, logger.getTimestampString(DEFAULT_TIMESTAMP));
}

TEST_F(DefaultLoggerTest, DebugSeverityToString)
{
    EXPECT_EQ(std::string("DEBUG"), DefaultLogger::severityToString(Severity::DEBUG));
}

TEST_F(DefaultLoggerTest, InfoSeverityToString)
{
    EXPECT_EQ(std::string("INFO"), DefaultLogger::severityToString(Severity::INFO));
}

TEST_F(DefaultLoggerTest, WarnSeverityToString)
{
    EXPECT_EQ(std::string("WARN"), DefaultLogger::severityToString(Severity::WARN));
}

TEST_F(DefaultLoggerTest, ErrorSeverityToString)
{
    EXPECT_EQ(std::string("ERROR"), DefaultLogger::severityToString(Severity::ERROR));
}

TEST_F(DefaultLoggerTest, ManualLogPrint)
{
    std::cout.rdbuf(stdoutBuffer);

    logger.debug(DEFAULT_MESSAGE);
    logger.info(DEFAULT_MESSAGE);
    logger.warn(DEFAULT_MESSAGE);
    logger.error(DEFAULT_MESSAGE);
}

TEST_F(DefaultLoggerTest, LogToString)
{
    std::stringstream logStream;
    std::string expectedEntry(buildExpectedEntry("DEBUG"));

    DefaultLogger stringLogger(unit, logStream);

    stringLogger.log(Severity::DEBUG, DEFAULT_TIMESTAMP, DEFAULT_MESSAGE);

    EXPECT_EQ(expectedEntry, logStream.str());
}

TEST_F(DefaultLoggerTest, LogToFile)
{
    std::string expectedEntry(buildExpectedEntry("DEBUG"));

    std::ofstream outFile;
    outFile.open("test.log");

    DefaultLogger fileLogger(unit, outFile);

    fileLogger.log(Severity::DEBUG, DEFAULT_TIMESTAMP, DEFAULT_MESSAGE);

    outFile.close();

    std::ifstream inFile;
    inFile.open("test.log");
    std::string logFileContents((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
    inFile.close();

    EXPECT_EQ(expectedEntry, logFileContents);
}
