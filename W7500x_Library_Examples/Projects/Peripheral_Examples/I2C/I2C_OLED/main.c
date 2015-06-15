/**
  ******************************************************************************
  * @file    I2C/I2C_OLED/main.c 
  * @author  IOP Team
  * @version V1.0.0
  * @date    15-JUN-2015
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, WIZnet SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2015 WIZnet Co.,Ltd.</center></h2>
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "W7500x.h"
#include "OLED_I2C.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define MAX_SIZE 9
#define OLED_ADDRESS	0x78
#define SCL GPIO_Pin_9
#define SDA GPIO_Pin_10
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
I2C_ConfigStruct conf;
GPIO_InitTypeDef GPIO_Def;
///                   memaddress,data0,data1 data2,data3,data4,data5,data6,data7
uint8_t Transmit_Data[MAX_SIZE]={0x00, 0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8};
uint8_t Recv_Data[MAX_SIZE];
/* Private function prototypes -----------------------------------------------*/
void delay_us(int us);
void delay_ms(int count);
/* Private functions ---------------------------------------------------------*/

int main()
{

	SystemInit();

    conf.mode = I2C_Master;
    conf.slave_address = 0x78;
    conf.master.prescale = 0x61;
    conf.master.timeout = 0x006F;
    
    I2C_Init(I2C0, conf);
    OLED_Init();
	
	
	OLED_Fill(0xFF);
	delay_ms(20);
	OLED_Fill(0x00);
	delay_ms(10);
    
	OLED_ShowStr(0,3,"Welcome to",1);
	OLED_ShowStr(0,4,"WIznet Academy^^",2);	

  } 
void delay_us(int us)
{
        volatile uint32_t delay = us; // approximate loops per ms at 24 MHz, Debug config
    for(; delay != 0; delay--)
        __NOP();
}
void delay_ms(int count) {
        delay_us(count*1000);
}

