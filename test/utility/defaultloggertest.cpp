#include <string>
#include <sstream>

#include <gtest/gtest.h>

#include "../../src/utility/defaultlogger.hpp"

class DefaultLoggerTest : public ::testing::Test
{
private:
    std::streambuf *stdoutBuffer;

protected:
    std::stringstream stdoutStream;

    DefaultLoggerTest()
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
    DefaultLogger logger;
    std::string message("Test message");
    std::stringstream ss;
    ss << message << std::endl;
    std::string expectedMessage(ss.str());

    logger.log(message);

    EXPECT_EQ(expectedMessage, stdoutStream.str());
}
