#ifndef _GPIO_H_
#define _GPIO_H_

#include "fx2regs.h"

sbit CPLD_RST_N_PIN = IOA ^ 0;
sbit FB_REQ_PIN     = IOA ^ 7;
// sbit CODEC_RST_N_PIN = IOA ^ 6;

//Define SPI port
sbit MCLK_SPI_CS = IOA ^ 0;
sbit MCLK_SPI_SCK = IOA ^ 1;
sbit MCLK_SPI_SI = IOA ^ 2;

#endif // _GPIO_H_