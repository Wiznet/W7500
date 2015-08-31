#GPIO Blink_LED example
******************************************************************************
(C) COPYRIGHT 2015 WIZnet

  * file    : GPIO/Blink_LED(WIZwiki-W7500ECO)/readme.md
  * author  : IOP Team
  * version : V1.0.0
  * date    : 1-May-2015
  * brief   : Description of the GPIO Blink_LED example.

******************************************************************************

THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME. AS A RESULT, WIZNET SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.

******************************************************************************

### Example Description

GPIO ports are connected on APB2 bus, using UB_MASKED and LB_MASKED registers 
2 cycles are required to set a pin and another cycle to reset it. So GPIO pins
can toggle at AHB clock divided by 4.

This example describes how to use UB_MASKED and LB_MASKED
(Port Bit GPIO_SetBits/GPIO_ResetBits Register)

PA_01, PA_02(configured in output pushpull mode) toggles in a forever 
loop:
 - Set Pin_1 and Pin_2 by setting corresponding bits 
   in GPIO_SetBits function.
 - Reset Pin_1 and Pin_2 by setting corresponding bits 
   in GPIO_WriteBit function.

______________________________________________________________________________

### Directory contents

  - GPIO/LED_Blink(WIZwiki-W7500ECO)/main.c                                                   (Main program)
  - GPIO/LED_Blink(WIZwiki-W7500ECO)/MDK/W7500x_GPIO_Blink_LED(WIZwiki-W7500ECO).uvproj       (Project file)
______________________________________________________________________________

### Hardware and Software environment 

  - This example has been tested with WIZnet WIZwiki W7500 platform.
  - To select the WIZnet WIZwiki platform used to run the example.

  - WIZwiki W7500ECO Set-up 
    - Use LED1 connected to PA_01 pin
    - Use LED2 connected to PA_02 pin
    - In order to use the LED to be changed from PAD_AF0 to PAD_AF1.
______________________________________________________________________________

### How to use it ?

In order to make the program work, you must do the following :

 - Open your preferred toolchain.
 - Rebuild all files and load your image into target memory.
 - Run the example.
 - WIZwiki W7500 where the Flash memory density ranges 128Kbytes.
 - If you have any questions, please use the forum site.
   - "http://wizwiki.net/forum/"

<h3><center>&copy; COPYRIGHT 2015 WIZnet Co.,Ltd.</center></h3>
