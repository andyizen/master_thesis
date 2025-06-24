#include "filter_init.hpp"
#include "xil_io.h"
#include <cmath>

// Axi write data
static void axi_write_float(uintptr_t addr, float value) {
    union {
        float f;
        uint32_t u;
    } conv;
    conv.f = value;
    Xil_Out32(addr, conv.u);
}

void compute_biquad_coeff(float fc, float Q, float gain_db, FilterType type, int channel, uintptr_t mem_coeff_base) {
    float omega = 2.0f * PI * fc / FS;
    float K = tanf(omega / 2.0f);
    float alpha = K * K + 1.0f;
    float beta  = K / Q;
    float gamma = 1.0f / (alpha + beta);
    float A = powf(10.0f, gain_db / 40.0f);
    float sqrt_A = sqrtf(A);

    BiquadCoeff coeff;

    switch (type) {
        case FilterType::Lowpass:
            coeff.b0 = gamma;
            coeff.b1 = 2.0f * gamma;
            coeff.b2 = gamma;
            coeff.a1 = 2.0f * gamma * (1.0f - K * K);
            coeff.a2 = gamma * (alpha - beta);
            break;

        case FilterType::Highpass:
            coeff.b0 = gamma;
            coeff.b1 = -2.0f * gamma;
            coeff.b2 = gamma;
            coeff.a1 = 2.0f * gamma * (1.0f - K * K);
            coeff.a2 = gamma * (alpha - beta);
            break;

        case FilterType::Peak:
            coeff.b0 = gamma * (alpha + beta * A);
            coeff.b1 = 2.0f * gamma * (1.0f - K * K);
            coeff.b2 = gamma * (alpha - beta * A);
            coeff.a1 = coeff.b1;
            coeff.a2 = gamma * (alpha - beta);
            break;

        case FilterType::Shelf:
            coeff.b0 = gamma * (alpha + beta * sqrt_A + (A - 1.0f));
            coeff.b1 = 2.0f * gamma * (1.0f - K * K);
            coeff.b2 = gamma * (alpha - beta * sqrt_A + (A - 1.0f));
            coeff.a1 = coeff.b1;
            coeff.a2 = gamma * (alpha - beta * A);
            break;
    }

    uintptr_t base = mem_coeff_base + channel * NUM_COEFFS * sizeof(float);
    axi_write_float(base + 0,  coeff.b0);
    axi_write_float(base + 4,  coeff.b1);
    axi_write_float(base + 8,  coeff.b2);
    axi_write_float(base + 12, coeff.a1);
    axi_write_float(base + 16, coeff.a2);
}
