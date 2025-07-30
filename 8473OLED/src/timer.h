#ifndef TIMER_H_
#define TIMER_H_

#include <SI_C8051F380_Register_Enums.h>                // SFR declarations
#include "system_init.h"

//-----------------------------------------------------------------------------
// Types
//-----------------------------------------------------------------------------
typedef enum {
    TIMER1_WAIT,
    TIMER1_COUNT,
} TIMER1_MODE;


//-----------------------------------------------------------------------------
// Function Declarations
//-----------------------------------------------------------------------------
void Timer_Init(void);
void Set_ticks_Timer1(void);
bool Timer1_IsDone(void);
void Wait_us_Timer1(unsigned int us);
void Count_Timer1(unsigned int ms);

#endif /* TIMER_H_ */
