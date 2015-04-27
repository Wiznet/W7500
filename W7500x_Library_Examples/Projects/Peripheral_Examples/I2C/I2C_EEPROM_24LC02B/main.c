/**
  ******************************************************************************
  * @file    I2C/I2C_EEPROM_24LC02B/main.c 
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
#define MAX_SIZE 9
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
UART_InitTypeDef UART_InitStructure;
I2C_ConfigStruct conf;
///                   memaddress,data0,data1 data2,data3,data4,data5,data6,data7
uint8_t Transmit_Data[MAX_SIZE]={0x00, 0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8};
uint8_t Recv_Data[MAX_SIZE];
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief   Main program
  * @param  None
  * @retval None
  */
int main()
{
    int i;

    /*System clock configuration*/
    SystemInit();
    /* UART0 and UART1 configuration*/
    UART_StructInit(&UART_InitStructure);
    /* Configure UART0 */
    UART_Init(UART1,&UART_InitStructure);
    printf("########  I2C EEPROM TEST  #########\r\n");

    /* I2C Init */

    /*  I2C confiugred as follow:
     *  - I2C master mode
     *  - I2C slave address : 0xA0
     *  - I2C Prescale : 0x61
     *     /If MCU clock is 20MHz and Prescale value is 0x61, SCL occurs 100KHz as clock.
     *  - I2C Timeout : 0xFFFF
     */
    conf.mode = I2C_Master;
    conf.slave_address = 0xA0;
    conf.master.prescale = 0x61;
    conf.master.timeout = 0xFFFF;
    /* Cofigure I2C0 */
    I2C_Init(I2C0, conf);

    /* EEPROM Write Test*/
    /* It can transmit up to 9data bytes to the EEPROM(24AA02) ( mem_address 1byte, data 8bytes )   */
    if( I2C_Burst_Write(I2C0,conf.slave_address,&Transmit_Data[0],9,1) == -1 )
        return -1; 
    /*It must be use the delay function between Write operation and Read operation */
    I2C_Delay(0x000F0000);
    /*I2C Core reset */
    I2C_Reset(I2C0);

    // EEPROM Read Test
    /* I2C Start */
    I2C_Start(I2C0,conf.slave_address,I2C_WRITE_SA7);
    /* The memory address of EEPROM send to EEPROM and it wait the ack signal */
    I2C_SendDataAck(I2C0,0x00);         
    /*Once the Slave address and memotu address are clocked in and 
     *acknowledged by the EEPROM, the W7500 must generate another start condition.*/
    I2C_Restart_Structure(I2C0,conf.slave_address,I2C_READ_SA7);
    /* EEPROM Read Test*/
    for(i=0;i<MAX_SIZE;i++)
    {
        if(i != MAX_SIZE-1)     Recv_Data[i] = I2C_ReceiveData(I2C0,0);
        else                    Recv_Data[i] = I2C_ReceiveData(I2C0,1);
    }

    for(i=0;i<MAX_SIZE-2;i+=2)
        printf("[%02d]:%02x,  [%02d]:%02x\r\n",i,Recv_Data[i],i+1,Recv_Data[i+1]);

    return 0;
}
