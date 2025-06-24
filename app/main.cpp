#include "filter_init.hpp"
#include "xparameters.h"
#include "xil_io.h"

// AXI_Lite addresse
#define CTRL_REG_BASE   XPAR_BIQUAD_DFII_FLOAT_0_S_AXI_CTRL_BASEADDR
#define CTRL_REG_START  0x00
#define CTRL_REG_STATUS 0x04
#define CTRL_REG_LBA    0x10
#define CTRL_REG_HBA    0x14

int main() {
    // AXI4 addresses
    const uint64_t mem_coeff_addr = 0xC0000000;
    const uint32_t lba = static_cast<uint32_t>(mem_coeff_addr & 0xFFFFFFFF);
    const uint32_t hba = static_cast<uint32_t>((mem_coeff_addr >> 32) & 0xFFFFFFFF);

    // Set LBA/HBA 
    Xil_Out32(CTRL_REG_BASE + CTRL_REG_LBA, lba);
    Xil_Out32(CTRL_REG_BASE + CTRL_REG_HBA, hba);

    // Filter init
    for (int ch = 0; ch < NUM_CHANNELS; ++ch) {
        float fc    = 500.0f + 100.0f * ch;
        float Q     = 0.707f;
        float gain  = (ch % 2 == 0) ? 0.0f : -6.0f;
        FilterType type = (ch % 4 == 0) ? FilterType::Lowpass :
                          (ch % 4 == 1) ? FilterType::Highpass :
                          (ch % 4 == 2) ? FilterType::Peak :
                                          FilterType::Shelf;

        compute_biquad_coeff(fc, Q, gain, type, ch, mem_coeff_addr);
    }

    // start komponent
    Xil_Out32(CTRL_REG_BASE + CTRL_REG_START, 1);
    //wait for start of komponente
    while ((Xil_In32(CTRL_REG_BASE + CTRL_REG_STATUS) & 0x1) == 0);

    while (1);
}
