#include <imgsim/hash.hpp>
#include <bit>

/*
 * ill write all theory like dat
 * we will receive every pic as a hash
 * so we need to compare its Hamming distance
 * Hamming distance can be determined as a number of characters or values different in two strings or vectors
 * ofc with to 64 bit values we can just a xor of them (a^b)
*/
namespace imgsim {
    using ImgHash  = std::uint64_t;
    std::uint32_t hamming_distance(ImgHash a, ImgHash b) {
        return static_cast<uint32_t>(std::popcount(a^b));
    }
}

