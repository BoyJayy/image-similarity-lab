#include <iostream>
#include <imgsim/hash.hpp>
int main() {
    uint64_t a = 0x123456789ABCDEF0;
    uint64_t b = 0x123456789ABCDEF1;
    std::cout << imgsim::hamming_distance(a, b) << std::endl;
}
