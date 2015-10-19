#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>

#include <gtest/gtest.h>

#include "../../src/utility/defaultlogger.hpp"

class DefaultLoggerTest : public ::testing::Test
{
private:
    std::streambuf *stdoutBuffer;

protected:
    std::time_t timestamp = 1445253011;
    std::string timestampString;
    DefaultLogger logger;
    std::stringstream stdoutStream;

    DefaultLoggerTest()
        : timestampString("2015-10-19 13:10:11")
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
    expectedMessageStream << timestampString << ": " << message << std::endl;

    logger.log(timestamp, message);

    EXPECT_EQ(expectedMessageStream.str(), stdoutStream.str());
}

TEST_F(DefaultLoggerTest, GetTimestampString)
{
    EXPECT_EQ(timestampString, logger.getTimestampString(timestamp));
}
