#pragma once
#include <cstdint>
#include <cstddef>
#include <filesystem>

namespace imgsim {
    inline constexpr int SHA256_HASH_SIZE = 32;
    using sha256_hash_t = std::array<std::uint8_t, SHA256_HASH_SIZE>;
    [[nodiscard]] sha256_hash_t sha256_file(const std::filesystem::path& path);
}