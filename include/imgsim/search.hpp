#pragma once
#include <cstdint>
#include <cstddef>
#include <vector>

namespace imgsim {
    struct Match {
        std::size_t index;
        std::uint64_t hash;
        std::uint32_t distance;
    };
    [[nodiscard]] std::vector<Match> brute_force_k(std::uint64_t query,
            const std::vector<std::uint64_t>& hashes,
            std::size_t k);
}
