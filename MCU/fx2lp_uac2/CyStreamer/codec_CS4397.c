#include "codec_CS4397.h"

#include "codec.h"
#include "gpio.h"

#include <stddef.h>
#include <string.h>

#define I2C_POLL_FOR_COMPLETE() while (I2CPckt.status != I2C_IDLE)

static CS4397_RegisterTypeDef xdata Reg;
static uint8_t xdata TxBuf[sizeof(CS4397_RegisterTypeDef) + 1];

CODEC_TypeDef code codec =
{
	CS4397_Init,
	NULL,
    NULL,
    NULL,
	CS4397_SetFormat,
    CS4397_SetFreq,
	CS4397_SetMute,
	// CS4397_SetVolume,
    NULL
};

uint8_t CS4397_Init()
{
    CS4397_RegisterTypeDef xdata *reg = &TxBuf[1];
    TxBuf[0] = CS4397_CONTROL1_ADDR;

    CODEC_RST_N_PIN = 1;  
    EZUSB_Delay(2);

	Reg.control1 = CS4397_ACKS | CS4397_DIF2 | CS4397_DIF1 | CS4397_DIF0 | CS4397_RSTN;
	Reg.control2 = CS4397_SD | CS4397_DEM0;
	Reg.control3 = 0x00;
	Reg.lch_att = 0xFF;
	Reg.rch_att = 0xFF;
	Reg.control4 = CS4397_INVL;
	Reg.dsd1 = 0x00;
	Reg.control5 = CS4397_SYNCE;
	Reg.sound_control = 0x00;
	Reg.dsd2 = 0x00;
	Reg.control6 = CS4397_PW;
	Reg.control7 = 0x00;
	Reg.control8 = CS4397_ADPE;

    memcpy(&TxBuf[1], &Reg, sizeof(Reg));

    EZUSB_WriteI2C(CS4397_I2C_ADDR, sizeof(TxBuf), TxBuf);
    I2C_POLL_FOR_COMPLETE();

	return TRUE;
}

// uint8_t CS4397_SetVolume(uint8_t vol)
// {
//     TxBuf[0] = CS4397_LCH_ATT_ADDR;

//     vol = (vol > 0) ? (vol + 155) : 0;
//     Reg.lch_att = Reg.rch_att = vol;

//     memcpy(TxBuf + 1, &Reg.lch_att, 2);

//     EZUSB_WriteI2C(CS4397_I2C_ADDR, 3, TxBuf);
//     I2C_POLL_FOR_COMPLETE();

// 	return TRUE;
// }

uint8_t CS4397_SetMute(uint8_t mute)
{
    TxBuf[0] = CS4397_CONTROL2_ADDR;

    if (mute)
        Reg.control2 |= CS4397_SMUTE;
    else
        Reg.control2 &= ~CS4397_SMUTE;

    TxBuf[1] = Reg.control2;

    EZUSB_WriteI2C(CS4397_I2C_ADDR, 2, TxBuf);
    I2C_POLL_FOR_COMPLETE();

	return TRUE;
}

static void CS4397_SoftReset(BOOL reset)
{
    TxBuf[0] = CS4397_CONTROL1_ADDR;
    TxBuf[1] = CS4397_RSTN & reset;
}

uint8_t CS4397_SetFormat(uint8_t format)
{
    TxBuf[0] = CS4397_CONTROL3_ADDR;

    switch (format) {
    case CODEC_FORMAT_PCM:
        Reg.control3 &= ~CS4397_DP;
        break;
    case CODEC_FORMAT_DSD:
        Reg.control3 |= CS4397_DP;
        break;
    default:
        return FALSE;
    }

    TxBuf[1] = Reg.control3;

    EZUSB_WriteI2C(CS4397_I2C_ADDR, 2, TxBuf);
    I2C_POLL_FOR_COMPLETE();

	return TRUE;
}

void SPIByteWrite(unsigned char b)
// caller manages SPI_CS signal
{
    SPI_CLK = 0;
    if(b & 0x80) MOSI = 1;else MOSI= 0;
    SPI_CLK = 1; SPI_CLK = 0;
    if(b & 0x40) MOSI = 1;else MOSI= 0;
    SPI_CLK = 1; SPI_CLK = 0;
    if(b & 0x20) MOSI = 1;else MOSI= 0;
    SPI_CLK = 1; SPI_CLK = 0;
    if(b & 0x10) MOSI = 1;else MOSI= 0;
    SPI_CLK = 1; SPI_CLK = 0;
    if(b & 0x08) MOSI = 1;else MOSI= 0;
    SPI_CLK = 1; SPI_CLK = 0;
    if(b & 0x04) MOSI = 1;else MOSI= 0;
    SPI_CLK = 1; SPI_CLK = 0;
    if(b & 0x02) MOSI = 1;else MOSI= 0;
    SPI_CLK = 1; SPI_CLK = 0;
    if(b & 0x01) MOSI = 1;else MOSI= 0;
    SPI_CLK = 1; SPI_CLK = 0;
}

uint8_t CS4397_SetMCLK(uint8_t mclk)
{

}


