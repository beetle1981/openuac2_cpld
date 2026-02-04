#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include "fx2.h"
#include <stdint.h>

//#define TMP87 Slave Address
#define TMP87CH74F_I2C_ADDR 0x00

//define sub address
#define P0_PORT_ADDR        0x0000 //P0 port control
#define P1_PORT_ADDR        0x0001
#define P2_PORT_ADDR        0x0002
#define P3_PORT_ADDR        0x0003
#define P4_PORT_ADDR        0x0004
#define P5_PORT_ADDR        0x0005
#define P6_PORT_ADDR        0x0006
#define P7_PORT_ADDR        0x0007
#define P8_PORT_ADDR        0x0008
#define P9_PORT_ADDR        0x0009

#define P0_CR_ADDR          0x000a  //P0 I/O control, only write
#define P1_CR_ADDR          0x000b  //P1 I/O control
#define P4_CR_ADDR          0x000c  //P4 I/O control
#define P5_CR_ADDR          0x000d  //P5 I/O control
//A/D control
#define ADCCR_CTL_ADDR      0x000e //A/D converter control
#define ADCDR_CTL_ADDR      0x000f // A/D converter register

//timer register 1A
#define TREG1_A_ADDR_L      0x0010
#define TREG1_A_ADDR_H      0x0011
//timer register 1B
#define TREG1_B_ADDR_L      0x0012
#define TREG1_B_ADDR_H      0x0013

#define TC1_CR_ADDR         0x0014 //TC1 control
#define TC2_CR_ADDR         0x0015 //TC2 control

//timer register 2
#define TREG2_ADDR_L        0x0016
#define TREG2_ADDR_H        0x0017

//timer register 3 (8 BIT)
#define TREG3_A_ADDR_L      0x0018
#define TREG3_B_ADDR_H      0x0019
#define TC3_CR_ADDR         0x001a

#define TREG4_ADDR          0x001b
#define TC4_CR_ADDR         0x001c
#define PD_PORT_ADDR        0x001d

#define SBICR1_ADDR 		0x0020 //sbi control 1: write only
#define SBIDBR_ADDR 		0x0021 //display data buffer from 0F80 - 0FCF
#define SBICR2_ADDR 		0x0023 //read - SBI status; write - sbi control 2
#define EINTCR4_ADDR        0X0024 //external interrupt 4
#define EINTCR2_ADDR        0X0025 //external interrupt 2
#define EINTCR3_ADDR        0X0026 //external interrupt 3
#define SIO_CR1_ADDR        0x0027 //SIO1 control 1
#define SIO_CR2_ADDR        0x0028 //SIO1 control 2
#define VFT_CR1_ADDR 		0x0029 // WRITE: VFT control register 1 ; READ: BIT7 WAIT 0 - VFT DISPLAY IN OPERATION, 1 - OPERATION DISABLE
#define VFT_CR2_ADDR 		0x002a //WRITE ONLY, vft control register 2
#define P3_IO_ADDR 			0x002b //WRITE ONLY, P3 I/O control

#define WDT_CR1_ADDR        0x0034 //WDT cocntrol
#define WDT_CR2_ADDR        0x0035 //WDT cocntrol

#define TBT_CR_ADDR         0x0036 //TBT/TG/DVO control
#define EINT_CR_ADDR        0x0037 //Interrupt control

#define SYS_CR1_ADDR        0x0038 //System control
#define SYS_CR2_ADDR        0x0039 //System control

#define E_IR_ADDR_L         0x003a //Interrupt enable register
#define E_IR_ADDR_H         0x003b //Interrupt enable register
#define I_L_ADDR_L          0x003c //Interrupt latch
#define I_L_ADDR_H          0x003c //Interrupt latch
#define REG_BANK_ADDR       0x003f //write: Register bank selector; read - PSW(Program status word)
//Grid line G1-G14 (V1-V14); Seg line P1-P10 (V35-V21); Segment is Anode, for display pattern
#define VFT_DBR_GRID_ADDR_1		0x0f80  //Display data buffer 0x0f80 - 0x0f8f: T0 to T15 for PIN V0 to V7. Large current output 是栅极（Grid）
#define VFT_DBR_GRID_ADDR_2   	0x0f90  //Display data buffer 0x0f90 - 0x0f9f: T0 to T15 for PIN V8 to V15. Large current output
#define VFT_DBR_SEG_ADDR_3     	0x0fa0  //Display data buffer 0x0fa0 - 0x0faf: T0 to T15 for PIN V16 to V23. middle current output for segment 
#define VFT_DBR_SEG_ADDR_2     	0x0fb0  //Display data buffer 0x0fb0 - 0x0fbf: T0 to T15 for PIN V24 to V31. middle current output for segment 是阳极（Anode）
#define VFT_DBR_SEG_ADDR_1     	0x0fc0  //Display data buffer 0x0fc0 - 0x0fcf: T0 to T15 for PIN V32 to V36, bit 0 - 4. middle current output for segment

//VFT control register 1
#define VFTCR1_BLK_DISABLE  (1U << 7) // 0 - DISPLAY ENABLE
#define VFTCR1_SDT_00       (0U << 5) //2^9/fc
#define VFTCR1_SDT_01       (1U << 5) //2^10/fc
#define VFTCR1_SDT_10       (10U << 5) //2^11/fc
#define VFTCR1_SDT_01       (11U << 5) //2^12/fc
#define VFTCR1_VSEL_32      (0U)    //V31 TO V0
#define VFTCR1_VSEL_32      (1U)    //V32 TO V0
#define VFTCR1_VSEL_32      (2U)    //V33 TO V0
#define VFTCR1_VSEL_32      (3U)    //V34 TO V0
#define VFTCR1_VSEL_32      (4U)    //V35 TO V0
#define VFTCR1_VSEL_32      (5U)    //V36 TO V0

//VFT control register 2
//Dimmer time control
#define VFTCR2_DIM_15DIV16  (0U << 5) //DIMMER TIME SELECT 15/16 * TDISP (S)
#define VFTCR2_DIM_14DIV16  (1U << 5) //DIMMER TIME SELECT 14/16 * TDISP (S)
#define VFTCR2_DIM_12DIV16  (2U << 5) //DIMMER TIME SELECT 12/16 * TDISP (S)
#define VFTCR2_DIM_10DIV16  (3U << 5) //DIMMER TIME SELECT 10/16 * TDISP (S)
#define VFTCR2_DIM_8DIV16  (4U << 5) //DIMMER TIME SELECT 8/16 * TDISP (S)
#define VFTCR2_DIM_6DIV16  (5U << 5) //DIMMER TIME SELECT 6/16 * TDISP (S)
#define VFTCR2_DIM_4DIV16  (6U << 5) //DIMMER TIME SELECT 4/16 * TDISP (S)
#define VFTCR2_DIM_2DIV16  (7U << 5) //DIMMER TIME SELECT 2/16 * TDISP (S)
//Display mode control
#define VFTCR2_STA_1DM  (0U) //1 display mode(T0)
#define VFTCR2_STA_2DM  (1U) //2 display mode(T1 to T0)
#define VFTCR2_STA_3DM  (2U) //3 display mode(T2 to T0)
#define VFTCR2_STA_4DM  (3U) //4  display mode(T3 to T0)
#define VFTCR2_STA_5DM  (4U) //5 display mode(T4 to T0)
#define VFTCR2_STA_6DM  (5U) //6 display mode(T5 to T0)
#define VFTCR2_STA_7DM  (6U) //7 display mode(T6 to T0)
#define VFTCR2_STA_8DM  (7U) //8 display mode(T7 to T0)
#define VFTCR2_STA_9DM  (8U) //9 display mode(T8 to T0)
#define VFTCR2_STA_10DM  (9U) //10 display mode(T9 to T0)
#define VFTCR2_STA_11DM  (10U) //11 display mode(T10 to T0)
#define VFTCR2_STA_12DM  (11U) //12 display mode(T11 to T0)
#define VFTCR2_STA_13DM  (12U) //13 display mode(T12 to T0)
#define VFTCR2_STA_14DM  (13U) //14 display mode(T13 to T0)
#define VFTCR2_STA_15DM  (14U) //15 display mode(T14 to T0)
#define VFTCR2_STA_16DM  (15U) //16 display mode(T15 to T0)

typedef struct 
{
	uint8_t vft_control1;		//DAC Chip control
	uint8_t vft_control2;	//Board control
} Display_RegisterTypeDef;

typedef struct 
{
	uint8_t buffer_t0;		//T0 buffer
	uint8_t buffer_t1;		//T1 buffer
	uint8_t buffer_t2;		//T2 buffer
	uint8_t buffer_t3;		//T3 buffer
	uint8_t buffer_t4;		//T4 buffer
	uint8_t buffer_t5;		//T5 buffer
	uint8_t buffer_t6;		//T6 buffer
	uint8_t buffer_t7;		//T7 buffer
	uint8_t buffer_t8;		//T8 buffer
	uint8_t buffer_t9;		//T9 buffer
	uint8_t buffer_t10;		//T10 buffer
	uint8_t buffer_t11;		//T11 buffer
	uint8_t buffer_t12;		//T12 buffer
	uint8_t buffer_t13;		//T13 buffer
	uint8_t buffer_t14;		//T14 buffer
	uint8_t buffer_t15;		//T15 buffer
} Display_BufferTypeDef;

typedef struct
{
	uint8_t (*Init)(void);
	uint8_t (*DeInit)(void);
	uint8_t (*Echo)(void);
	uint8_t (*Clear)(void);
	uint8_t (*SetFormat)(uint8_t);
	uint8_t (*SetFreq)(uint32_t);
	uint8_t (*SetMute)(uint8_t);
	uint8_t (*SetVolume)(uint8_t);
} Display_TypeDef;


#endif //_DISPLAY_H_