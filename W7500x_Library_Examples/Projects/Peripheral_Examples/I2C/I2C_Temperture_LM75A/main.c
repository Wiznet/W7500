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
#define I2C_Debug
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
UART_InitTypeDef UART_InitStructure;
I2C_ConfigStruct conf;
/* Private function prototypes -----------------------------------------------*/
void delay_us(int us);
void delay_ms(int count);
/* Private functions ---------------------------------------------------------*/
/**
  * @brief   Main program
  * @param  None
  * @retval None
  */

int main()
{
    float result = 0;
    uint8_t recv_data[2] ={0,};
    uint8_t register_address = LM75_REG_TEMP;
    
    

    /*System clock configuration*/
    SystemInit();
//    *(volatile uint32_t *)(0x41001014) = 0x0060100; //clock setting 48MHz
    
    /* CLK OUT Set */
//    PAD_AFConfig(PAD_PA,GPIO_Pin_2, PAD_AF2); // PAD Config - CLKOUT used 3nd Function

    /* UART0 and UART1 configuration*/
    UART_StructInit(&UART_InitStructure);
    /* Configure UART0 */
    UART_Init(UART1,&UART_InitStructure);
    printf("########  I2C LM75 Temperature TEST  #########\r\n");
    
    /* Cofigure I2C0 */
    conf.scl = I2C_PA_9;
    conf.sda = I2C_PA_10;
    I2C_Init(&conf);
    while(1)
    {
        /* Temperature Read Test*/
        /*Send LM75 slave address */
        I2C_Write(&conf, LM75_7bitSlaveAddress, &register_address, 0);
        delay_us(10);
        
        /*Read data*/
        I2C_Read(&conf, LM75_7bitSlaveAddress, &recv_data[0], 2);
        
        result = ((recv_data[0] << 8) | recv_data[1]) >> 5;
        result = result * 0.125;
        
        printf("Temperature : %.2f \r\n", result);
        
        delay_ms(2000);
    }
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



