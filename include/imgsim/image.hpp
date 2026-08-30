#pragma once
#include <cstdint>
#include <cstddef>
#include <vector>

namespace imgsim {
struct Image {
    std::size_t width{};
    std::size_t height{};
    std::vector<std::uint8_t> data; 
};
struct GrayScale {
    std::size_t width{};
    std::size_t height{};
    std::vector<std::uint8_t> data; // pixels brightness that we got from rgb
};

// Y=0.299R+0.587G+0.114B bcs every color has different brightness, so we need to convert it to grayscale
GrayScale convert_to_grayscale(const std::vector<std::uint8_t>& rgb_data,
                               std::size_t width, std::size_t height);
// for instance for ahash we need 8x8 grayscale image
GrayScale resize_grayscale(const GrayScale& image,
    std::size_t new_width,std::size_t new_height);
}