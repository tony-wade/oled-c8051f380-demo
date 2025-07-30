#ifndef SYSTEM_INIT_H_
#define SYSTEM_INIT_H_

#include <SI_C8051F380_Register_Enums.h>
// "stddef.h"  is not supported in Keil

//-----------------------------------------------------------------------------
// Global Constants
//-----------------------------------------------------------------------------
#define SPI_CLOCK          1000000      // Maximum SPI clock (Hz)

//-----------------------------------------------------------------------------
// GPIO Setting
//-----------------------------------------------------------------------------
// SPI pins is strictly defined
// P0.0 as SCL(D6)= SCK, < 10 MHz
// MISO is not needed, but exist.
// P0.2 as SI(D7) = MOSI
// P0.3 as XCS = NSS

SI_SBIT(A0, SFR_P0, 4);   // P0.4 as A0
SI_SBIT(XRES, SFR_P0, 5); // P0.5 as XRES

SI_SBIT(SW, SFR_P2, 0);    // P2.0 as SWitch (Silicon Labs macro)


//-----------------------------------------------------------------------------
// Function Declarations
//-----------------------------------------------------------------------------
void PORT_Init(void);
void SPI0_Init(void);
void OSCILLATOR_Init(void);

#endif /* SYSTEM_INIT_H_ */
