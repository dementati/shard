#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>

#include <gtest/gtest.h>

#include "../../src/core/object.hpp"
#include "../../src/utility/defaultlogger.hpp"

#define DEFAULT_TIMESTAMP 1445253011
#define DEFAULT_TIMESTAMP_STRING "2015-10-19 13:10:11"
#define DEFAULT_TEST_UNIT_NAME "TestUnit"

class TestUnit : public Object
{
public:
    const std::string unitName() const { return std::string(DEFAULT_TEST_UNIT_NAME); }
};

class DefaultLoggerTest : public ::testing::Test
{
private:
    std::streambuf *stdoutBuffer;

protected:
    std::time_t timestamp = DEFAULT_TIMESTAMP;
    std::string timestampString;
    TestUnit unit;
    DefaultLogger logger;
    std::stringstream stdoutStream;

    DefaultLoggerTest()
        : logger(unit), timestampString(DEFAULT_TIMESTAMP_STRING)
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

    void testLog(const std::string &expectedSeverityString, const Severity &severity)
    {
        std::string message("Test message");
        
        std::stringstream expectedMessageStream;
        expectedMessageStream << timestampString << "|" 
            << DEFAULT_TEST_UNIT_NAME << "|" 
            << expectedSeverityString << ": " 
            << message << std::endl;

        logger.log(severity, timestamp, message);

        EXPECT_EQ(expectedMessageStream.str(), stdoutStream.str());   
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
    EXPECT_EQ(timestampString, logger.getTimestampString(timestamp));
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

