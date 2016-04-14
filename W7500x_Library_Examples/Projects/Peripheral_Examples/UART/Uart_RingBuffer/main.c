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
#include <string.h>
#include "W7500x_uart.h"
#include "common.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define RET_OK		0
#define RET_NOK		-1
#define RET_TIMEOUT -2

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
// This variables are initialized at W7500x_it.c
UART_InitTypeDef UART_InitStructure;

BUFFER_DEFINITION(u0rx, 1024);	// To adjust the size
BUFFER_DEFINITION(u0tx, 1024);	// To adjust the size
BUFFER_DEFINITION(u1rx, 1024);	// To adjust the size
BUFFER_DEFINITION(u1tx, 1024);	// To adjust the size

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

int32_t uart_putc(uint8_t uartNum, uint8_t ch);
int32_t uart_puts(uint8_t uartNum, uint8_t* buf, uint8_t reqSize);
int32_t uart_getc(uint8_t uartNum);
int32_t uart_getc_nonblk(uint8_t uartNum);
int32_t uart_gets(uint8_t uartNum, uint8_t* buf, uint8_t reqSize);

extern uint32_t u1rx_cnt;
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
    int32_t ch;

    /*System clock configuration*/
	SystemInit();
    
    /* CLK OUT Set */
//    PAD_AFConfig(PAD_PA,GPIO_Pin_2, PAD_AF2); // PAD Config - CLKOUT used 3nd Function

    /*using debugging*/
    S_UART_Init(115200);
    UART_StructInit(&UART_InitStructure);

    //UART_Init(UART0,&UART_InitStructure);
    UART_Init(UART1,&UART_InitStructure);

    UART_ITConfig(UART0,(UART_IT_FLAG_RXI),ENABLE);
    UART_ITConfig(UART1,(UART_IT_FLAG_RXI),ENABLE);

        //UART_FIFO_Enable(UART0,0,4);
    UART_FIFO_Enable(UART1,0,0);

    
    //S_UART_ITConfig(S_UART_CTRL_RXI,ENABLE);

    /* NVIC configuration */
    NVIC_ClearPendingIRQ(UART0_IRQn);
    NVIC_EnableIRQ(UART0_IRQn);

    NVIC_ClearPendingIRQ(UART1_IRQn);
    NVIC_EnableIRQ(UART1_IRQn);
    
    while(1)
    {
        ch = uart_getc(1);
        uart_putc(1,(uint8_t)ch);
        //printf("u1rx_cnt %d\r\n",u1rx_cnt);
    }
  
}


int32_t uart_putc(uint8_t uartNum, uint8_t ch)
{
    if(uartNum == 0)
    {
        if(IS_BUFFER_FULL(u0tx))
        {
            BUFFER_CLEAR(u0tx);
            return RET_NOK;
        }
        else
        {
            BUFFER_IN(u0tx) = ch;
            BUFFER_IN_MOVE(u0tx, 1);
            UART_ITConfig(UART0,(UART_IT_FLAG_TXI),ENABLE);
        }
    }
    else if(uartNum == 1)
    {
        if(IS_BUFFER_FULL(u1tx))
        {
            BUFFER_CLEAR(u1tx);
            return RET_NOK;
        }
        else
        {
            UartPutc(UART1,ch);
            //BUFFER_IN(u1tx) = ch;
            //BUFFER_IN_MOVE(u1tx, 1);
            //UART_ITConfig(UART1,(UART_IT_FLAG_TXI),ENABLE);
        }
    }

    return RET_OK;
}

int32_t uart_puts(uint8_t uartNum, uint8_t* buf, uint8_t reqSize)
{
    uint16_t lentot = 0;

    while(*buf != '\0' && lentot < reqSize)
    {
        uart_putc(uartNum, *buf);
        buf++;
        lentot++;
    }

    return lentot;
}

int32_t uart_getc(uint8_t uartNum)
{
    int32_t ch;

    if(uartNum == 0)
    {
        while(IS_BUFFER_EMPTY(u0rx));
        ch = (int32_t)BUFFER_OUT(u0rx);
        BUFFER_OUT_MOVE(u0rx, 1);
    }
    else if(uartNum == 1)
    {
        while( IS_BUFFER_EMPTY(u1rx) );
        ch = (int32_t)BUFFER_OUT(u1rx);
        BUFFER_OUT_MOVE(u1rx, 1);
    }
    else    return RET_NOK;

    return ch;
}

int32_t uart_getc_nonblk(uint8_t uartNum)
{
    int32_t ch;

    if(uartNum == 0)
    {
        if(IS_BUFFER_EMPTY(u0rx)) return RET_NOK;
        ch = (int32_t)BUFFER_OUT(u0rx);
        BUFFER_OUT_MOVE(u0rx,1);
    }
    else if(uartNum == 1)
    {
        if(IS_BUFFER_EMPTY(u1rx)) return RET_NOK;
        ch = (int32_t)BUFFER_OUT(u1rx);
        BUFFER_OUT_MOVE(u1rx,1);
    }
    else    return RET_NOK;

    return ch;
}

int32_t uart_gets(uint8_t uartNum, uint8_t* buf, uint8_t reqSize)
{
    uint16_t lentot = 0, len1st = 0;

    if(uartNum == 0)
    {
        lentot = reqSize = MIN(BUFFER_USED_SIZE(u0rx), reqSize);
		if(IS_BUFFER_OUT_SEPARATED(u0rx) && (len1st = BUFFER_OUT_1ST_SIZE(u0rx)) < reqSize) {
			memcpy(buf, &BUFFER_OUT(u0rx), len1st);
			BUFFER_OUT_MOVE(u0rx, len1st);
			reqSize -= len1st;
		}
        memcpy(buf+len1st, &BUFFER_OUT(u0rx), reqSize);
        BUFFER_OUT_MOVE(u0rx,reqSize);
    }
    else if(uartNum == 1)
    {
        lentot = reqSize = MIN(BUFFER_USED_SIZE(u1rx), reqSize);
		if(IS_BUFFER_OUT_SEPARATED(u1rx) && (len1st = BUFFER_OUT_1ST_SIZE(u1rx)) < reqSize) {
			memcpy(buf, &BUFFER_OUT(u1rx), len1st);
			BUFFER_OUT_MOVE(u1rx, len1st);
			reqSize -= len1st;
		}
        memcpy(buf+len1st, &BUFFER_OUT(u1rx), reqSize);
        BUFFER_OUT_MOVE(u1rx,reqSize);
    }
    else    return RET_NOK;

    return lentot;
}

