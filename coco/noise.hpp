#pragma once

#include <cstdint>


// inspired by FastLED noise functions: http://fastled.io/docs/3.1/noise_8cpp_source.html
namespace coco {

/**
	Generate noise in the range [-128, 127] for x with 8 bit fractional part
	@param x input of noise (only 16 bits of x are used)
	@return noise function at given x
*/
int8_t noiseS8(int x);

/**
	Generate noise in the range [0, 255] for x with 8 bit fractional part
	@param x input of noise (only 16 bits of x are used)
	@return noise function at given x
*/
inline uint8_t noiseU8(int x) {return noiseS8(x) + 128;}


/**
	Generate noise in the range [-32768, 32767] for x with 16 bit fractional part
	@param x input of noise (only 24 bits of x are used)
	@return noise function at given x
*/
int noiseS16(int x);

/**
	Generate noise in the range [0, 65535] for x with 16 bit fractional part
	@param x input of noise (only 24 bits of x are used)
	@return noise function at given x
*/
inline int noiseU16(int x) {return noiseS16(x) + 32768;}


// helpers
//int8_t bumpS8(uint8_t i, uint8_t x);
//int bumpS16(uint8_t i, unsigned x);

} // namespace coco
