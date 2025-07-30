#include "spi_oled_8473.h"

/*
 * Only Control_OLED(), OLED_RW() need to adjust when migrate to other MCU.
 * Now: C8051F380
 */

//-----------------------------------------------------------------------------
// F380 General OLED Control Func.
//-----------------------------------------------------------------------------
void Control_OLED(uint8_t cmd, const uint8_t* param, uint8_t param_len) {
    uint8_t i;    // old compiler

    // Since only sending for now, no need to open SPI interrupt
    //IE_ESPI0 = 0;   // disable SPI interrupt(if enable)
    SPI0CN_NSSMD0 = 0;  // Set chip select (XCS = NSS = Low)

    if (param == NULL){
        // Send 0x08 to wake OLED(same pic)
        A0 = 0;
        SPI0DAT = cmd;
        while (!SPI0CN_SPIF);   // Wait until finish
        SPI0CN_SPIF = 0;    // Clear SPI transfer complete flag
        A0 = 1;             // End command phase
    }

    else {
        // Send command byte (CMD)
        A0 = 0;
        SPI0DAT = cmd;
        while (!SPI0CN_SPIF);
        SPI0CN_SPIF = 0;    // Clear SPI transfer complete flag
        A0 = 1;             // End command phase

        // Send command parameter
        for (i = 0; i < param_len; i++) {
            SPI0DAT = param[i];
            while (!SPI0CN_SPIF);
            SPI0CN_SPIF = 0;  // Clear flag
        }
    }

    SPI0CN_NSSMD0 = 1;  // Release chip select (XCS = NSS = High)
    //IE_ESPI0 = 1;   // re-enable SPI interrupt
}

//-----------------------------------------------------------------------------
// F380 Update OLED frame buffer (for Wake up, please use Control_OLED())
//-----------------------------------------------------------------------------
void OLED_RW(const uint8_t* frame_list, uint16_t frame_list_len) {    // need to adjust with frame size
    uint16_t i;   // need to adjust with frame size

    // Since only sending for now, no need to open SPI interrupt
    //IE_ESPI0 = 0;   // disable SPI interrupt(if enable)
    SPI0CN_NSSMD0 = 0;  // XCS = NSS = Low

    // Send command byte (CMD)
    A0 = 0;                 // Set command phase
    SPI0DAT = 0x08;
    while (!SPI0CN_SPIF);
    SPI0CN_SPIF = 0;        // Clear SPI transfer complete flag
    A0 = 1;                 // End command phase

    // Send Frame Data
    for (i = 0; i < frame_list_len; i++) {
        SPI0DAT = frame_list[i];
        while (!SPI0CN_SPIF);
        SPI0CN_SPIF = 0;  // Clear flag
    }

    SPI0CN_NSSMD0 = 1;  // XCS = NSS = High
    //IE_ESPI0 = 1;   // re-enable SPI interrupt
}


//-----------------------------------------------------------------------------
// Turn ON & Initialize OLED 8473
//-----------------------------------------------------------------------------
void Power_ON(void)
{
    // C90 is so old....
    static const uint8_t param_02[] = {0x00};
    static const uint8_t param_09[] = {0x00};
    static const uint8_t param_10[] = {0x06, 0x00, 0x00};
    static const uint8_t param_12[] = {0x42, 0x00, 0x00};  //3.3v
    static const uint8_t param_13[] = {0x00};
    static const uint8_t param_14[] = {0x01};
    static const uint8_t param_16[] = {0x00};
    static const uint8_t param_17[] = {0x00};
    static const uint8_t param_18[] = {0x07};
    static const uint8_t param_1A[] = {0x02};
    static const uint8_t param_1C[] = {0x00};
    static const uint8_t param_1D[] = {0x00};
    static const uint8_t param_30[] = {0x00, 0x10, 0x01, 0x0F};
    static const uint8_t param_32[] = {0x00, 0x2F};
    static const uint8_t param_34[] = {0x01};
    static const uint8_t param_35[] = {0x10};
    static const uint8_t param_36[] = {0x00};
    static const uint8_t param_37[] = {0x2F};
    static const uint8_t param_38[] = {0x00, 0x00};
    static const uint8_t param_39[] = {0x00};
    static const uint8_t param_48[] = {0x03};
    static const uint8_t param_D0[] = {0x80};
    static const uint8_t param_D2[] = {0x00};
    static const uint8_t param_D9[] = {0x00};
    static const uint8_t param_DB[] = {0x0F};
    static const uint8_t param_DD[] = {0x88};
    static const uint8_t param_E0[] = {0x10};
    static const uint8_t param_E2[] = {0x01};
    static const uint8_t param_E3[] = {0x00};
    static const uint8_t param_E4[] = {0x3F, 0x3F};
    static const uint8_t param_E5[] = {0x07};
    static const uint8_t param_E6[] = {0x07};
    static const uint8_t param_E7[] = {0x07};
    static const uint8_t param_FD[] = {0x10};  // 3.3v

    // VDD, XCS need to provide at the same time(<100ms)
    // VAH ON
    XRES = 1;
    Wait_us_Timer1(1);  // > 100ns

    // Please refer to data sheet(>1.1ms before OLED write)
    Control_OLED(0x01, NULL, 0);    // reset to default
    //Wait_us_Timer1(1);  // > 200ns
    Control_OLED(0x02, param_02, sizeof(param_02));
    Control_OLED(0x09, param_09, sizeof(param_09));
    Control_OLED(0x10, param_10, sizeof(param_10));
    Control_OLED(0x12, param_12, sizeof(param_12));
    Control_OLED(0x13, param_13, sizeof(param_13));
    Control_OLED(0x14, param_14, sizeof(param_14));
    Control_OLED(0x16, param_16, sizeof(param_16));
    Control_OLED(0x17, param_17, sizeof(param_17));
    Control_OLED(0x18, param_18, sizeof(param_18));
    Control_OLED(0x1A, param_1A, sizeof(param_1A));
    Control_OLED(0x1C, param_1C, sizeof(param_1C));
    Control_OLED(0x1D, param_1D, sizeof(param_1D));
    Control_OLED(0x30, param_30, sizeof(param_30));
    Control_OLED(0x32, param_32, sizeof(param_32));
    Control_OLED(0x34, param_34, sizeof(param_34));
    Control_OLED(0x35, param_35, sizeof(param_35));
    Control_OLED(0x36, param_36, sizeof(param_36));
    Control_OLED(0x37, param_37, sizeof(param_37));
    Control_OLED(0x38, param_38, sizeof(param_38));
    Control_OLED(0x39, param_39, sizeof(param_39));
    Control_OLED(0x48, param_48, sizeof(param_48));
    Control_OLED(0xD0, param_D0, sizeof(param_D0));
    Control_OLED(0xD2, param_D2, sizeof(param_D2));
    Control_OLED(0xD9, param_D9, sizeof(param_D9));
    Control_OLED(0xDB, param_DB, sizeof(param_DB));
    Control_OLED(0xDD, param_DD, sizeof(param_DD));
    Control_OLED(0xE0, param_E0, sizeof(param_E0));
    Control_OLED(0xE2, param_E2, sizeof(param_E2));
    Control_OLED(0xE3, param_E3, sizeof(param_E3));
    Control_OLED(0xE4, param_E4, sizeof(param_E4));
    Control_OLED(0xE5, param_E5, sizeof(param_E5));
    Control_OLED(0xE6, param_E6, sizeof(param_E6));
    Control_OLED(0xE7, param_E7, sizeof(param_E7));
    Control_OLED(0xFD, param_FD, sizeof(param_FD));

    // follow by OLED write
}

//-----------------------------------------------------------------------------
// Turn OFF OLED
//-----------------------------------------------------------------------------
void Power_OFF(void)
{
    SPI0CN_NSSMD0 = 1;  // XCS = NSS = H
    XRES = 0;
    Wait_us_Timer1(1);
    //VAH OFF
    //SCK (SCL / D6), MOSI (SI / D7) H, else L.
}

//-----------------------------------------------------------------------------
// Stand-by Mode ON/OFF
//-----------------------------------------------------------------------------
void Set_Standby(bool enable)
{
    uint8_t input[1];
    input[0] = enable ? 0x01 : 0x00;   // Standby OFF when false(0x00)
    Control_OLED(0x14, input, sizeof(input));
}

//-----------------------------------------------------------------------------
// Power Save Mode ON/OFF (VAH ON/OFF, after Stand-by Mode ON only)
//-----------------------------------------------------------------------------
// can realize through GPIO

//-----------------------------------------------------------------------------
//  OLED Frame ON/OFF
//-----------------------------------------------------------------------------
void Set_Display(bool enable)
{
    uint8_t input[1];
    input[0] =  enable ? 0x01 : 0x00;   // Display ON when true(0x01)
    Control_OLED(0x02,  input, sizeof(input));
}

//-----------------------------------------------------------------------------
// OLED brightness update & brightness schedule
//-----------------------------------------------------------------------------
void Set_Brightness(uint8_t level)
{
    uint8_t input[1];   // must be on the top as old C....

    level = level % 0x10;  // max value is 0x0F

    input[0] = level;
    Control_OLED(0xDB, input, 1);
}

// local brightness list
const uint8_t code schedule[] ={0x0E, 0x0A, 0x08, 0x06, 0x04, 0x03, 0x02};

void Update_Brightness(void)
{
    static uint8_t idx = 0;
    Set_Brightness(schedule[idx]);

    idx++;
    if (idx >= sizeof(schedule)) {
        idx = 0;
    }
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Can't use when in Stand-by with VAH
void Rotate180(uint8_t enable, const uint8_t* frame_list, uint8_t frame_list_len)
{
    uint8_t input[1];
    input[0] = (enable ? 0x0B : 0x00);    // Rotate 180  when enable == 1(0x0B)
    Control_OLED(0x1D, input, sizeof(input));

    OLED_RW(frame_list, frame_list_len);
}

