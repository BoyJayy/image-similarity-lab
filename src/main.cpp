#include <iostream>
#include <imgsim/hash.hpp>
#include <imgsim/search.hpp>
int main() {
    std::vector<std::uint64_t> hashes;
    hashes.push_back(0x123456789ABCDEF0);
    hashes.push_back(0x123456789ABCDEF1);
    std::uint64_t query = 0x123456789ABCDEF2;
    auto matches = imgsim::brute_force_k(query, hashes, 2);
    for (auto& match : matches) {
        std::cout << match.index << ": " << match.distance << std::endl;
    }
    uint64_t a = 0x123456789ABCDEF0;
    uint64_t b = 0x123456789ABCDEF1;
    std::cout << imgsim::hamming_distance(a, b) << std::endl;
}
