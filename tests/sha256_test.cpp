#include <imgsim/sha256.hpp>
#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>
#include <array>

TEST(Sha256FileTest, ChecksSHA256) {
    /* okay at first ill get sha256 of string "hello" in terminal by openssl
        echo -n "hello" | openssl dgst -sha256
        returned SHA2-256(stdin)= 2cf24dba5fb0a30e26e83b2ac5b9e29e1b161e5c1fa7425e73043362938b9824
        so now i need to read some file from temp directorywith word hello and it will return the same hash
    */
    const std::filesystem::path tempFilePath = std::filesystem::temp_directory_path() / "imgsim_sha256_hello_test.txt";
    std::filesystem::remove(tempFilePath); //remove if exists
    {
        std::ofstream file(tempFilePath, std::ios::binary);
        ASSERT_TRUE(file.is_open());
        file << "hello";
        ASSERT_TRUE(file.good());
    }
    const imgsim::sha256_hash_t expectedHash = {
        0x2c, 0xf2, 0x4d, 0xba, 0x5f, 0xb0, 0xa3, 0x0e,
        0x26, 0xe8, 0x3b, 0x2a, 0xc5, 0xb9, 0xe2, 0x9e,
        0x1b, 0x16, 0x1e, 0x5c, 0x1f, 0xa7, 0x42, 0x5e,
        0x73, 0x04, 0x33, 0x62, 0x93, 0x8b, 0x98, 0x24
    }; //as we got from openssl command
    const imgsim::sha256_hash_t actualHash = imgsim::sha256_file(tempFilePath);
    EXPECT_EQ(actualHash, expectedHash); // check equality of hashes
    std::filesystem::remove(tempFilePath); //cleanup
}