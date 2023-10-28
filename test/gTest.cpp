#include <gtest/gtest.h>
#include <coco/noise.hpp>


using namespace coco;

// noise
// -----

/*TEST(cocoTest, bump8s) {
    std::cout << " [";
    for (int i = 0; i < 4096; ++i) {
        if (i != 0)
            std::cout << ", ";
        //int x = bumpS8(i >> 8, i & 0xff);
        int x = noiseI16(i << 8);
        std::cout << x;
    }
    std::cout << "]";
}*/

TEST(cocoTest, noiseI8) {
    int last = noiseI8(0);
    for (int i = 0; i < 65536; ++i) {
        int n = noiseI8(i);

        // check range
        EXPECT_GE(n, -128);
        EXPECT_LE(n, 127);

        // check slope
        EXPECT_TRUE(std::abs(last - n) <= 2);
        last = n;
    }
}

TEST(cocoTest, noiseI16) {
    int last = noiseI16(0);
    for (int i = 0; i < 65536; ++i) {
        int n = noiseI16(i << 8);

        // check range
        EXPECT_GE(n, -32768);
        EXPECT_LE(n, 32767);

        // check slope
        EXPECT_TRUE(std::abs(last - n) <= (2 << 8));
        last = n;
    }
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    int success = RUN_ALL_TESTS();
    return success;
}
