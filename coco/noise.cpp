#include "noise.hpp"
#include "permute8.hpp"
#include <cmath>


namespace {

// average for signed integers
inline int avg(int i, int j) {
    return (i + j /*+ 1*/) >> 1;
}

} // namespace

namespace coco {


// 8 bit using int8_t

// lerp for 8 bit signed integers. the interpolator r is interpreted as 0..255/256
inline int8_t lerpI8(int8_t a, int8_t b, uint8_t r) {
    if (b > a)
        return a + (r * uint8_t(b - a) >> 8);
    return a - (r * uint8_t(a - b) >> 8);
}

// helper function: calculate bumps of varying height in the range -128..127
inline int8_t bumpI8(uint8_t i, uint8_t x) {

    // quadratic function with zero crossings at x=0 and x=256 and minimum of y=-128 at x=128
    int8_t y = (uint8_t)(x * x >> 7) - (uint8_t)(x + x);

    auto hash = permute8[i];
    int8_t u, v;
    if (hash & 8) {
        u = y;
        v = y;
    } else {
        if (hash & 4) {
            u = 0;
            v = y;
        } else {
            u = y;
            v = 0;
        }
    }

    if (hash & 1)
        u = ~u;
    if (hash & 2)
        v = ~v;

    return avg(u, v);
}

// generate noise in the range -128..127 for x in 8.8 fixed point notation
int8_t noiseI8(int x) {
    // integer part of x
    uint8_t i = x >> 8;

    // fractional part of x
    uint8_t f = uint8_t(x);

    // bump for position i and negative bump for next position
    int8_t g1 = bumpI8(i, f);
    int8_t g2 = ~bumpI8(i + 1, f);

    // interpolate between the bumps
    return lerpI8(g1, g2, f);
}


// 16 bit using int

// lerp for 16.16 bit fixed float. the interpolator r is in the range [0.0 1.0), i.e. [0 65535]
inline int lerpI16(int a, int b, unsigned r) {
    if (b > a)
        return a + (r * uint32_t(uint16_t(b - a)) >> 16);
    return a - (r * uint32_t(uint16_t(a - b)) >> 16);
}

// helper function: calculate bumps of varying height in the range -32768..32767
inline int bumpI16(uint8_t i, unsigned x) {

    // quadratic function with zero crossings at x=0 and x=65536 and minimum of y=-32768 at x=32768
    int y = (x * uint32_t(x) >> 15) - (x + x);

    auto hash = permute8[i];
    int u, v;
    if (hash & 8) {
        u = y;
        v = y;
    } else {
        if (hash & 4) {
            u = 0;
            v = y;
        } else {
            u = y;
            v = 0;
        }
    }

    if (hash & 1)
        u = ~u;
    if (hash & 2)
        v = ~v;

    return avg(u, v);
}

// generate noise in the range -128..127 for x in 8.8 fixed point notation
int noiseI16(int x) {
    // integer part of x
    uint8_t i = x >> 16;

    // fractional part of x
    int f = x & 0xffff;

    // bump for position i and negative bump for next position
    int g1 = bumpI16(i, f);
    int g2 = ~bumpI16(i + 1, f);

    // interpolate between the bumps
    return lerpI16(g1, g2, f);
}


// helper function: calculate bumps of varying height in the range [-1.0, 1.0]
inline float bump(uint8_t i, float a) {
    // quadratic function with zero crossings at a=0 and a=1 and minimum of y=-1 at x=0.5
    float b = 4.0f * (a * a - a);

    auto hash = permute8[i];
    float u, v;
    if (hash & 8) {
        u = b;
        v = b;
    } else {
        if (hash & 4) {
            u = 0;
            v = b;
        } else {
            u = b;
            v = 0;
        }
    }

    if (hash & 1)
        u = -u;
    if (hash & 2)
        v = -v;

    // return average of u and v
    return (u + v) * 0.5f;
}

} // namespace coco
