#include "imgsim/hash.hpp"

#include <cstdint>
#include <gtest/gtest.h>

TEST(HammingDistanceTest, EqualHashesHaveZeroDistance) {
    EXPECT_EQ(imgsim::hamming_distance(0ull, 0ull), 0);
    EXPECT_EQ(imgsim::hamming_distance(42ull, 42ull), 0);
    EXPECT_EQ(imgsim::hamming_distance(0x123456789ABCDEF0ull, 0x123456789ABCDEF0ull), 0);
}

TEST(HammingDistanceTest, OneBitDifference) {
    EXPECT_EQ(imgsim::hamming_distance(0ull, 1ull), 1);
    EXPECT_EQ(imgsim::hamming_distance(0b0000ull, 0b0010ull), 1);
}

TEST(HammingDistanceTest, MultipleBitDifference) {
    EXPECT_EQ(imgsim::hamming_distance(0b0000ull, 0b1111ull), 4);
    EXPECT_EQ(imgsim::hamming_distance(0b101010ull, 0b111000ull), 2);
}

TEST(HammingDistanceTest, AllBitsDifferent) {
    EXPECT_EQ(imgsim::hamming_distance(0ull, ~0ull), 64);
}
