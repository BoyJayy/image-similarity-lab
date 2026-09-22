#include <imgsim/sha256.hpp>
#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>
#include <array>
#include <stdexcept>
#include <string>

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

/*TEST (Sha256FileTest, TwoExactPictures) {
    const std::filesystem::path tempFilePath1 = get_file_path("pic1_test.png");
    ASSERT_TRUE(std::filesystem::exists(tempFilePath1));
    const std::filesystem::path tempFilePath2 = get_file_path("pic2_test.png");
    ASSERT_TRUE(std::filesystem::exists(tempFilePath2));
    const imgsim::sha256_hash_t hash1 = imgsim::sha256_file(tempFilePath1);
    const imgsim::sha256_hash_t hash2 = imgsim::sha256_file(tempFilePath2);
    EXPECT_NE(hash1, hash2); // check equality of hashes for two identical pictures
}*/

TEST(Sha256FileTest, ReadsDataAfterFirstBuffer) {
    const std::filesystem::path temp_directory =
        std::filesystem::temp_directory_path()
        / "imgsim_sha256_large_file_test";

    std::filesystem::remove_all(temp_directory);
    std::filesystem::create_directories(temp_directory);
    const std::filesystem::path first_path =
        temp_directory / "first.bin";
    const std::filesystem::path second_path =
        temp_directory / "second.bin";
    const std::string common_data(1024 * 1024, 'a');
    {
        std::ofstream first_file(first_path, std::ios::binary);
        std::ofstream second_file(second_path, std::ios::binary);
        ASSERT_TRUE(first_file.is_open());
        ASSERT_TRUE(second_file.is_open());
        first_file.write(
            common_data.data(),
            static_cast<std::streamsize>(common_data.size())
        );
        second_file.write(
            common_data.data(),
            static_cast<std::streamsize>(common_data.size())
        );
        // these bytes are after the first 1 MiB buffer.
        first_file.put('x');
        second_file.put('y');
        ASSERT_TRUE(first_file.good());
        ASSERT_TRUE(second_file.good());
    }
    EXPECT_NE(
        imgsim::sha256_file(first_path),
        imgsim::sha256_file(second_path)
    );
    std::filesystem::remove_all(temp_directory);
}

TEST(Sha256FileTest, MissingFileThrows) {
    const auto missingPath =std::filesystem::temp_directory_path() /"imgsim_definitely_missing_file.bin";
    std::filesystem::remove(missingPath);
    EXPECT_THROW(imgsim::sha256_file(missingPath),std::runtime_error);
}