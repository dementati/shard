#pragma GCC diagnostic ignored "-Weffc++"

#include <ctime>
#include <fstream>
#include <sstream>
#include <streambuf>
#include <string>

#include <gtest/gtest.h>

#include "../../src/utility/StreamLogger.hpp"

#define DEFAULT_TIMESTAMP 1445253011
#define DEFAULT_TIMESTAMP_STRING "2015-10-19 13:10:11"
#define DEFAULT_TEST_UNIT_NAME "TestUnit"
#define DEFAULT_MESSAGE "Test message"

class StreamLoggerTest : public ::testing::Test
{
protected:
    const std::string mUnit;
    const StreamLogger mDefaultLogger;
    std::streambuf *mStdoutBuffer;
    const std::stringstream mStdoutStream;

    StreamLoggerTest()
    :
        mUnit("TestUnit"),
        mDefaultLogger(mUnit, std::cout, Severity::DEBUG)
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

    void testLog(const Severity logSeverity)
    {
        mDefaultLogger.log(logSeverity, DEFAULT_TIMESTAMP, DEFAULT_MESSAGE);
    }

    void testLog(const std::string &expectedSeverityString, const Severity logSeverity)
    {
        std::string expectedLogEntry = buildExpectedEntry(expectedSeverityString);

        testLog(logSeverity);

        EXPECT_EQ(expectedLogEntry, mStdoutStream.str());   
    }

    void testNoLogWithMinSeverity(const Severity minSeverity, const Severity logSeverity)
    {
        StreamLogger logger(mUnit, std::cout, minSeverity); 

        logger.log(logSeverity, DEFAULT_TIMESTAMP, DEFAULT_MESSAGE);

        EXPECT_EQ(std::string(), mStdoutStream.str());
    }

    void testLogWithMinSeverity(const std::string expectedSeverityString, const Severity minSeverity, const Severity logSeverity)
    {
        std::string expectedLogEntry = buildExpectedEntry(expectedSeverityString);

        StreamLogger logger(mUnit, std::cout, minSeverity); 

        logger.log(logSeverity, DEFAULT_TIMESTAMP, DEFAULT_MESSAGE);

        EXPECT_EQ(expectedLogEntry, mStdoutStream.str());
    }

    static const std::string buildExpectedEntry(const std::string &timestamp, 
        const std::string &mUnit, const std::string &severity, const std::string &message)
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

    mDefaultLogger.debug(DEFAULT_MESSAGE);
    mDefaultLogger.info(DEFAULT_MESSAGE);
    mDefaultLogger.warn(DEFAULT_MESSAGE);
    mDefaultLogger.error(DEFAULT_MESSAGE);
}

TEST_F(StreamLoggerTest, LogToString)
{
    std::stringstream logStream;
    std::string expectedEntry(buildExpectedEntry("DEBUG"));

    StreamLogger stringLogger(mUnit, logStream, Severity::DEBUG);

    stringLogger.log(Severity::DEBUG, DEFAULT_TIMESTAMP, DEFAULT_MESSAGE);

    EXPECT_EQ(expectedEntry, logStream.str());
}

TEST_F(StreamLoggerTest, LogToFile)
{
    std::string expectedEntry(buildExpectedEntry("DEBUG"));

    std::ofstream outFile;
    outFile.open("test.log");

    StreamLogger fileLogger(mUnit, outFile, Severity::DEBUG);

    fileLogger.log(Severity::DEBUG, DEFAULT_TIMESTAMP, DEFAULT_MESSAGE);

    outFile.close();

    std::ifstream inFile;
    inFile.open("test.log");
    std::string logFileContents((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
    inFile.close();

    EXPECT_EQ(expectedEntry, logFileContents);
}

TEST_F(StreamLoggerTest, MinSeverityDebug_LogSeverityDebug)
{
    testLogWithMinSeverity("DEBUG", Severity::DEBUG, Severity::DEBUG);
}

TEST_F(StreamLoggerTest, MinSeverityDebug_LogSeverityInfo)
{
    testLogWithMinSeverity("INFO", Severity::DEBUG, Severity::INFO);
}

TEST_F(StreamLoggerTest, MinSeverityDebug_LogSeverityWarn)
{
    testLogWithMinSeverity("WARN", Severity::DEBUG, Severity::WARN);
}

TEST_F(StreamLoggerTest, MinSeverityDebug_LogSeverityError)
{
    testLogWithMinSeverity("ERROR", Severity::DEBUG, Severity::ERROR);
}

TEST_F(StreamLoggerTest, MinSeverityInfo_LogSeverityDebug)
{
    testNoLogWithMinSeverity(Severity::INFO, Severity::DEBUG);
}

TEST_F(StreamLoggerTest, MinSeverityInfo_LogSeverityInfo)
{
    testLogWithMinSeverity("INFO", Severity::INFO, Severity::INFO);
}

TEST_F(StreamLoggerTest, MinSeverityInfo_LogSeverityWarn)
{
    testLogWithMinSeverity("WARN", Severity::INFO, Severity::WARN);
}

TEST_F(StreamLoggerTest, MinSeverityInfo_LogSeverityError)
{
    testLogWithMinSeverity("ERROR", Severity::INFO, Severity::ERROR);
}

TEST_F(StreamLoggerTest, MinSeverityWarn_LogSeverityDebug)
{
    testNoLogWithMinSeverity(Severity::WARN, Severity::DEBUG);
}

TEST_F(StreamLoggerTest, MinSeverityWarn_LogSeverityInfo)
{
    testNoLogWithMinSeverity(Severity::WARN, Severity::INFO);
}

TEST_F(StreamLoggerTest, MinSeverityWarn_LogSeverityWarn)
{
    testLogWithMinSeverity("WARN", Severity::WARN, Severity::WARN);
}

TEST_F(StreamLoggerTest, MinSeverityWarn_LogSeverityError)
{
    testLogWithMinSeverity("ERROR", Severity::WARN, Severity::ERROR);
}

TEST_F(StreamLoggerTest, MinSeverityError_LogSeverityDebug)
{
    testNoLogWithMinSeverity(Severity::ERROR, Severity::DEBUG);
}

TEST_F(StreamLoggerTest, MinSeverityError_LogSeverityInfo)
{
    testNoLogWithMinSeverity(Severity::ERROR, Severity::INFO);
}

TEST_F(StreamLoggerTest, MinSeverityError_LogSeverityWarn)
{
    testNoLogWithMinSeverity(Severity::ERROR, Severity::WARN);
}

TEST_F(StreamLoggerTest, MinSeverityError_LogSeverityError)
{
    testLogWithMinSeverity("ERROR", Severity::ERROR, Severity::ERROR);
}
