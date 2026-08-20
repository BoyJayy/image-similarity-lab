#include <imgsim/exact_duplicates.hpp>
#include <imgsim/sha256.hpp>
#include <filesystem>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <iostream>


namespace imgsim {
    struct Sha256Hasher {
    std::size_t operator()(const imgsim::sha256_hash_t& hash) const noexcept {
        std::size_t result = 0;
        for (unsigned char byte : hash) {
            result ^= static_cast<std::size_t>(byte) + 0x9e3779b9 + (result << 6) + (result >> 2);
        }
        return result;
    }
    };
    std::vector<DuplicateGroup> find_exact_duplicates(const DuplicateGroup& files) {
        std::unordered_map<std::uintmax_t, DuplicateGroup> size_to_files;
        // we will store files by size by map (uintmax_t cuz filesystem::file_size returns uintmax_t)
        for (const auto& file : files)
            //if file exists by path and its not directory or smth
            if (std::filesystem::exists(file) && std::filesystem::is_regular_file(file)) {
                std::uintmax_t file_size = std::filesystem::file_size(file); 
                size_to_files[file_size].push_back(file);
            }

        /* 
            x bytes: [file1, file2, file3]
            y bytes: [file4, file5]
            z bytes: [file6]
            like this and check sha256 for each
        */
       std::vector<DuplicateGroup> result;
        for (const auto& [size, group]: size_to_files) {
            if (group.size() < 2) continue; // not possible to have duplicates if only one file of that size
            // check sha256 for each file in the group
            std::unordered_map<sha256_hash_t, DuplicateGroup, Sha256Hasher> hash_to_files;
            for (auto& file : group) {
                try {
                    sha256_hash_t hash = sha256_file(file);
                    hash_to_files[hash].push_back(file);
                } catch (const std::exception& e) {
                    std::cerr << "Error processing file " << file << ": " << e.what() << std::endl;
                }
            }
            for (const auto& [hash, file_group] : hash_to_files) {
                if (file_group.size() > 1) {
                    result.push_back(file_group);
                }
            }
        }

        return result;
    }
}