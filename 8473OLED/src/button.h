#ifndef BUTTON_H_
#define BUTTON_H_

#include "system_init.h"
#include "timer.h"
#include "spi_oled_8473.h"
#include "test_image.h"

//-----------------------------------------------------------------------------
// Types
//-----------------------------------------------------------------------------
typedef enum {
    BUTTON_IDLE,
    BUTTON_DEBOUNCE,
    BUTTON_PRESSED,
    BUTTON_RELEASED
} ButtonState;


#define BUTTON_ACTIVE_LOW     1    // set active-low

#if BUTTON_ACTIVE_LOW
    #define Read_Button()   (!SW)
#else
    #define Read_Button()   (SW)
#endif


//-----------------------------------------------------------------------------
// Function Declarations
//-----------------------------------------------------------------------------
void Button_Update(void);

void OneClickEvent(void);
void DoubleClickEvent(void);
void LongPressEvent(void);


#endif /* BUTTON_H_ */
