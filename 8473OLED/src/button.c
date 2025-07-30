#include "button.h"

/*
 *  Higher the system clock, the more sensitive code is.
 *  Be aware with any multi-requirement in if statement & any ISR scenario.
 */

//-----------------------------------------------------------------------------
// Constants
//-----------------------------------------------------------------------------
static ButtonState button_state = BUTTON_IDLE;
static uint16_t short_press_counter = 0;
static uint16_t long_press_counter = 0;
static bool prev_input = false;   // not triggered
static bool timeoutPending = false;

const uint16_t DEBOUNCE_TIME = 10;          // ms
const uint16_t ACTION_COMPLETE_TIME = 300;  // ms
const uint16_t LONG_PRESS_TIME = 1000;      // ms

//-----------------------------------------------------------------------------
// Button Event Logic
//-----------------------------------------------------------------------------
void Button_Update(void)
{
    volatile bool now_input = Read_Button();

    switch (button_state) {

      case BUTTON_IDLE:
          // triggered only when not pressed to pressed.
          if (!prev_input && now_input) {
              button_state = BUTTON_DEBOUNCE;
              Count_Timer1(DEBOUNCE_TIME);
          }
          break;

      case BUTTON_DEBOUNCE:
          if (Timer1_IsDone()) {
              if (now_input) {
                  button_state = BUTTON_PRESSED;
                  Count_Timer1(LONG_PRESS_TIME - DEBOUNCE_TIME);
              }
              else {
                  button_state = BUTTON_RELEASED;   // invalid input
              }
          }
          break;

      case BUTTON_PRESSED:
          if (!now_input) {

              if (Timer1_IsDone()){
                  long_press_counter += 1;
              }
              else {
                  short_press_counter += 1;
              }
              button_state = BUTTON_RELEASED;
              Count_Timer1(DEBOUNCE_TIME);
          }
          break;

      case BUTTON_RELEASED:
          if (Timer1_IsDone()){

              if (!timeoutPending) {
                  Count_Timer1(ACTION_COMPLETE_TIME);   //  detect further action
                  timeoutPending = true;
              }

              else {
                  //Events
                  if (short_press_counter == 1){
                      OneClickEvent();
                  }
                  else if (short_press_counter == 2){
                      DoubleClickEvent();
                  }
                  else if (long_press_counter == 1){
                      LongPressEvent();
                  }
                  // Can realize Multi-click here

                  // back to idle
                  button_state = BUTTON_IDLE;
                  short_press_counter = 0;   // reset
                  long_press_counter = 0;    // reset
                  timeoutPending = false;
              }
           }

          else if (now_input && timeoutPending) {
              button_state = BUTTON_DEBOUNCE;
              Count_Timer1(DEBOUNCE_TIME);
              timeoutPending = false;
          }
          break;
    }

    prev_input = now_input;  // update
}

//-----------------------------------------------------------------------------
// Button Event  Constants (Can migrate to new file)
//-----------------------------------------------------------------------------
static bool OLED_ON = false;
static bool Disply_ON = false;


//-----------------------------------------------------------------------------
// One-Click: OLED Brightness Control
//-----------------------------------------------------------------------------
void OneClickEvent(void) {

    if (Disply_ON && OLED_ON) {
        Update_Brightness();
    }
}

//-----------------------------------------------------------------------------
// Double-Click:: OLED Display Control
//-----------------------------------------------------------------------------
void DoubleClickEvent(void) {

    if (OLED_ON) {

        if (!Disply_ON) {
            Set_Standby(false);
            Control_OLED(0x08, NULL, 0);  // Wake
            Set_Display(true);

            Disply_ON = true;
        }
        else {
            Set_Display(false);
            Wait_us_Timer1(10000);  // 10 ms
            Set_Standby(true);

            Disply_ON = false;
        }
    }
}

//-----------------------------------------------------------------------------
// Long Press: OLED On-Off
//-----------------------------------------------------------------------------
void LongPressEvent(void) {

    if (!OLED_ON) {
        // VAH H
        Power_ON();
        Set_Standby(false);   // not in data sheet!!
        OLED_RW(TEST_IMAGE_1, sizeof(TEST_IMAGE_1));
        Set_Display(true);   // not in data sheet!!

        OLED_ON = true;
        Disply_ON = true;
    }
    else {
        if (Disply_ON){
            DoubleClickEvent();  // need display off, back to stand by
        }
        Power_OFF();

        OLED_ON = false;
        Disply_ON = false;
    }
}


