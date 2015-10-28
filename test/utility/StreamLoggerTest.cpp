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
    StreamLogger mDefaultLogger;

public:
    TestUnit() 
    : 
        mDefaultLogger(*this) 
    {}

    const Logger& logger() const { return mDefaultLogger; }

    const std::string unitName() const { return std::string(DEFAULT_TEST_UNIT_NAME); }
};

class StreamLoggerTest : public ::testing::Test
{
protected:
    std::streambuf *mStdoutBuffer;
    const TestUnit mUnit;
    const StreamLogger mLogger;
    const std::stringstream mStdoutStream;

    StreamLoggerTest()
    : 
        mLogger(mUnit)
    {
        // Capture stdout
        mStdoutBuffer = std::cout.rdbuf();
        std::cout.rdbuf(mStdoutStream.rdbuf());    
    }

    ~StreamLoggerTest()
    {
        // Release stdout
        std::cout.rdbuf(mStdoutBuffer);
    }

    void testLog(const Severity &severity)
    {
        mLogger.log(severity, DEFAULT_TIMESTAMP, DEFAULT_MESSAGE);
    }

    void testLog(const std::string &expectedSeverityString, const Severity &severity)
    {
        std::string expectedLogEntry = buildExpectedEntry(expectedSeverityString);

        testLog(severity);

        EXPECT_EQ(expectedLogEntry, mStdoutStream.str());   
    }

    static const std::string buildExpectedEntry(const std::string &timestamp, const std::string &mUnit, const std::string &severity, const std::string &message)
    {
        std::stringstream expectedMessageStream;
        expectedMessageStream << timestamp << "|" 
            << mUnit << "|" 
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
    EXPECT_EQ(DEFAULT_TIMESTAMP_STRING, mLogger.getTimestampString(DEFAULT_TIMESTAMP));
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
    std::cout.rdbuf(mStdoutBuffer);

    mLogger.debug(DEFAULT_MESSAGE);
    mLogger.info(DEFAULT_MESSAGE);
    mLogger.warn(DEFAULT_MESSAGE);
    mLogger.error(DEFAULT_MESSAGE);
}

TEST_F(StreamLoggerTest, LogToString)
{
    std::stringstream logStream;
    std::string expectedEntry(buildExpectedEntry("DEBUG"));

    StreamLogger stringLogger(mUnit, logStream);

    stringLogger.log(Severity::DEBUG, DEFAULT_TIMESTAMP, DEFAULT_MESSAGE);

    EXPECT_EQ(expectedEntry, logStream.str());
}

TEST_F(StreamLoggerTest, LogToFile)
{
    std::string expectedEntry(buildExpectedEntry("DEBUG"));

    std::ofstream outFile;
    outFile.open("test.log");

    StreamLogger fileLogger(mUnit, outFile);

    fileLogger.log(Severity::DEBUG, DEFAULT_TIMESTAMP, DEFAULT_MESSAGE);

    outFile.close();

    std::ifstream inFile;
    inFile.open("test.log");
    std::string logFileContents((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
    inFile.close();

    EXPECT_EQ(expectedEntry, logFileContents);
}
