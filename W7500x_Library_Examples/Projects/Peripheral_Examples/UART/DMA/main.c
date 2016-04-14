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
  * @file    Uart/DMA/main.c 
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
#include "W7500x_dma.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define TxBufferSize1   (countof(TxBuffer1) - 1)

/* Private macro -------------------------------------------------------------*/
#define countof(a)   (sizeof(a) / sizeof(*(a)))

/* Private variables ---------------------------------------------------------*/
UART_InitTypeDef UART_InitStructure;
uint8_t TxBuffer1[] = "\r\nUART DMA TxBuffer -> UART0 Data Register success!!";
uint32_t i = 0;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/**
  * @brief   Main program
  * @param  None
  * @retval None
  *
*/
int main()
{
    unsigned int current_state;
    
    //    *(volatile uint32_t *)(0x41001014) = 0x0060100; //clock setting 48MHz
    
    /*System clock configuration*/
	SystemInit();
    
    /* CLK OUT Set */
    //PAD_AFConfig(PAD_PA,GPIO_Pin_2, PAD_AF2); // PAD Config - CLKOUT used 3nd Function

    /*using debugging*/
    //S_UART_Init(115200);
    
    /* UART0 and UART1 configuration*/
    UART_StructInit(&UART_InitStructure);
    
    /* Configure UART0 */
    UART_Init(UART0,&UART_InitStructure);
    /* Configure Uart0 Interrupt Enable*/
    UART_ITConfig(UART0, (UART_IT_FLAG_TXI|UART_IT_FLAG_RXI),ENABLE);    
    /* NVIC configuration */
    NVIC_ClearPendingIRQ(UART0_IRQn);
    NVIC_EnableIRQ(UART0_IRQn);
    
    /* Configure UART1 */    
    UART_Init(UART1,&UART_InitStructure);
    /* Configure Uart1 Interrupt Enable*/
    UART_ITConfig(UART1,(UART_IT_FLAG_TXI|UART_IT_FLAG_RXI),ENABLE);
     /* NVIC configuration */
    NVIC_ClearPendingIRQ(UART1_IRQn);
    NVIC_EnableIRQ(UART1_IRQn);
     
    /* Configure DMA */
    dma_data_struct_init();
    dma_init();
    
    /* UART0 DMA Channel (triggered by UART0 Tx event) Config */
    DMA ->CHNL_ENABLE_SET = (1<<DMA_UART0); // Enable DMA Channel UART0
    
    dma_m2p_copy (DMA_UART0, (uint32_t)TxBuffer1, 0x4000C000, 0, 32);
    UART_DMA_Config(UART0, (UART_DMAControl_TXDMAE)); //UART DMA cmd enable signal for new channel
    do { /* Wait until PL230 DMA controller return to idle state */
        current_state = ((DMA->DMA_STATUS >> 4)  & 0xF);
    } while (current_state!=0);
    while(UART_GetFlagStatus(UART0, UART_FLAG_BUSY)); //Wait until UART return to Transmit FIFO empty

    dma_m2p_copy (DMA_UART0, (uint32_t)TxBuffer1+32, 0x4000C000, 0, 20);
    DMA ->CHNL_ENABLE_CLR = (1<<DMA_UART0);
    DMA ->CHNL_ENABLE_SET = (1<<DMA_UART0); //DMA cmd enable signal for next data
    do { /* Wait until PL230 DMA controller return to idle state */
        current_state = (DMA->DMA_STATUS >> 4)  & 0xF;
    } while (current_state!=0);
    while(UART_GetFlagStatus(UART0, UART_FLAG_BUSY)); //Wait until UART return to Transmit FIFO empty

    UART_DMA_Config(UART0, (UART_DMAControl_TXDMAE)); //UART DMA cmd clear signal

    while (1)
    {
    }  
}
