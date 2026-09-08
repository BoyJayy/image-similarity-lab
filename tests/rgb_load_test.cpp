#include <gtest/gtest.h>
#include <imgsim/image.hpp>
#include "test_helpers.hpp"

namespace imgsim {

TEST(ImageLoadTest, LoadsImageAsRGB) {
    const auto path = test_helpers::data_test_path("pic1_test.jpg");
    imgsim::RGBImage image = imgsim::load_RGB_image(path);
    EXPECT_GT(image.width, 0);
    EXPECT_GT(image.height, 0);
    EXPECT_EQ(image.data.size(),image.width * image.height * 3);
}

}