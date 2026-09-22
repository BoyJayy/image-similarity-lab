#pragma once
#include <cstdint>
#include <filesystem>
#include <imgsim/image.hpp>

namespace imgsim {
    using ImgHash  = std::uint64_t;
    std::uint32_t hamming_distance(ImgHash a, ImgHash b);
    ImgHash average_hash(const GrayScale& image);
    ImgHash average_hash(const std::filesystem::path& path);
}

