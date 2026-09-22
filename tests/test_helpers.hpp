#pragma once
//#include <cstdint>
#include <filesystem>
#include <string_view>

namespace test_helpers {

namespace fs = std::filesystem;

inline fs::path project_root() {
    return fs::path{__FILE__}.parent_path().parent_path();
}

inline fs::path data_path(std::string_view filename) {
    return project_root() / "data" / filename;
}

inline fs::path data_test_path(const std::string& filename) {
    return std::filesystem::path(__FILE__).parent_path() / "data"/ filename;
}

}