#ifndef _CS4397_H_
#define _CS4397_H_

#include <stdint.h>

// #define CS4397_I2C_ADDR           (0x10 << 1)
#define CS4397A_I2C_ADDR	0x10	//FL, FR -0010000
#define CS4397B_I2C_ADDR	0x11	//C, LFE -0010001
#define CS4397C_I2C_ADDR	0x12	//Ls, Rs -0010010
#define PCF8574_I2C_ADDR	0x21	//other  -0100001
#define PLL1708_I2C_ADDR	0x

#define CS4397_CONTROL1_ADDR       0X01	//01H


// Control 1
#define CS4397_CAL		(1U << 7)	//Initiate a calibration to miniize the differrential DC offset. default: 0 - disable
#define CS4397_SMUTE	(1U << 6)	//L: MUTE H: unmute; default: 0 - enable
#define CS4397_PDN		(1U << 0) //L: ON; H: OFF; default: 1 - power down
//Format control single speed
#define CS4397_SS_FMT_LFT	(0U << 1) //Left Justified, up to 24 bit
#define CS4397_SS_FMT_I2S	(1U << 1) //I2S, up to 24 bit
#define CS4397_SS_FMT_R16	(2U << 1) //Right Justified, 16 bit data
#define CS4397_SS_FMT_R24	(3U << 1) //Right Justified, 24 bit data
//De-Emphasis single speed
#define CS4397_SS_DEM_32K	(0U << 3) //32kHz De-Emphasis
#define CS4397_SS_DEM_44K	(1U << 3) //44.1kHz De-Emphasis
#define CS4397_SS_DEM_48K	(2U << 3) //48kHz De-Emphasis
#define CS4397_SS_DEM_OFF	(3U << 3) //De-Emphasis Disabled
//Double Speed Sample Rate control
#define CS4397_DUL_FMT_LFT	(28U << 1) //Left Justified up to 24-bit data, format 0
#define CS4397_DUL_FMT_I2S	(29U << 1) //I2S up to 24-bit data, format 1
#define CS4397_DUL_FMT_R16	(30U << 1) //Right Justified 16-bit data, format 2
#define CS4397_DUL_FMT_R24	(31U << 1) //Right Justified 24-bit data, format 3
//Quad Speed Sample Rate control
#define CS4397_QUD_FMT_LFT	(24U << 1) //Left Justified up to 24-bit data, format 0
#define CS4397_QUD_FMT_I2S	(25U << 1) //I2S up to 24-bit data, format 1
#define CS4397_QUD_FMT_R16	(26U << 1) //Right Justified 16-bit data, format 2
#define CS4397_QUD_FMT_R14	(27U << 1) //Right Justified 24-bit data, format 3
//8x Interpolated Input Mode Options
#define CS4397_8X_FMT_R20	(16U << 1) //Right Justified 20-bit data
#define CS4397_8X_FMT_R24	(17U << 1) //Right Justified 24-bit data
//DSD options
#define CS4397_DSD_64		(20U << 1) //DSD64
#define CS4397_DSD_128		(21U << 1) //DSD128

// Control 2
#define PCF8574_MCK_SEL		(1U << 7)	//H: internal; L: external
#define PCF8574_MCK_Freq	(1U << 6)   //H: 384Fs; L: 192Fs
#define PCF8574_reset 		(1U << 5)	//H: normal; L: reset
// #define PCF8574_DFS1		(1U << 4)
// #define PCF8574_DFS0		(1U << 3)
#define PCF8574_DSD_GAIN	(1U << 2)	//H: DSD; L: PCM
#define PCF8574_DSD_ACT		(1U << 1)	//H: DSD L: PCM
#define PCF8574_HMUTE		(1U << 0)	//H: ON; L: OFF


typedef struct 
{
	uint8_t control1;
	uint8_t control2;
} CS4397_RegisterTypeDef;

uint8_t CS4397_Init();
// uint8_t CS4397_SetVolume(uint8_t vol);
uint8_t CS4397_SetMute(uint8_t mute);
uint8_t CS4397_SetFormat(uint8_t format);
uint8_t CS4397_SetFreq(uint8_t format);
// uint8_t CS4397_Play();
// uint8_t CS4397_Stop();

#endif // _CS4397_H_
