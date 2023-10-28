#pragma once

#include <cstdint>


// inspired by FastLED noise functions: http://fastled.io/docs/3.1/noise_8cpp_source.html
namespace coco {

/**
	Generate noise in the range [-128, 127] for x in 8.8 fixed point notation
	@param x input of noise in 8.8 fixed point notation
	@return noise function at given x
*/
int8_t noiseS8(int x);

/**
	Generate noise in the range [0, 255] for x in 8.8 fixed point notation
	@param x input of noise in 8.8 fixed point notation
	@return noise function at given x
*/
inline uint8_t noiseU8(int x) {return noiseS8(x) + 128;}

} // namespace coco
