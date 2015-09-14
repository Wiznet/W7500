/**
  ******************************************************************************
  * @file    GPIO/Blink_LED/main.c 
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
#include "W7500x_gpio.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
GPIO_InitTypeDef GPIO_InitDef;

/* Private function prototypes -----------------------------------------------*/
void delay_ms(__IO uint32_t nCount);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main Function
  */
int main()
{	
    /* Set Systme init */
    SystemInit();
		
    /* GPIO LED1 & LED2 Set */
    GPIO_InitDef.GPIO_Pin = ( GPIO_Pin_1 | GPIO_Pin_2) ; // Set to Pin_1 (LED1) & Pin_2 (LED2)
    GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT; // Set to Mode Output
    GPIO_Init(GPIOA, &GPIO_InitDef);
    PAD_AFConfig(PAD_PA,(GPIO_Pin_1|GPIO_Pin_2), PAD_AF1); // PAD Config - LED used 2nd Function
	
	
    GPIO_SetBits(GPIOA, ( GPIO_Pin_1 | GPIO_Pin_2) ); // LED1 & LED2 Off
    
    while(1)
    {
        delay_ms(500);
        // LED1 OFF, LED2 OFF
        GPIO_SetBits(GPIOA, ( GPIO_Pin_1 | GPIO_Pin_2) ); // LED1 & LED2 Off

        delay_ms(500);
        GPIO_WriteBit(GPIOA, GPIO_Pin_1, Bit_RESET);

        delay_ms(500);
        GPIO_WriteBit(GPIOA, GPIO_Pin_2, Bit_RESET);
    }
}

/**
  * @brief  Delay Function
  */
void delay_ms(__IO uint32_t nCount)
{
    volatile uint32_t delay = nCount * 2500; // approximate loops per ms at 24 MHz, Debug config
    for(; delay != 0; delay--)
        __NOP();
}

