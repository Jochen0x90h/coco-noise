#include "noise.hpp"
#include "permute8.hpp"


namespace coco {

// average for 8 bit signed integers
inline int8_t avgS8(int8_t i, int8_t j) {
	return (i + j + 1) >> 1;
}

// lerp for 8 bit signed integers. the interpolator r is interpreted as 0..255/256
inline int8_t lerpS8(int8_t a, int8_t b, uint8_t r) {
	if (b > a)
		return a + (uint8_t)(r * (uint8_t)(b - a) >> 8);
	return a - (uint8_t)(r * (uint8_t)(a - b) >> 8);
}

// helper function: calculate bumps of varying height in the range -128..127
inline int8_t bumpS8(uint8_t i, uint8_t x) {
	int8_t hash = permute8[i];
	int8_t y = (uint8_t)(x * x >> 7) - (uint8_t)(x + x);

	int8_t u, v;
	if (hash & 8) {
		u = y;
		v = y;
	} else {
		if (hash & 4) {
			u = 1;
			v = y;
		} else {
			u = y;
			v = 1;
		}
	}

	if (hash & 1)
		u = ~u;
	if (hash & 2)
		v = ~v;

	return avgS8(u, v);
}

// generate noise in the range -128..127 for x in 8.8 fixed point notation
int8_t noiseS8(int x) {
	// integer part of x
	uint8_t i = x >> 8;

	// fractional part of x
	uint8_t f = uint8_t(x);

	// bump for position i and negative bump for next position
	int8_t g1 = bumpS8(i, f);
	int8_t g2 = ~bumpS8(i + 1, f);

	// interpolate between the bumps
	return lerpS8(g1, g2, f);
}

} // namespace coco
