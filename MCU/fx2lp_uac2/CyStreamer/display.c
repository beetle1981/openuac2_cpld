/* for VFT display control */
#include "display.h"
// #include "fx2.h"

// #include <stddef.h>
// #include <string.h>

#define I2C_POLL_FOR_COMPLETE() while (I2CPckt.status != I2C_IDLE)

static Display_RegisterTypeDef xdata reg;
static uint8_t xdata TxBuf[sizeof(Display_RegisterTypeDef) + 1];
static Display_BufferTypeDef xdata  buffer;

Display_TypeDef code display =
{
    Init,
    DeInit,
    Echo,
    Clear,
    NULL,
    NULL
};

uint8_t Init()
{
    
    return TRUE;
}

uint8_t DeInit()
{
    return TRUE;
}

uint8_t Echo()
{
    return TRUE;
}

uint8_t Clear()
{
    return TRUE;
}

static void i2cWrite(uint16_t subaddr, uint8_t data)
{
    TxBuf[0] = (subaddr >> 8); // High byte
    TxBuf[1] = (subaddr & 0xFF); // Low byte
    TxBuf[2] = data;
    EZUSB_WriteI2C(TMP87CH74F_I2C_ADDR, 3, TxBuf);
    I2C_POLL_FOR_COMPLETE();
    return TRUE;
}