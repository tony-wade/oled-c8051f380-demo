#include "system_init.h"

// ----------------------------------------------------------------------------
// Port Initialization
// ----------------------------------------------------------------------------
void PORT_Init(void) {
    P0MDOUT |= 0x3D;    // Set P0.0~P0.5 as push-pull output, except P0.1(MISO)
    XRES = 0;
    A0 = 0;

    P0SKIP |= 0X30;     // 0.4, 0.5 as GPIO

    // Crossbar configuration, critical
    XBR0 = 0x02;        // Enable the SPI
    XBR1 = 0x40;        // Enable crossbar (allows output)
}

//-----------------------------------------------------------------------------
// SPI0 Initialization
//-----------------------------------------------------------------------------
void SPI0_Init()
{
   SPI0CFG   = 0x70;                   // Enable the SPI as a Master, SCL is H in idle state, rising trigger
   SPI0CN    = 0x0D;                   // 4-wire Single Master, SPI enabled(NSS=XCS H)

   // SPI clock frequency equation from the data sheet
   SPI0CKR   = (12000000 / (2*SPI_CLOCK)) - 1;

   //IE_ESPI0 = 1;                     // Enable SPI interrupts(Since only sending for now, no need to open)
   //IE_EA = 1;                        // Enable global interrupts (Put in main.c)
}

//-----------------------------------------------------------------------------
// Oscillator Initialization
//-----------------------------------------------------------------------------
void OSCILLATOR_Init(void) {
    OSCICN = 0x83;   // Internal oscillator = 12 MHz
}



