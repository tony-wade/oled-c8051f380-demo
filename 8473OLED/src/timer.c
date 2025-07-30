#include "timer.h"

/*Setting TR does not force the timer to reset.*/

//-----------------------------------------------------------------------------
// Constants
//-----------------------------------------------------------------------------
// 'volatile' is used when value may change outside, ex.ISR. Need to R/W in place for each loop.
static volatile TIMER1_MODE timer1_mode;
static volatile bool timer1_done = true;
static volatile unsigned long count_ticks = 0;  // long for longer duration


/* Oscillator Initialization is in system_init.h */

//-----------------------------------------------------------------------------
// Timer Initialization
//-----------------------------------------------------------------------------
void Timer_Init(void) {
    /*Timer 2 has auto-reload for convenience*/
    TMOD |= 0x10;  // Timer1 as 16-bit timers
    CKCON |= 0x00; // Timer1 divide by 12(1MHz)

    IE_ET1 = 1;    // Enable Timer1 interrupt
    //IE_EA = 1;     // Enable global interrupts (Put in main.c)
}

//-----------------------------------------------------------------------------
// Set count_ticks to 16 bits Timer1 and adjust it
//-----------------------------------------------------------------------------
void Set_ticks_Timer1(void){
  if (count_ticks > 65535){
      TH1 = 0x00;   // High byte
      TL1 = 0x00;   // Low byte
      count_ticks -= 65536UL;
  }
  else{
      TH1 = (65536UL - count_ticks) >> 8;   // High byte
      TL1 = (65536UL - count_ticks) & 0xFF; // Low byte
      count_ticks -= count_ticks;
  }
}

//-----------------------------------------------------------------------------
// Checks if Timer1 counting is completed.
//-----------------------------------------------------------------------------
bool Timer1_IsDone(void) {
    return timer1_done;
}

//-----------------------------------------------------------------------------
// Wait() with microsecond resolution (Max:65ms)
//-----------------------------------------------------------------------------
void Wait_us_Timer1(unsigned int us) {
    unsigned int value;

    timer1_mode = TIMER1_WAIT;
    timer1_done = false;    // reset

    value = 65536UL - us;  // 1MHz as timer clock
    TH1 = value >> 8;    // High byte
    TL1 = value & 0xFF;  // Low byte

    TCON_TR1 = 1;  // Start Timer1

    while(!timer1_done);  // Wait until done
}

//-----------------------------------------------------------------------------
// non-blocked Count-down function
//-----------------------------------------------------------------------------
void Count_Timer1(unsigned int ms){
    timer1_mode = TIMER1_COUNT;
    timer1_done = false;    // reset

    // (unsigned long)/UL is critical since ms is int!
    count_ticks = 1000UL * ms;  // set 1MHz as timer clock

    Set_ticks_Timer1();

    TCON_TR1 = 1;  // Start Timer1
}

//-----------------------------------------------------------------------------
// ISR is unique so can't be in .h
//-----------------------------------------------------------------------------
SI_INTERRUPT(Timer1_ISR, 3) {
    switch (timer1_mode){

       case TIMER1_WAIT:
          TCON_TR1 = 0;   // Stop Timer1
          timer1_done = true;
          break;

       case TIMER1_COUNT:
          if (count_ticks != 0) {
              Set_ticks_Timer1() ;
          }
          if (count_ticks == 0) {
              TCON_TR1 = 0;   // Stop Timer1
              timer1_done = true;
          }
          break;
    }

}
