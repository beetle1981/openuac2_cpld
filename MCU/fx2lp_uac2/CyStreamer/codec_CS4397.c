#include "codec_CS4397.h"

#include "codec.h"
#include "gpio.h"

#include <stddef.h>
#include <string.h>

#define I2C_POLL_FOR_COMPLETE() while (I2CPckt.status != I2C_IDLE)

static CS4397_RegisterTypeDef xdata reg;
static uint8_t xdata TxBuf[sizeof(CS4397_RegisterTypeDef) + 1];

CODEC_TypeDef code codec =
{
	CS4397_Init,
	CS4397_DeInit,
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
    // CS4397_RegisterTypeDef xdata *reg = &TxBuf[1];
    // TxBuf[0] = CS4397_dac_ADDR;
    CS4397_AMute(ON);
    CS4397_Reset(OFF);
    CS4397_PMC(ON);  
    // EZUSB_Delay(2);

    
	return TRUE;
}

uint8_t CS4397_DeInit()
{
    CS4397_SetMute(ON);
    CS4397_Reset(ON);
}

static void CS4397_PMC(uint8_t pmc)
{
    if (ON) //default: 1 - Power Down
        reg.dac |= ~CS4397_PDN;
    else
        reg.dac |= CS4397_PDN;
    UpdateReg(DAC);
    return TRUE;   
}

static void CS4397_Reset(uint8_t reset)
{
    //Reset ON
    switch (reset)
    {
    case ON:
        reg.board |= ~PCF8574_RESET;
        UpdateReg(BOARD);
        break;
    case OFF:
        reg.board |= PCF8574_RESET;
        UpdateReg(BOARD);
        break;
    default:
        reg.dac |= CS4397_CAL;
        UpdateReg(DAC);
    }
    return TRUE;
}

uint8_t CS4397_SetMute(uint8_t mute)
{
    if (mute)
    {
        CS4397_AMute(mute);
        CS4397_SoftMute(mute);
    }
    else{
        CS4397_AMute(mute);
        CS4397_SoftMute(mute);
    }
	return TRUE;
}

static void CS4397_AMute(uint8_t mute) //Amute will power off the LFP and HardMute the DAC
{
    if (mute)
        reg.board |= ~PCF8574_AMUTE;
    else
        reg.board |= PCF8574_AMUTE;
    UpdateReg(BOARD);
	return TRUE;
}

static void CS4397_SoftMute(uint8_t mute)
{
    if (mute)
        reg.dac |= CS4397_SMUTE;
    else
        reg.dac |= ~CS4397_SMUTE;
    UpdateReg(DAC);
	return TRUE;
}

uint8_t CS4397_SetFormat(uint8_t freq, uint8_t interface)
{
    switch (freq)
    {
    case 32000: //32K
        reg.dac = (interface == 2) ? CS4397_SS_DEM_32K | CS4397_SS_FMT_R24 : CS4397_SS_DEM_32K | CS4397_SS_FMT_R16;
        break;
    case 64000: //64K
        reg.dac = (interface == 2) ? CS4397_DUL_FMT_R24 : CS4397_DUL_FMT_R16;
        break;
    case 44100: //44K1
        reg.dac = (interface == 2) ? CS4397_SS_DEM_44K1 | CS4397_SS_FMT_R24 : CS4397_SS_DEM_44K1 | CS4397_SS_FMT_R16;
        break;
    case 88200: //88K2
        reg.dac = (interface == 2) ? CS4397_DUL_FMT_R24 : CS4397_DUL_FMT_R16;
        break;
    case 176400: //176K4
        reg.dac = (interface == 2) ? CS4397_QUD_FMT_R24 : CS4397_QUD_FMT_R16;
        break;
    case 48000: //48K
        reg.dac = (interface == 2) ? CS4397_SS_DEM_48K | CS4397_SS_FMT_R24 : CS4397_SS_DEM_48K | CS4397_SS_FMT_R16;
        break;
    case 96000: //96K
        reg.dac = (interface == 2) ? CS4397_DUL_FMT_R24 : CS4397_DUL_FMT_R16;
        break;
    case 192000: //192K
        reg.dac = (interface == 2) ? CS4397_QUD_FMT_R24 : CS4397_QUD_FMT_R16;
        break;
    case 2822400: //DSD64
        reg.dac = (interface == 4) ? CS4397_DSD_64 : NULL;
        break;
    case 5644800: //DSD128
        reg.dac = (interface == 4) ? CS4397_DSD_128 : NULL;
        break;    
    default:
        reg.dac |= CS4397_PDN;
        break;
    }
    reg.dac |= CS4397_SMUTE;
    UpdateReg(DAC);
    CS4397_AMute();
	return TRUE;
}

uint8_t CS4397_SetFreq(uint8_t freq)
{
    switch (freq) {
    case FS_32K_XN:
        reg.board != ~PCF8574_MCK_INT;
        reg.mclk = EXT_MCLK_32K;
        break;
    case FS_44K1_XN:
        reg.board != ~PCF8574_MCK_INT;
        reg.mclk = EXT_MCLK_44K1;
        break;
    case FS_48K_XN:
        reg.board != ~PCF8574_MCK_INT;
        reg.mclk = EXT_MCLK_48K;
        break;
    case FS_DSD:
        reg.board != ~PCF8574_MCK_INT;
        reg.mclk = EXT_MCLK_DSD;
        break;
    default:
        reg.board != PCF8574_MCK_INT;
        break;
    }
    CS4397_SoftMute(mute);
    UpdateReg(MCLK); //config mclk
    UpdateReg(BOARD);
	return TRUE;
}

static void UpdateReg(uint8_t regx)
{
    switch (regx)
    {
    case DAC:
        TxBuf[0] = CS4397_CONTROL_ADDR;
        TxBuf[1] = reg.dac;
        EZUSB_WriteI2C(CS4397A_I2C_ADDR, 2, TxBuf);
        I2C_POLL_FOR_COMPLETE();

        EZUSB_WriteI2C(CS4397B_I2C_ADDR, 2, TxBuf);
        I2C_POLL_FOR_COMPLETE();

        EZUSB_WriteI2C(CS4397C_I2C_ADDR, 2, TxBuf);
        I2C_POLL_FOR_COMPLETE();
        break;
    case BOARD:
        TxBuf[0] = reg.board;
        EZUSB_WriteI2C(PCF8574_I2C_ADDR, 1, TxBuf);
        I2C_POLL_FOR_COMPLETE();
        break;
    case MCLK:
        TxBuf[0] = reg.mclk;
        EZUSB_WriteI2C(PLL1708_I2C_ADDR_MOD, 1, TxBuf);
        I2C_POLL_FOR_COMPLETE();
    default: //mclk config
        return FALSE;
    }
    return TRUE;
}

// void SPIByteWrite(unsigned char b)
// // caller manages SPI_CS signal
// {
//     SPI_CLK = 0;
//     if(b & 0x80) MOSI = 1;else MOSI= 0;
//     SPI_CLK = 1; SPI_CLK = 0;
//     if(b & 0x40) MOSI = 1;else MOSI= 0;
//     SPI_CLK = 1; SPI_CLK = 0;
//     if(b & 0x20) MOSI = 1;else MOSI= 0;
//     SPI_CLK = 1; SPI_CLK = 0;
//     if(b & 0x10) MOSI = 1;else MOSI= 0;
//     SPI_CLK = 1; SPI_CLK = 0;
//     if(b & 0x08) MOSI = 1;else MOSI= 0;
//     SPI_CLK = 1; SPI_CLK = 0;
//     if(b & 0x04) MOSI = 1;else MOSI= 0;
//     SPI_CLK = 1; SPI_CLK = 0;
//     if(b & 0x02) MOSI = 1;else MOSI= 0;
//     SPI_CLK = 1; SPI_CLK = 0;
//     if(b & 0x01) MOSI = 1;else MOSI= 0;
//     SPI_CLK = 1; SPI_CLK = 0;
// }


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




