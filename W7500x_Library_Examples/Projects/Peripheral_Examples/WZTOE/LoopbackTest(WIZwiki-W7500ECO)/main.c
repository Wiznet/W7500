/**
  ******************************************************************************
  * @file    WZTOE/Loopback/main.c 
  * @author  IOP Team
  * @version V1.0.1
  * @date    19-May-2015
  * @brief   Main program body
  ******************************************************************************
  * @attention
  * @par Revision history
  *    <2015/05/19> V1.0.1 by justinKim
  *      1. Print Address %.3d -> %d 
  *    <2015/05/01> 1st Release
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
#include "W7500x_gpio.h"
#include "W7500x_uart.h"
#include "W7500x_crg.h"
#include "W7500x_wztoe.h"
#include "W7500x_miim.h"
#include "mmc_sd.h"
#include "loopback.h"
/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define __DEF_USED_MDIO__ 
#define __DEF_USED_IC101AG__ //for W7500 Test main Board V001

/* Private function prototypes -----------------------------------------------*/
void delay(__IO uint32_t milliseconds); //Notice: used ioLibray
void TimingDelay_Decrement(void);

/* Private variables ---------------------------------------------------------*/
static __IO uint32_t TimingDelay;
uint8_t test_buf[2048];

/**
  * @brief   Main program
  * @param  None
  * @retval None
  */
int main()
{
    //uint8_t tx_size[8] = { 2, 2, 2, 2, 2, 2, 2, 2 };
    //uint8_t rx_size[8] = { 2, 2, 2, 2, 2, 2, 2, 2 };
    uint8_t mac_addr[6] = {0x00, 0x08, 0xDC, 0x01, 0x02, 0x03}; 
    uint8_t src_addr[4] = {192, 168,  77,  9};
    uint8_t gw_addr[4]  = {192, 168,  77,  1};
    uint8_t sub_addr[4] = {255, 255, 255,  0};		
    //uint8_t dns_server[4] = {8, 8, 8, 8};           // for Example domain name server
    uint8_t tmp[8], ret, cid[16];
    int i;
    GPIO_InitTypeDef GPIO_InitDef;  


    /* External Clock */
    CRG_PLL_InputFrequencySelect(CRG_OCLK);

    /* Clock */
     *(volatile uint32_t *)(0x41001014) = 0x000C0200; // 48MHz
    //*(volatile uint32_t *)(0x41001014) = 0x00050200; // 20MHz, Default
    //*(volatile uint32_t *)(0x41001014) = 0x00040200; // 16MHz
   
    
    /* Set Systme init */
    SystemInit();

    /* UART2 Init */
    S_UART_Init(115200);

    /* SysTick_Config */
    SysTick_Config((GetSystemClock()/1000));

    /* Set WZ_100US Register */
    printf(" GetSystemClock : %d (Hz) \r\n", GetSystemClock());  
    setTIC100US((GetSystemClock()/10000));
    printf(" val: %X, getTIC100US: %X, (%X) \r\n", GetSystemClock(), getTIC100US(), *(uint32_t *)WZTOE_TIC100US);        


#ifdef __DEF_USED_IC101AG__ //For using IC+101AG
    *(volatile uint32_t *)(0x41003068) = 0x64; //TXD0 - set PAD strengh and pull-up
    *(volatile uint32_t *)(0x4100306C) = 0x64; //TXD1 - set PAD strengh and pull-up
    *(volatile uint32_t *)(0x41003070) = 0x64; //TXD2 - set PAD strengh and pull-up
    *(volatile uint32_t *)(0x41003074) = 0x64; //TXD3 - set PAD strengh and pull-up
    *(volatile uint32_t *)(0x41003050) = 0x64; //TXE  - set PAD strengh and pull-up
#endif	
    printf("PHY is linked. \r\n"); 
#ifdef __DEF_USED_MDIO__ 
    /* mdio Init */
    mdio_init(GPIOB, MDC, MDIO );
    /* PHY Link Check via gpio mdio */
    while( link() == 0x0 )
    {
        printf(".");  
        delay(500);
    }
    printf("PHY is linked. \r\n");  
#else
    delay(1000);
    delay(1000);
#endif
    
    GPIO_InitDef.GPIO_Pin = (GPIO_Pin_1 | GPIO_Pin_2);
    GPIO_InitDef.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_Init(GPIOA, &GPIO_InitDef);
    PAD_AFConfig(PAD_PA, (GPIO_Pin_1 | GPIO_Pin_2), PAD_AF1);  

    for(i=0; i<4; i++)
    {
        // LED ON
        GPIO_ResetBits(GPIOA, (GPIO_Pin_1 | GPIO_Pin_2)) ;
        delay(200);	
        // LED OFF
        GPIO_SetBits(GPIOA, (GPIO_Pin_1 | GPIO_Pin_2)) ;        
        delay(200);		
    }

    printf("[DEBUG] SD Card	Test\r\n");
    bsp_sd_gpio_init();
    ret = SD_Init();

    switch(SD_Type)
    {
        case SD_TYPE_MMC: printf("[DEBUG] init ret : %d , SD Card Type : MMC\r\n", ret); 	break;
        case SD_TYPE_V1: printf("[DEBUG] init ret : %d , SD Card Type : SD\r\n", ret); 	break;
        case SD_TYPE_V2: printf("[DEBUG] init ret : %d , SD Card Type : SD2\r\n", ret); 	break;
        case SD_TYPE_V2HC: printf("[DEBUG] init ret : %d , SD Card Type : SDHC\r\n", ret); 	break;
        default: printf("[DEBUG] init ret : %d , SD Card Type : %d\r\n", ret, SD_Type); 	break;
    }

    memset(&cid[0], 0x00, 16);
    ret = SD_GetCID(cid);
    if( (cid[0]==0x00) && (cid[1]==0x00) && (cid[2]==0x00) && (cid[3]==0x00) &&
          (cid[4]==0x00) && (cid[5]==0x00) && (cid[6]==0x00) && (cid[7]==0x00) &&
            (cid[8]==0x00) && (cid[9]==0x00) && (cid[10]==0x00) && (cid[11]==0x00) &&
            (cid[12]==0x00) && (cid[13]==0x00) && (cid[14]==0x00) && (cid[15]==0x00)
    )
    {
        // Turn on LED 1
        printf("SD Test Fail!!\r\n");
        GPIO_ResetBits(GPIOA, GPIO_Pin_1);
    }
    else
    {
        // Turn on LED 1 & LED 2
        printf("SD Test O.K!!!r\n");
        GPIO_ResetBits(GPIOA, (GPIO_Pin_1|GPIO_Pin_2) );
    }
    //printf("[DEBUG] state : %d\r\n", state);
    printf("[DEBUG] CID / MID : 0x%.2X\r\n", cid[0]);
    printf("[DEBUG] CID / OID : %c%c\r\n", cid[1], cid[2]);
    printf("[DEBUG] CID / PNM : %c%c%c%c%c\r\n", cid[3], cid[4], cid[5], cid[6], cid[7]);
    
    
    /* Network Configuration */
    setSHAR(mac_addr);
    getSHAR(tmp);
    printf(" MAC ADDRESS : %.2X:%.2X:%.2X:%.2X:%.2X:%.2X\r\n",tmp[0],tmp[1],tmp[2],tmp[3],tmp[4],tmp[5]); 
    
    setSIPR(src_addr);
    getSIPR(tmp);
    printf("IP ADDRESS : %d.%d.%d.%d\r\n",tmp[0],tmp[1],tmp[2],tmp[3]); 
    
    setGAR(gw_addr);
    getGAR(tmp);
    printf("GW ADDRESS : %d.%d.%d.%d\r\n",tmp[0],tmp[1],tmp[2],tmp[3]); 

    setSUBR(sub_addr);
    getSUBR(tmp);
    printf("SN MASK: %d.%d.%d.%d\r\n",tmp[0],tmp[1],tmp[2],tmp[3]); 

    while(1)
    {
        loopback_tcps(0, test_buf, 5000);
    }

}

/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in milliseconds.
  * @retval None
  */
void delay(__IO uint32_t milliseconds)
{
  TimingDelay = milliseconds;

  while(TimingDelay != 0);
}

/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}

