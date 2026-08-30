#include <imgsim/image.hpp>
#include <gtest/gtest.h>
#include <vector>

namespace imgsim {
TEST(GrayscaleResizeTest, ResizeFakeToBigger) {
    GrayScale image{
        .width = 2,
        .height = 2,
        .data = {0,100, 200, 250},
    };
    GrayScale resized = imgsim::resize_grayscale(image, 3, 3);
    /*
    result:
    dx = 0.5
    dy = 0.5
        0     50     100

        100   150    200

        200   250    300
    */
    EXPECT_EQ(resized.width, 3);
    EXPECT_EQ(resized.height, 3);
    ASSERT_EQ(resized.data.size(), 9);
    EXPECT_EQ(resized.data[0], 0);
    EXPECT_EQ(resized.data[1], 50);
    EXPECT_EQ(resized.data[2], 100);
    EXPECT_EQ(resized.data[3], 100);
    EXPECT_EQ(resized.data[4], 138);
    EXPECT_EQ(resized.data[5], 175);
    EXPECT_EQ(resized.data[6], 200);
    EXPECT_EQ(resized.data[7], 225);
    EXPECT_EQ(resized.data[8], 250);
}
}