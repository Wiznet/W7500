#ifndef __OLED_I2C_H
#define	__OLED_I2C_H

#include "w7500x.h"


#define OLED_ADDRESS	0x78 //通过调整0R电阻,屏可以0x78和0x7A两个地址 -- 默认0x78
#define SCL GPIO_Pin_9
#define SDA GPIO_Pin_10

void I2C_Configuration(GPIO_TypeDef* GPIOx);
void I2C_WriteByte(GPIO_TypeDef* GPIOx,uint8_t addr,uint8_t data);
void WriteCmd(GPIO_TypeDef* GPIOx,unsigned char I2C_Command);
void WriteDat(GPIO_TypeDef* GPIOx,unsigned char I2C_Data);
void OLED_Init(GPIO_TypeDef* GPIOx);
void OLED_SetPos(GPIO_TypeDef* GPIOx,unsigned char x, unsigned char y);
void OLED_Fill(GPIO_TypeDef* GPIOx,unsigned char fill_Data);
void OLED_CLS(GPIO_TypeDef* GPIOx);
void OLED_ON(GPIO_TypeDef* GPIOx);
void OLED_OFF(GPIO_TypeDef* GPIOx);
void OLED_ShowStr(GPIO_TypeDef* GPIOx,unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize);
void OLED_ShowCN(GPIO_TypeDef* GPIOx,unsigned char x, unsigned char y, unsigned char N);
void OLED_DrawBMP(GPIO_TypeDef* GPIOx,unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);


#endif
