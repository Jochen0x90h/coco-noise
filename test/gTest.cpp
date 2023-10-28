#include <gtest/gtest.h>
#include <coco/noise.hpp>


using namespace coco;

// noise
// -----

TEST(cocoTest, noise) {
	//EXPECT_EQ(align(33, 32), 64);

	int last = noiseS8(0);
	for (int i = 1; i < 1024; ++i) {
		int n = noiseS8(i);
		EXPECT_TRUE(std::abs(last - n) <= 2);
		last = n;
	}
}


int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	int success = RUN_ALL_TESTS();
	return success;
}
