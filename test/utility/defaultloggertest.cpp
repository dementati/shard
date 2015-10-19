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
};

TEST_F(DefaultLoggerTest, Log)
{
    std::string message("Test message");

    std::stringstream expectedMessageStream;
    expectedMessageStream << timestampString << "|" << DEFAULT_TEST_UNIT_NAME << ": " 
        << message << std::endl;

    logger.log(timestamp, message);

    EXPECT_EQ(expectedMessageStream.str(), stdoutStream.str());
}

TEST_F(DefaultLoggerTest, GetTimestampString)
{
    EXPECT_EQ(timestampString, logger.getTimestampString(timestamp));
}
