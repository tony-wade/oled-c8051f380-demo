/*
 * GPIO Configuration — see system_init.h
 *
 * SPI pins are hardware-defined:
 *   - P0.0 : SCK (SCL / D6), < 10 MHz
 *   - P0.2 : MOSI (SI / D7)
 *   - P0.3 : NSS  (XCS)
 *   - MISO is not used, but present.
 *
 * Additional OLED control pins:
 *   - P0.4 : A0    (Command/Data select)
 *   - P0.5 : XRES  (Reset)
 *
 * User input:
 *   - P2.0 : SW    (Switch input, Silicon Labs macro)
 *
 * VAH(15V) is provide by external source
 */

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <SI_C8051F380_Register_Enums.h>                // SFR declarations
#include "system_init.h"
#include "button.h"

//-----------------------------------------------------------------------------
// Constants
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// SiLabs_Startup() Routine
// ----------------------------------------------------------------------------
void SiLabs_Startup (void)
{
  PCA0MD = 0x00;                      // Disable watch-dog timer
}

// ----------------------------------------------------------------------------
// Initialization
// ----------------------------------------------------------------------------
void Init_Device (void)
{
    OSCILLATOR_Init();
    Timer_Init();
    PORT_Init();
    SPI0_Init();
    IE_EA = 1;     // Enable global interrupts
}


//-----------------------------------------------------------------------------
// main() Routine
// ----------------------------------------------------------------------------
int main (void)
{
  Init_Device();

  // Make SI init high
  SPI0DAT = 0xFF;
  while (!SPI0CN_SPIF);
  SPI0CN_SPIF = 0;

  while (1) {
      Button_Update();
  }
}

