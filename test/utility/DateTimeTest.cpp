#include <gtest/gtest.h>

#include "../../src/utility/DateTime.hpp"

#define DEFAULT_TIMESTAMP 1445253011
#define DEFAULT_TIMESTAMP_STRING "2015-10-19 13:10:11"

class DateTimeTest : public ::testing::Test
{
};

TEST_F(DateTimeTest, GetTimestampString)
{
    EXPECT_EQ(DEFAULT_TIMESTAMP_STRING, DateTime::getTimestampString(DEFAULT_TIMESTAMP));
}
