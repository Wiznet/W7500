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
  * @file    DualTimer/TimerRun/W7500x_it.c
  * @author  IOP Team
  * @version V1.0.0
  * @date    01-May-2015
  * @brief   This file contains the headers of the interrupt handlers.
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
#include "W7500x_it.h"
#include "W7500x_uart.h"
#include "common.h"

BUFFER_DECLARATION(u0rx);
BUFFER_DECLARATION(u0tx);
BUFFER_DECLARATION(u1rx);
BUFFER_DECLARATION(u1tx);


/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{}


/******************************************************************************/
/*                 W7500x Peripherals Interrupt Handlers                      */
/*    Add here the Interrupt Handler for the used peripherals                 */
/******************************************************************************/

/**
  * @brief  This function handles SSP0 Handler.
  * @param  None
  * @retval None
  */
void SSP0_Handler(void)
{}

/**
  * @brief  This function handles SSP1 Handler.
  * @param  None
  * @retval None
  */
void SSP1_Handler(void)
{}


/**
  * @brief  This function handles UART0 Handler.
  * @param  None
  * @retval None
  */
void UART0_Handler(void)
{
    if(UART_GetITStatus(UART0,UART_IT_FLAG_RXI))
    {
        if( IS_BUFFER_FULL(u0rx) ){
            BUFFER_CLEAR(u0rx);
            UART_ReceiveData(UART0);
        }
        else {
            BUFFER_IN(u0rx) = UART_ReceiveData(UART0);
            BUFFER_IN_MOVE(u0rx, 1);
        }
    }
	if(UART_GetITStatus(UART0, UART_IT_FLAG_TXI)) 
    {
		if(IS_BUFFER_EMPTY(u0tx)) {
			UART_ITConfig(UART0, UART_IT_FLAG_TXI, DISABLE);
		} else {
			UART_SendData(UART0, BUFFER_OUT(u1tx));
			BUFFER_OUT_MOVE(u0tx, 1);
            UART_ClearITPendingBit(UART0,UART_IT_FLAG_TXI);
		}
	}
}


/**
  * @brief  This function handles UART1 Handler.
  * @param  None
  * @retval None
  */
uint32_t u1rx_cnt = 0;
void UART1_Handler(void)
{
    if(UART_GetITStatus(UART1,UART_IT_FLAG_RXI))
    {
        if( IS_BUFFER_FULL(u1rx) ){
            BUFFER_CLEAR(u1rx);
            //UART_ReceiveData(UART1);
        }
        
        while(UART_GetFlagStatus(UART1, UART_FLAG_RXFE) != SET)
        {
            BUFFER_IN(u1rx) = UART_ReceiveData(UART1);
            BUFFER_IN_MOVE(u1rx, 1);
            u1rx_cnt++;
        }
    }

	if(UART_GetITStatus(UART1, UART_IT_FLAG_TXI)) 
    {
		if(IS_BUFFER_EMPTY(u1tx)) {
			UART_ITConfig(UART1, UART_IT_FLAG_TXI, DISABLE);
		} else {
			UART_SendData(UART1, BUFFER_OUT(u1tx));
			BUFFER_OUT_MOVE(u1tx, 1);
            UART_ClearITPendingBit(UART1,UART_IT_FLAG_TXI);
		}
	}
}


/**
  * @brief  This function handles UART2 Handler.
  * @param  None
  * @retval None
  */
void UART2_Handler(void)
{
    uint8_t ch;

    if( S_UART_GetITStatus(S_UART_INTSTATUS_RXI) != RESET ) {
            S_UART_ClearITPendingBit(S_UART_INTSTATUS_RXI);
            ch = S_UartGetc();
            S_UartPutc(ch);
        }    
}


/**
  * @brief  This function handles I2C0 Handler.
  * @param  None
  * @retval None
  */
void I2C0_Handler(void)
{}


/**
  * @brief  This function handles I2C1 Handler.
  * @param  None
  * @retval None
  */
void I2C1_Handler(void)
{}


/**
  * @brief  This function handles PORT0 Handler.
  * @param  None
  * @retval None
  */
void PORT0_Handler(void)
{}


/**
  * @brief  This function handles PORT1 Handler.
  * @param  None
  * @retval None
  */
void PORT1_Handler(void)
{}


/**
  * @brief  This function handles PORT2 Handler.
  * @param  None
  * @retval None
  */
void PORT2_Handler(void)
{}


/**
  * @brief  This function handles PORT3 Handler.
  * @param  None
  * @retval None
  */
void PORT3_Handler(void)
{}


/**
  * @brief  This function handles DMA Handler.
  * @param  None
  * @retval None
  */
void DMA_Handler(void)
{}

/**
  * @brief  This function handles DUALTIMER0 Handler.
  * @param  None
  * @retval None
  */
void DUALTIMER0_Handler(void)
{}


/**
  * @brief  This function handles DUALTIMER1 Handler.
  * @param  None
  * @retval None
  */
void DUALTIMER1_Handler(void)
{}


/**
  * @brief  This function handles PWM0 Handler.
  * @param  None
  * @retval None
  */
void PWM0_Handler(void)
{}

/**
  * @brief  This function handles PWM1 Handler.
  * @param  None
  * @retval None
  */
void PWM1_Handler(void)
{}

/**
  * @brief  This function handles PWM2 Handler.
  * @param  None
  * @retval None
  */
void PWM2_Handler(void)
{}

/**
  * @brief  This function handles PWM3 Handler.
  * @param  None
  * @retval None
  */
void PWM3_Handler(void)
{}

/**
  * @brief  This function handles PWM4 Handler.
  * @param  None
  * @retval None
  */
void PWM4_Handler(void)
{}

/**
  * @brief  This function handles PWM5 Handler.
  * @param  None
  * @retval None
  */
void PWM5_Handler(void)
{}

/**
  * @brief  This function handles PWM6 Handler.
  * @param  None
  * @retval None
  */
void PWM6_Handler(void)
{}

/**
  * @brief  This function handles PWM7 Handler.
  * @param  None
  * @retval None
  */
void PWM7_Handler(void)
{}

/**
  * @brief  This function handles ADC Handler.
  * @param  None
  * @retval None
  */
void ADC_Handler(void)
{}

/**
  * @brief  This function handles WATOE Handler.
  * @param  None
  * @retval None
  */
void WZTOE_Handler(void)
{}

/**
  * @brief  This function handles EXTI Handler.
  * @param  None
  * @retval None
  */
void EXTI_Handler(void)
{}



/******************* (C) COPYRIGHT 2015 WIZnet Co.,Ltd *****END OF FILE****/
