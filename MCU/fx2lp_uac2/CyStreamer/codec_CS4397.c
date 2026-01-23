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
    // TxBuf[0] = CS4397_CONTROL1_ADDR;
    CS4397_AMute(ON);
    CS4397_Reset(ON);  
    EZUSB_Delay(2);

	// Reg.control1 = CS4397_ACKS | CS4397_DIF2 | CS4397_DIF1 | CS4397_DIF0 | CS4397_RSTN;
	// Reg.control2 = CS4397_SD | CS4397_DEM0;
	// Reg.control3 = 0x00;
	// Reg.lch_att = 0xFF;
	// Reg.rch_att = 0xFF;
	// Reg.control4 = CS4397_INVL;
	// Reg.dsd1 = 0x00;
	// Reg.control5 = CS4397_SYNCE;
	// Reg.sound_control = 0x00;
	// Reg.dsd2 = 0x00;
	// Reg.control6 = CS4397_PW;
	// Reg.control7 = 0x00;
	// Reg.control8 = CS4397_ADPE;

    // memcpy(&TxBuf[1], &Reg, sizeof(Reg));

    // EZUSB_WriteI2C(CS4397_I2C_ADDR, sizeof(TxBuf), TxBuf);
    // I2C_POLL_FOR_COMPLETE();

	return TRUE;
}

uint8_t CS4397_DeInit()
{
    CS4397_SetMute(ON);
    CS4397_Reset(ON);
}

static void CS4397_PMC(uinit8_t pmc)
{
    TxBuf[0] = CS4397_CONTROL1_ADDR;
    switch(pmc){
        case ON:
            reg.control1 |= ~CS4397_PDN;
            TxBuf[1] = reg.control1;
            break;
        case OFF:
            reg.control1 |= CS4397_PDN;
            TxBuf[1] = reg.control1;
            break;
        default:
            return FALSE;     
    }

    EZUSB_WriteI2C(CS4397A_I2C_ADDR, 2, TxBuf);
    I2C_POLL_FOR_COMPLETE();

    EZUSB_WriteI2C(CS4397B_I2C_ADDR, 2, TxBuf);
    I2C_POLL_FOR_COMPLETE();

    EZUSB_WriteI2C(CS4397C_I2C_ADDR, 2, TxBuf);
    I2C_POLL_FOR_COMPLETE();

    return TRUE;   
}

static void CS4397_Reset(uint8_t reset)
{
    //Reset ON
    switch (reset)
    {
    case ON:
        reg.control_board |= ~PCF8574_RESET;
        TxBuf[0] =  reg.control_board;
        EZUSB_WriteI2C(PCF8574_I2C_ADDR, 1, TxBuf);
        I2C_POLL_FOR_COMPLETE();
        break;
    case OFF:
        reg.control_board |= PCF8574_RESET;
        TxBuf[0] =  reg.control_board;
        EZUSB_WriteI2C(PCF8574_I2C_ADDR, 1, TxBuf);
        I2C_POLL_FOR_COMPLETE();
        break;
    default:
        reg.control_board |= ~PCF8574_RESET;
        TxBuf[0] =  reg.control_board;
        EZUSB_WriteI2C(PCF8574_I2C_ADDR, 1, TxBuf);
        I2C_POLL_FOR_COMPLETE();

        EZUSB_Delay1ms;
        //Normal Operation
        reg.control_board |= PCF8574_RESET;
        TxBuf[0] =  reg.control_board;
        EZUSB_WriteI2C(PCF8574_I2C_ADDR, 1, TxBuf);
        I2C_POLL_FOR_COMPLETE();
        break;
    }
    return TRUE;
}

uint8_t CS4397_SetMute(uint8_t mute)
{
    switch(mute){
        case ON:
            CS4397_AMute(ON);
            CS4397_SoftMute(ON);
            break;
        case OFF:
            CS4397_AMute(OFF);
            CS4397_SoftMute(OFF);
            break;
        default:
            return FALSE;
    }
	return TRUE;
}

static void CS4397_AMute(uint8_t amute) //Amute will power off the LFP and HardMute the DAC
{
    switch (amute)
    {
    case OFF:
        reg.control_board |= ~PCF8574_AMUTE;
        TxBuf[0] = reg.control_board;
        break;
    
    default:
        reg.control_board |= PCF8574_AMUTE;
        TxBuf[0] = reg.control_board;
        break;
    }  

    EZUSB_WriteI2C(PCF8574_I2C_ADDR, 1, TxBuf);
    I2C_POLL_FOR_COMPLETE();

	return TRUE;
}

static void CS4397_SoftMute(uint8_t softmute)
{
    TxBuf[0] = CS4397_CONTROL1_ADDR;

    switch (softmute)
    {
    case OFF:
        reg.control1 |= CS4397_SMUTE;
        TxBuf[1] = reg.control1;
        break;
    
    default:
        reg.control1 |= ~CS4397_SMUTE;
        TxBuf[1] = reg.control1;
        break;
    }

    EZUSB_WriteI2C(CS4397A_I2C_ADDR, 2, TxBuf);
    I2C_POLL_FOR_COMPLETE();

    EZUSB_WriteI2C(CS4397B_I2C_ADDR, 2, TxBuf);
    I2C_POLL_FOR_COMPLETE();

    EZUSB_WriteI2C(CS4397C_I2C_ADDR, 2, TxBuf);
    I2C_POLL_FOR_COMPLETE();

	return TRUE;
}

uint8_t CS4397_SetFormat(uint8_t format)
{
    // TxBuf[0] = CS4397_CONTROL3_ADDR;
    TxBuf[0] = CS4397_CONTROL1_ADDR;

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

uint8_t CS4397_SetFreq(uint8_t freq)
{
    // TxBuf[0] = CS4397_CONTROL3_ADDR;
    TxBuf[0] = EXT_MCLK_EN_SCKO2 | ;

    switch (freq) {
    case MultipleOf32K:
        Reg.control3 &= ~CS4397_DP;
        break;
    case MultipleOf44K1:
        Reg.control3 |= CS4397_DP;
        break;
    case MultipleOf48K:
        Reg.control3 |= CS4397_DP;
        break;
    default:
        return FALSE;
    }

    TxBuf[1] = Reg.control3;

    EZUSB_WriteI2C(PLL1708_I2C_ADDR_MOD, 1, TxBuf);
    I2C_POLL_FOR_COMPLETE();

	return TRUE;
}

uint8_t CS4397_SetMCLK(uint8_t mclk)
{


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




