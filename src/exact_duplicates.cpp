#include <imgsim/exact_duplicates.hpp>
#include <imgsim/sha256.hpp>
#include <filesystem>
#include <fstream>
#include <vector>
#include <unordered_map>

namespace imgsim {
    std::vector<DuplicateGroup> find_exact_duplicates(const DuplicateGroup& files) {
        std::unordered_map<std::uintmax_t, DuplicateGroup> size_to_files;
        // we will store files by size by map (uintmax_t cuz filesystem::file_size returns uintmax_t)
        for (const auto& file : files)
            //if file exists by path and its not directory or smth
            if (std::filesystem::exists(file) && std::filesystem::is_regular_file(file)) {
                std::uintmax_t file_size = std::filesystem::file_size(file); 
                size_to_files[file_size].push_back(file);
            }
        std::vector<DuplicateGroup> result;
        for (const auto& [size, group] : size_to_files) {
            if (group.size() < 2) continue; // skip groups with less than 2 files
            vector<sha256_hash_t> hashes;
            for (const auto& file : group) {
                try {
                    hashes.push_back(sha256_file(file));
                } catch (const std::exception& e) {
                    // handle the error (e.g., log it, skip the file, etc.)
                    std::cerr << "Error hashing file " << file << ": " << e.what() << std::endl;
                }
            }
            //attention
            //ITS DOESNT WORK I FORGOT TO STORE HASHES WITH FILES SO I CANT FIND DUPLICATES BY HASHES ILL REWORK IT LATER
            
            
            
            //now ill use binary search to find duplicates by hash (avoids O(n^2) complexity)
            sort(hashes.begin(), hashes.end());
            for (const auto& hash: hashes) {
                int lb = std::lower_bound(hashes.begin(), hashes.end(), hash) - hashes.begin(); // index of first element not less than hash
                int ub = std::upper_bound(hashes.begin(), hashes.end(), hash) - hashes.begin(); // index of first element greater than has h
                //so the formula is lb-ub = number of elements equal to hash 
                if (ub - lb > 1) { // if there are duplicates
                    DuplicateGroup duplicate_group;
                    for (int i = lb; i < ub; ++i) {
                        duplicate_group.push_back(group[i]);
                    }
                    result.push_back(duplicate_group);
                }
            }
        }
        return result;

    }
}