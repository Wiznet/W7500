/**
  ******************************************************************************
  * @file    I2C/I2C_Temperture_LM75A/main.c 
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
#define LM75_REG_TEMP   0x00
#define LM75_REG_CONF   0x01
#define LM75_REG_TOS    0x02
#define LM75_REG_THYS   0x03
#define LM75_7bitSlaveAddress 0x90
#define MAX_SIZE 10
#define I2C_Debug
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
UART_InitTypeDef UART_InitStructure;
I2C_ConfigStruct conf;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void Delay_for(uint32_t delay);
/**
  * @brief   Main program
  * @param  None
  * @retval None
  */

int main()
{
    int result;
    uint16_t recv_data =0;
    int cnt;
    

    /*System clock configuration*/
    SystemInit();
    /* UART0 and UART1 configuration*/
    UART_StructInit(&UART_InitStructure);
    /* Configure UART0 */
    UART_Init(UART1,&UART_InitStructure);
    printf("########  I2C LM75 Temperature TEST  #########\r\n");

    /* I2C Init */
    /*  I2C confiugred as follow:
     *  - I2C master mode
     *  - I2C slave address : 0x90
     *  - I2C Prescale : 0x61
     *     /If MCU clock is 20MHz and Prescale value is 0x61, SCL occurs 100KHz as clock.
     *  - I2C Timeout : 0xFFFF
     */
    conf.mode = I2C_Master;
    conf.slave_address = LM75_7bitSlaveAddress;
    conf.master.prescale = 0x61;
    conf.master.timeout = 0xFFFF;
    /* Cofigure I2C0 */
    I2C_Init(I2C0, conf);
    /* Temperature Read Test*/
    /*START - send LM75 slave address  - send LM75_REG_TEMP Register address - receive temperature data*/
    I2C_Start(I2C0,conf.slave_address,I2C_WRITE_SA7);
    
    /*LM75_REG_TEMP register to read LM75*/
    I2C_SendDataAck(I2C0,0x00);      
    for(cnt = 0; cnt <=  MAX_SIZE; cnt +=2)
    {
        /* Enable the ReStart Condition for Read operation */
        I2C_Restart_Structure(I2C0,conf.slave_address,I2C_READ_SA7);
        /* Receive the value of upper address(31:16) */
        recv_data = I2C_ReceiveData(I2C0,0);
        /* Set upper address and lower address*/
        if(MAX_SIZE - cnt < 0x01)
        {
            recv_data = (recv_data << 8) | I2C_ReceiveData(I2C0,1);
        }
        else
        {
            recv_data = (recv_data << 8) | I2C_ReceiveData(I2C0,0);
        }
        /* only the 11 significant bits should be used, and the 5 LSB bits of the LS byte are zero and should be ignored*/
        recv_data = (recv_data >>5);
        /* One of the ways to calculate the Temo value in C from the 11-bit Temp data*/
        result = recv_data *0.125;
        printf("Read Temp Hex= %x\t,Read Temp Dec = %d\t, Temp = %d\r\n",recv_data,recv_data,result);

       Delay_for(0x0000010);
    }
 } 


 void Delay_for(uint32_t delay)
  {
         int i =0;
                  for( i=0;i<delay;i++);
  }
