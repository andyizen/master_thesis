#ifndef FILTER_INIT_HPP
#define FILTER_INIT_HPP

#include <cstdint>

constexpr int NUM_CHANNELS = 16;
constexpr int NUM_COEFFS   = 5;
constexpr float FS = 48000.0f;
constexpr float PI = 3.14159265358979323846f;

// Biquad struct
struct BiquadCoeff {
    float b0, b1, b2;
    float a1, a2;
};

// filter types
enum class FilterType {
    Lowpass,
    Highpass,
    Peak,
    Shelf
};

// Compute helpers 
void compute_biquad_coeff(
    float fc,
    float Q,
    float gain_db,
    FilterType type,
    int channel,
    uintptr_t mem_coeff_base
);

#endif 
