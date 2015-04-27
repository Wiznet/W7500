#I2C Read/Write example
******************************************************************************
(C) COPYRIGHT 2015 WIZnet Co.,Ltd.

  * file    : I2C/I2C_Init/readme.md 
  * author  : IOP Team
  * version : V1.0.0
  * date    : 1-May-2015
  * brief   : Description of the I2C Data Read/Write example.
******************************************************************************
THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME. AS A RESULT, WIZNET SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
******************************************************************************

### Example Description

This example provides a description of how to use a Read/Write operation.
This example provides the elementary steps to control the following modules and
use them in an application:

______________________________________________________________________________
### Directory contents

  - I2C/I2C_Init/main.c                            (Main program)
  - I2C/I2C_Init/W7500x_it.c                       (Interrupt Handlers)
  - I2C/I2C_Init/W7500x_it.h                       (Interrupt Handlers Header file)
  - I2C/I2C_Init/W7500x_conf.h                     (Library Configuration file)
  - I2C/I2C_Init/MDK/W7500x_I2C_Init.uvproj        (Project file)
  - I2C/I2C_Init/GCC/Makefile                      (GCC Make file)
______________________________________________________________________________

### Hardware and Software environment 


    --W7500--        ---slave--
   |         |      |          |
   |     SDA |------| SDA      |
   |     SCL |------| SCL      |
   |         |      |          |
   |         |      |          |
    ---------       -----------


______________________________________________________________________________

### How to use it ? 
In order to make the program work, you must do the following :

 - Open your preferred toolchain.
 - Rebuild all files and load your image into target memory.
 - Run the example.
 - WIZwiki W7500 where the Flash memory density ranges 128Kbytes.
 - If you have any questions, please use the forum site.
   - "http://wizwiki.net/forum/"

______________________________________________________________________________

### Flow Chart
 - Master Init
 - Device address send from W7500 to EEPROM
 - START enable
 - Confirm the Ack Receive
 - Slave address send from W7500 to EEPROM
 - Confirm the Ack Receive
 - Send the data from W7500 to EEPROM
 - Restart enable
 - Confirm the Ack Receive
 - Receive the data
 - Transmit the Ack transmission
 - STOP enable

<h3><center>&copy; COPYRIGHT 2015 WIZnet Co.,Ltd.</center></h3>
