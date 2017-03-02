/*******************************************************************************************************************************************************
 * Copyright ¨Ï 2016 <WIZnet Co.,Ltd.> 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the ¡°Software¡±), 
 * to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED ¡°AS IS¡±, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*********************************************************************************************************************************************************/
/**
  ******************************************************************************
  * @file    Uart/Interrupt/main.c 
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
#include <stdio.h>
#include "W7500x_uart.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
UART_InitTypeDef UART_InitStructure;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/**
  * @brief   Main program
  * @param  None
  * @retval None
  *
*/

// For using this test code, W7500 must connect UART0 with UART1
// PA13(UTXD0) <----> PB03(URXD1), PA14(U_RXD0) <----> PB02(U_TXD1)
// UART2 is used for monitoring in this test code PB10(U_TXD2), PB11(U_RXD2)

int main()
{
//    uint32_t i;
  

    /*System clock configuration*/
	SystemInit();
//    *(volatile uint32_t *)(0x41001014) = 0x0060100; //clock setting 48MHz
    
    /* CLK OUT Set */
//    PAD_AFConfig(PAD_PA,GPIO_Pin_2, PAD_AF2); // PAD Config - CLKOUT used 3nd Function

    /* Configure UART2 */
    S_UART_Init(115200);

    /* Configure Uart2 Interrupt Enable*/
    S_UART_ITConfig((S_UART_CTRL_TXI|S_UART_CTRL_RXI),ENABLE);
    
    /* NVIC configuration */
    NVIC_EnableIRQ(UART2_IRQn);
    NVIC_ClearPendingIRQ(UART2_IRQn);
    
    while(1);  
}

