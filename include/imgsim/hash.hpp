#pragma once
#include <cstdint>

namespace imgsim {
    using ImgHash  = std::uint64_t;
    std::uint32_t hamming_distance(ImgHash a, ImgHash b);
} // namespace imgsim signature!

