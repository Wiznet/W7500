/**
  ******************************************************************************
  * @file    I2C/I2C_Init/main.c 
  * @author  IOP Team
  * @version V1.0.0
  * @date    01-May-2015
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
#include "W7500x.h"
#include <stdio.h>
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define Slave_address   0xA0
#define I2C_Debug
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
I2C_ConfigStruct conf;

int8_t I2C_1byte_rw(I2C_TypeDef * I2Cx,uint8_t Prescale,uint16_t Timeout,uint8_t SlaveAddress,uint8_t data);
void Delay_for(uint32_t nCount);
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief   Main program
  * @param  None
  * @retval None
  */
//This example send 2byte from master(I2c0) to slave(must have slave address )
int main()
{
    uint8_t data     =    0xAA;
	/*System clock configuration*/
	SystemInit();
    /* I2C Init */
    /*  I2C confiugred as follow:
     *  - I2C master mode
     *  - I2C slave address : 0xA0
     *  - I2C Prescale : 0x61
     *      If main clock is 20MHz,  SCL operate as 100KHz
     *  - I2C Timeout : 0xFFFF
     */
    conf.mode = I2C_Master;
    conf.slave_address = Slave_address;
    conf.master.prescale = 0x61;
    conf.master.timeout = 0xFFFF;
     /* Cofigure I2C0 */
    I2C_Init(I2C0, conf);
    /* I2C Start condition*/
    I2C_Start(I2C0,conf.slave_address,I2C_WRITE_SA7);
    /*Send data(0xAA) and it wait the ack*/
    I2C_SendDataAck(I2C0,data);
    /*Send data(0xAB) and it wait the ack*/
    I2C_SendDataAck(I2C0,data+1);
    /*Send Stop condition*/
    I2C_Stop(I2C0);

  } 


void Delay_for(uint32_t nCount)
{

for(; nCount != 0; nCount--);
    
}

