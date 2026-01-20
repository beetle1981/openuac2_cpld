#ifndef _CS4397_H_
#define _CS4397_H_

#include <stdint.h>

// #define CS4397_I2C_ADDR           (0x10 << 1)
#define CS4397A_I2C_ADDR          0x10	//FL, FR -0010000
#define CS4397B_I2C_ADDR          0x11	//C, LFE -0010001
#define CS4397C_I2C_ADDR          0x12	//Ls, Rs -0010010
#define CS4397_I2C_ADDR           0x21	//other  -0100001

#define CS4397_CONTROL1_ADDR       0X01	//01H
// #define CS4397_CONTROL1_ADDR      0x00
// #define CS4397_CONTROL2_ADDR      0x01
// #define CS4397_CONTROL3_ADDR      0x02
// #define CS4397_LCH_ATT_ADDR       0x03
// #define CS4397_RCH_ATT_ADDR       0x04
// #define CS4397_CONTROL4_ADDR      0x05
// #define CS4397_DSD1_ADDR          0x06
// #define CS4397_CONTROL5_ADDR      0x07
// #define CS4397_SOUND_CONTROL_ADDR 0x08
// #define CS4397_DSD2_ADDR          0x09
// #define CS4397_CONTROL6_ADDR      0x0a
// #define CS4397_CONTROL7_ADDR      0x0b
// #define CS4397_CONTROL8_ADDR      0x15

// Control 1
#define CS4397_CAL		(1U << 7)	//Initiate a calibration to miniize the differrential DC offset. default: 0 - disable
#define CS4397_SMUTE		(1U << 6)	//L: MUTE H: unmute; default: 0 - enable
#define CS4397_M4		(1U << 5)	//
#define CS4397_M3		(1U << 4)
#define CS4397_M2		(1U << 3)
#define CS4397_M1		(1U << 2)
#define CS4397_M0		(1U << 1)
#define CS4397_PDN		(1U << 0) //L: ON; H: OFF; default: 1 - power down

// #define CS4397_ACKS  (1U << 7)
// #define CS4397_EXDF  (1U << 6)
// #define CS4397_ECS   (1U << 5)
// #define CS4397_DIF2  (1U << 3)
// #define CS4397_DIF1  (1U << 2)
// #define CS4397_DIF0  (1U << 1)
// #define CS4397_RSTN  (1U << 0)

// Control 2
#define CS4397_MCK_SEL	(1U << 7)	//H: internal; L: external
#define CS4397_MCK_Freq	(1U << 6)   //H: 384Fs; L: 192Fs
#define CS4397_reset 	(1U << 5)	//H: normal; L: reset
// #define CS4397_DFS1		(1U << 4)
// #define CS4397_DFS0		(1U << 3)
#define CS4397_DSD_GAIN	(1U << 2)	//H: DSD; L: PCM
#define CS4397_DSD_ACT	(1U << 1)	//H: DSD L: PCM
#define CS4397_HMUTE	(1U << 0)	//H: ON; L: OFF

// // Control 3
// #define CS4397_DP    (1U << 7)
// #define CS4397_ADP	  (1U << 6)
// #define CS4397_DCKS  (1U << 5)
// #define CS4397_DCKB  (1U << 4)
// #define CS4397_MONO  (1U << 3)
// #define CS4397_DZFB  (1U << 2)
// #define CS4397_SELLR (1U << 1)
// #define CS4397_SLOW  (1U << 0)

// // Control 4
// #define CS4397_INVL  (1U << 7)
// #define CS4397_INVR  (1U << 6)
// #define CS4397_DFS2  (1U << 1)
// #define CS4397_SSLOW (1U << 0)

// // DSD1
// #define CS4397_DDM     (1U << 7)
// #define CS4397_DML     (1U << 6)
// #define CS4397_DMR     (1U << 5)
// #define CS4397_DDMOE   (1U << 4)
// #define CS4397_DDMT1   (1U << 3)
// #define CS4397_DDMT0   (1U << 2)
// #define CS4397_DSDD    (1U << 1)
// #define CS4397_DSDSEL0 (1U << 0)

// // Control 5
// #define CS4397_MSTBN   (1U << 7)
// #define CS4397_GC2     (1U << 3)
// #define CS4397_GC1     (1U << 2)
// #define CS4397_GC0     (1U << 1)
// #define CS4397_SYNCE   (1U << 0)

// // Sound control
// #define CS4397_SC2     (1U << 2)

// // DSD2
// #define CS4397_DSDF    (1U << 1)
// #define CS4397_DSDSEL1 (1U << 0)

// // Control 6
// #define CS4397_TDM1  (1U << 7)
// #define CS4397_TDM0  (1U << 6)
// #define CS4397_SDS1  (1U << 5)
// #define CS4397_SDS2  (1U << 4)
// #define CS4397_PW    (1U << 2)

// // Control 7
// #define CS4397_ATS1  (1U << 7)
// #define CS4397_ATS0  (1U << 6)
// #define CS4397_SDS0  (1U << 4)
// #define CS4397_TEST  (1U << 0)

// // Control 8
// #define CS4397_ADPE   (1U << 7)
// #define CS4397_ADPT1  (1U << 6)
// #define CS4397_ADPT0  (1U << 5)

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
