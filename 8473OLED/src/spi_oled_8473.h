#ifndef SPI_OLED_8473_H_
#define SPI_OLED_8473_H_


#include <SI_C8051F380_Register_Enums.h>
#include "system_init.h"
#include "timer.h"


//-----------------------------------------------------------------------------
// Function Declarations
//-----------------------------------------------------------------------------
void Control_OLED(uint8_t cmd, const uint8_t* param, uint8_t param_len);
void OLED_RW(const uint8_t* frame_list, uint16_t frame_list_len);
void Power_ON(void);
void Power_OFF(void);
void Set_Standby(bool enable);
void Set_Display(bool enable);
void Set_Brightness(uint8_t level);
void Update_Brightness(void);
void Rotate180(uint8_t enable, const uint8_t* frame_list, uint8_t frame_list_len);


#endif /* SPI_OLED_8473_H_ */
