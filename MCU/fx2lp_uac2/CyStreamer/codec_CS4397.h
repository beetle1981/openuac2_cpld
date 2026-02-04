#ifndef _CS4397_H_
#define _CS4397_H_

#include <stdint.h>

// #define CS4397_I2C_ADDR           (0x10 << 1)
#define CS4397A_I2C_ADDR	0x10	//FL, FR -0010000
#define CS4397B_I2C_ADDR	0x11	//C, LFE -0010001
#define CS4397C_I2C_ADDR	0x12	//Ls, Rs -0010010
#define PCF8574_I2C_ADDR	0x21	//other  -0100001
#define PLL1708_I2C_ADDR_MOD	0x38	//Mode Address
#define PLL1708_I2C_ADDR_SCKO1	0x36	//SCKO1 Address

#define CS4397_CONTROL_ADDR       0X01	//01H


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
#define CS4397_SS_DEM_44K1	(1U << 3) //44.1kHz De-Emphasis
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
#define CS4397_QUD_FMT_R24	(27U << 1) //Right Justified 24-bit data, format 3
//8x Interpolated Input Mode Options
#define CS4397_8X_FMT_R20	(16U << 1) //Right Justified 20-bit data
#define CS4397_8X_FMT_R24	(17U << 1) //Right Justified 24-bit data
//DSD options
#define CS4397_DSD_64		(20U << 1) //DSD64
#define CS4397_DSD_128		(21U << 1) //DSD128

// ------------------Control Board
#define PCF8574_MCK_INT		(1U << 7)	//H: internal; L: external
#define PCF8574_MCK_384FS	(1U << 6)   //H: 384Fs; L: 192Fs
#define PCF8574_RESET 		(1U << 5)	//H: normal; L: reset ON
// #define PCF8574_DFS1		(1U << 4)
// #define PCF8574_DFS0		(1U << 3)
#define PCF8574_DSD_GAIN	(1U << 2)	//H: DSD; L: PCM
#define PCF8574_DSD_ACT		(1U << 1)	//H: DSD L: PCM
#define PCF8574_AMUTE		(1U << 0)	//H: ON; L: OFF

//------------------Control MCLK
#define EXT_MCLK_EN_SCKO1	(1U << 7)  //SCKO1 Enable(default)
#define EXT_MCLK_EN_SCKO3	(1U << 6)  //SCKO3 Enable(default)
#define EXT_MCLK_EN_SCKO2	(1U << 5)  //SCKO2 Enable(default)
#define EXT_MCLK_EN_MCKO0	(1U << 4)  //SCKO0 Enable(default)
// //Sampling Rate Select
// #define EXT_MCLK_SR_DAUL	(1U << 2)  //Sampling rate double
// #define EXT_MCLK_SR_HALF	(2U << 2)  //Sampling rate half
// #define EXT_MCLK_SR_STD		(0U << 2)  //Sampling rate standard
// //Frequency Select
// #define EXT_MCLK_FS_48K		(0U)	//Fs = 48kHz(default)
// #define EXT_MCLK_FS_41K		(1U)	//Fs = 44.1kHz(default)
// #define EXT_MCLK_FS_32K		(2U)	//Fs = 32kHz(default)
//External MCLK select
#define EXT_MCLK_32K	((1U << 2) | 2U)	//Fs = 32kHz, SCKO2 = 16.3840MHz, SCKO3 = 24.576MHz
#define EXT_MCLK_44K1	((1U << 2) | 1U)	//Fs = 44.1kHz, SCKO2 = 22.5792MHz, SCKO3 = 33.8688MHz
#define EXT_MCLK_48K	((1U << 2) | 0U)	//Fs = 48kHz, SCKO2 = 24.576MHz, SCKO3 = 36.864MHz
#define EXT_MCLK_DSD	((0U << 2) | 1U)	//DSD64 or DSD128, SCKO2 = 11.2896MHz, SCKO3 = 16.9344MHz

typedef struct 
{
	uint8_t dac;		//DAC Chip control
	uint8_t board;	//Board control
	uint8_t mclk;	//external MCLK control
} CS4397_RegisterTypeDef;



uint8_t CS4397_Init();
uint8_t CS4397_DeInit();
// uint8_t CS4397_SetVolume(uint8_t vol);
uint8_t CS4397_SetMute(uint8_t mute);
uint8_t CS4397_SetFormat(uint8_t format);
uint8_t CS4397_SetFreq(uint8_t frequency);
// uint8_t CS4397_Play();
// uint8_t CS4397_Stop();

#endif // _CS4397_H_
