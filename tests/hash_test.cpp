#include "imgsim/hash.hpp"
#include "test_helpers.hpp"

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

TEST(AverageHashTest, UniformImageProducesZeroHash) {
    imgsim::GrayScale image{
        .width = 8,
        .height = 8,
        .data = std::vector<std::uint8_t>(64, 100), };
    EXPECT_EQ(imgsim::average_hash(image), 0ull);
}

/*
0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0
0   0   0   0   0   0   0   0
255 255 255 255 255 255 255 255
255 255 255 255 255 255 255 255
255 255 255 255 255 255 255 255
255 255 255 255 255 255 255 255
*/
TEST(AverageHashTest, BrightBottomHalfSetsLowerThirtyTwoBits) {
    std::vector<std::uint8_t> pixels(64, 0);
    std::fill(pixels.begin() + 32,pixels.end(),255);
    imgsim::GrayScale image{.width = 8,.height = 8,.data = pixels,};
    EXPECT_EQ(imgsim::average_hash(image),0x00000000FFFFFFFFull);
}

TEST(AverageHashTest, ExactTwoPicsHash) {
    imgsim::ImgHash fhash = imgsim::average_hash(test_helpers::data_test_path("pic1_test.jbg"));
    imgsim::ImgHash shash = imgsim::average_hash(test_helpers::data_test_path("pic2_test.jbg"));
    EXPECT_EQ(imgsim::hamming_distance(fhash, shash), 0);
}