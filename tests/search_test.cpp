#include "imgsim/search.hpp"

#include <cstdint>
#include <gtest/gtest.h>
#include <vector>

TEST(BruteForceKTest, ReturnsEmptyForEmptyDataset) {
    const std::vector<std::uint64_t> hashes;
    const auto result = imgsim::brute_force_k(0ull, hashes, 3);
    EXPECT_TRUE(result.empty());
}

TEST(BruteForceKTest, ReturnsClosestHash) {
    const std::vector<std::uint64_t> hashes = {
        0b1111ull,
        0b0001ull,
        0b0011ull
    };
    const auto result = imgsim::brute_force_k(0b0000ull, hashes, 1);
    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0].index, 1);
    EXPECT_EQ(result[0].hash, 0b0001ull);
    EXPECT_EQ(result[0].distance, 1);
}

TEST(BruteForceKTest, ReturnsTopKInDistanceOrder) {
    const std::vector<std::uint64_t> hashes = {
        0b1111ull,
        0b0001ull,
        0b0011ull,
        0b0000ull
    };
    const auto result = imgsim::brute_force_k(0b0000ull, hashes, 3);
    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0].index, 3);
    EXPECT_EQ(result[0].hash, 0b0000ull);
    EXPECT_EQ(result[0].distance, 0);
    EXPECT_EQ(result[1].index, 1);
    EXPECT_EQ(result[1].hash, 0b0001ull);
    EXPECT_EQ(result[1].distance, 1);
    EXPECT_EQ(result[2].index, 2);
    EXPECT_EQ(result[2].hash, 0b0011ull);
    EXPECT_EQ(result[2].distance, 2);
}

TEST(BruteForceKTest, KGreaterThanDatasetSizeReturnsAll) {
    const std::vector<std::uint64_t> hashes = {
        0b0000ull,
        0b0001ull
    };
    const auto result = imgsim::brute_force_k(0b0000ull, hashes, 10);
    ASSERT_EQ(result.size(), 2);
    EXPECT_EQ(result[0].index, 0);
    EXPECT_EQ(result[0].distance, 0);
    EXPECT_EQ(result[1].index, 1);
    EXPECT_EQ(result[1].distance, 1);
}

TEST(BruteForceKTest, TieBreaksByIndex) {
    const std::vector<std::uint64_t> hashes = {
        0b0011ull,
        0b0101ull
    };
    const auto result = imgsim::brute_force_k(0b0000ull, hashes, 2);
    ASSERT_EQ(result.size(), 2);
    EXPECT_EQ(result[0].index, 0);
    EXPECT_EQ(result[0].distance, 2);
    EXPECT_EQ(result[1].index, 1);
    EXPECT_EQ(result[1].distance, 2);
}
