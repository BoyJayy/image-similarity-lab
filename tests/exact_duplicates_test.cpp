#include <gtest/gtest.h>
#include <imgsim/exact_duplicates.hpp>

#include <algorithm>
#include <filesystem>
//#include <fstream>
#include <string>

namespace {
std::filesystem::path get_file_path(const std::string& filename) {
        return std::filesystem::path(__FILE__).parent_path() 
        / "data"
        / filename;
}


bool contains_path(const imgsim::DuplicateGroup& group,const std::filesystem::path& path) {
    return std::find(group.begin(), group.end(), path) != group.end();
}


TEST(ExactDuplicatesTest, IdenticalFilesAreGroupedTogether) {
    const auto file1 = get_file_path("pic1_test.jpg");
    const auto file2 = get_file_path("pic2_test.jpg");

    imgsim::DuplicateGroup files{file1, file2};

    const auto result = imgsim::find_exact_duplicates(files);

    ASSERT_EQ(result.size(), 1);
    ASSERT_EQ(result[0].size(), 2);

    EXPECT_TRUE(contains_path(result[0], file1));
    EXPECT_TRUE(contains_path(result[0], file2));
}
}