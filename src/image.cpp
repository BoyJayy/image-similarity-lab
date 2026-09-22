#include <cstddef>
#include <imgsim/image.hpp>
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <vector>
#include <cmath>
#include <memory>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


namespace imgsim {

RGBImage load_RGB_image(const std::filesystem::path path) {
    int width=0,height=0,channels=0;
    constexpr int desired_channels = 3;
    // instead of using stbi_uc* we use unique ptr to avoid memory leak on phase where we use stbi_image_free (delete doesnt work there)
    //also if we used stdi_image_free manually in the end, there is a chance to get exception and receive leak again
    std::unique_ptr<stbi_uc,decltype(&stbi_image_free)> pixels(stbi_load(path.string().c_str(),&width,&height,&channels,desired_channels), stbi_image_free);
    if (!pixels) {
        const char* reason = stbi_failure_reason();
        throw std::runtime_error( "failed to load image '" + path.string() + "': " +(reason ? reason : "unknown error"));
    }
    if (width<= 0 || height<=0) {
        throw std::runtime_error("loaded image has invalid dimensions: " + path.string());
    }
    RGBImage image;
    image.height=static_cast<size_t>(height);
    image.width=static_cast<size_t>(width);
    // get() is just raw pointer tho
    image.data.assign(pixels.get(),pixels.get() + image.width*image.height*desired_channels);
    return image;
}

GrayScale convert_to_grayscale(const RGBImage& rgb) {
    std::size_t width = rgb.width, height = rgb.height;
    std::vector<std::uint8_t> rgb_data = rgb.data;
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
    if (image.width == 0 || image.height == 0) {
        throw std::invalid_argument("cannot resize empty image");
    }
    if (image.data.size() != image.width * image.height) {
        throw std::invalid_argument("grayscale data size does not match image dimensions");
    }
    if (new_width < 2 || new_height < 2) {
        throw std::invalid_argument("resize dimensions must be at least 2");
    }
    GrayScale resized_image;
    resized_image.width = new_width;
    resized_image.height = new_height;
    resized_image.data.resize(new_width * new_height);
    //bilinear interpolation 
    double x_ratio = static_cast<double>(image.width-1) / static_cast<double>(new_width-1);
    double y_ratio = static_cast<double>(image.height-1) / static_cast<double>(new_height-1);
    //x = a*(1-t) + b*t in 1 dim  t is param that we can change
    // in 2nd dim we calc the same way as a 1 dim at first for points  x1y1 x2y1 and for x1y2 x2y2
    // then we got 2 points instead of 4 so we can make LERP(linear interpolation xd) between them to get the final point
    // https://en.wikipedia.org/wiki/Bilinear_interpolation
    for (std::size_t i = 0; i < new_height; i++) {
        for (std::size_t j = 0; j < new_width ; j++) {
            double x = j*x_ratio;
            double y = i*y_ratio;
            std::size_t x0 = static_cast<std::size_t>(std::floor(x));
            std::size_t y0 = static_cast<std::size_t>(std::floor(y));
            double dx = x-x0;
            double dy = y-y0;
            std::size_t x1 = std::min(x0+1,image.width-1);
            std::size_t y1 = std::min(y0+1,image.height-1);
            auto top_left = image.data[y0*image.width+x0];
            auto top_right = image.data[y0*image.width+x1];
            auto bottom_left = image.data[y1*image.width+x0];
            auto bottom_right = image.data[y1*image.width+x1];
            double top = (1.0-dx)*top_left + dx*top_right;
            double bottom = (1.0-dx)*bottom_left + dx*bottom_right;
            double value = (1.0-dy)*top + dy*bottom;
            resized_image.data[i*new_width+j] = static_cast<std::uint8_t>(std::lround(value));
        }
    }
    return resized_image;
}
}