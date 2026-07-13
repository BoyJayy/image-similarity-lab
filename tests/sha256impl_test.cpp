#include "imgsim/sha256impl.hpp"

#include <cstdint>
#include <gtest/gtest.h>

TEST(Sha256Test, MainTest) {
    imgsim::SHA256 sha256;
    sha256.update("Hello, world!", 13);
    std::string hash = sha256.hash();
    EXPECT_EQ(hash, "315f5bdb76d078c43b8ac0064e4a0164612b1fce77c869345bfc94c75894edd3");
}
