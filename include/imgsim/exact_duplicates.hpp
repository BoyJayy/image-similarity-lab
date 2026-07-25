#include <filesystem>
#include <vector>

namespace imgsim{
    using DuplicateGroup = std::vector<std::filesystem::path>;
    [[nodiscard]] std::vector<DuplicateGroup> find_exact_duplicates(const DuplicateGroup& files);
}