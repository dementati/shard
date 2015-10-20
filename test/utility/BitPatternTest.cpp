#include <cstdint>

#include <gtest/gtest.h>

#include "../../src/utility/BitPattern.hpp"

class BitPatternTest : public ::testing::Test
{
};

TEST_F(BitPatternTest, Concatenate_3_16bit_ints_zeroes)
{
    EXPECT_EQ(0, BitPattern::concatenate(0, 0, 0));
}

TEST_F(BitPatternTest, Concatenate_3_16bit_ints_ones)
{
    uint16_t a = 0b0000000000000001;
    uint16_t b = 0b0000000000000001;
    uint16_t c = 0b0000000000000001;
    uint64_t expected = 0b0000000000000000000000000000000100000000000000010000000000000001;

    EXPECT_EQ(expected, BitPattern::concatenate(a, b, c));
}

TEST_F(BitPatternTest, Concatenate_3_16bit_ints_oneTwoThree)
{
    uint16_t a = 0b0000000000000001;
    uint16_t b = 0b0000000000000010;
    uint16_t c = 0b0000000000000011;
    uint64_t expected = 0b0000000000000000000000000000000100000000000000100000000000000011;

    EXPECT_EQ(expected, BitPattern::concatenate(a, b, c));
}

TEST_F(BitPatternTest, Concatenate_2_16bit_ints_zeroes)
{
    EXPECT_EQ(0, BitPattern::concatenate(0, 0));
}

TEST_F(BitPatternTest, Concatenate_2_16bit_ints_ones)
{
    uint16_t a = 0b0000000000000001;
    uint16_t b = 0b0000000000000001;
    uint32_t expected = 0b00000000000000010000000000000001;

    EXPECT_EQ(expected, BitPattern::concatenate(a, b));
}

TEST_F(BitPatternTest, Concatenate_2_16bit_ints_oneTwo)
{
    uint16_t a = 0b0000000000000001;
    uint16_t b = 0b0000000000000010;
    uint32_t expected = 0b00000000000000010000000000000010;

    EXPECT_EQ(expected, BitPattern::concatenate(a, b));
}
