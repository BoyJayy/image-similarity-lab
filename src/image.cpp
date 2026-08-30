#include <imgsim/image.hpp>
#include <vector>
#include <cmath>

namespace imgsim {

GrayScale convert_to_grayscale(const std::vector<std::uint8_t>& rgb_data, std::size_t width, std::size_t height) {
    if (rgb_data.size() != width * height * 3) {
        throw std::invalid_argument("RGB data size does not match image dimensions");
    }
    GrayScale grayscale;
    grayscale.width = width;
    grayscale.height = height;
    grayscale.data.reserve(width*height);
    for (std::size_t i = 0; i < rgb_data.size(); i += 3) {
        std::uint8_t r = rgb_data[i];
        std::uint8_t g = rgb_data[i + 1];
        std::uint8_t b = rgb_data[i + 2];
        std::uint8_t gray_value = static_cast<std::uint8_t>(lround(0.299 * r + 0.587 * g + 0.114 * b));
        grayscale.data.push_back(gray_value);
    }
    return grayscale;
}

GrayScale resize_grayscale(const GrayScale& image, std::size_t new_width, std::size_t new_height) {
    GrayScale resized_image;
    resized_image.width = new_width;
    resized_image.height = new_height;
    resized_image.data.resize(new_width * new_height);
    //bilinear interpolation 
    size_t x_ratio = static_cast<size_t>(image.width) / new_width;
    size_t y_ratio = static_cast<size_t>(image.height) / new_height;
    for (std::size_t i = 0; i < new_height; i++) {

    }
}