#include "imgsim/image.hpp"
#include <cstdint>
#include <imgsim/hash.hpp>
#include <bit>
#include <numeric>

/*
 * ill write all theory like dat
 * we will receive every pic as a hash
 * so we need to compare its Hamming distance
 * Hamming distance can be determined as a number of characters or values different in two strings or vectors
 * ofc with 64 bit values we can just xor them (a^b)
*/
namespace imgsim {
    using ImgHash  = std::uint64_t;
    std::uint32_t hamming_distance(ImgHash a, ImgHash b) {
        return static_cast<uint32_t>(std::popcount(a^b));
    }

    //to obtain ahash everything that we need is to resize grayscale into 8x8 and after that replace every pixel by 1 rule
    // if pixel brighness is more than average => replace it with 1 otherwise with 0
    //8x8=64 bits 
    ImgHash average_hash(const GrayScale& image) { 
        GrayScale resized=resize_grayscale(image, 8, 8);
        std::uint64_t sum = std::accumulate(resized.data.begin(), resized.data.end(),uint64_t{0});
        ImgHash hash;
        for (auto& pixel: resized.data) {
            hash <<= 1;
            if (static_cast<std::uint64_t>(pixel) * 8 > sum) {
                hash |= ImgHash{1};
            }
        }
        return hash;
    }

    ImgHash average_hash(const std::filesystem::path& path){
        RGBImage rgb = load_RGB_image(path);
        GrayScale gr = convert_to_grayscale(rgb);
        return average_hash(gr);
    }
}

