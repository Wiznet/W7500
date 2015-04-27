#I2C and LM75 Temperature Sensor communication example
******************************************************************************
(C) COPYRIGHT 2015 WIZnet Co.,Ltd.

  * file    : I2C/I2C_Temperture_LM75A/readme.md 
  * author  : IOP Team
  * version : V1.0.0
  * date    : 1-May-2015
  * brief   :  Description of the I2C and LM75 Temperature Sensor communication example.
******************************************************************************
THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME. AS A RESULT, WIZNET SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
******************************************************************************

### Example Description

This example provides a description of how to use I2C to communicate with a
LM75 I2C temperature sensor is mounted on the evaluation board and used to get
instantaneous external temperature.

______________________________________________________________________________
### Directory contents

  - I2C/I2C_Temperture_LM75A/main.c                            					(Main program)
  - I2C/I2C_Temperture_LM75A/W7500x_it.c                       					(Interrupt Handlers)
  - I2C/I2C_Temperture_LM75A/W7500x_it.h                     				  	(Interrupt Handlers Header file)
  - I2C/I2C_Temperture_LM75A/W7500x_conf.h                     					(Library Configuration file)
  - I2C/I2C_Temperture_LM75A/MDK//W7500x_I2C_Temperture_LM75A.uvproj         	(Project file)
  - I2C/I2C_Temperture_LM75A/GCC/Makefile                      					(GCC Make file)
______________________________________________________________________________

### Hardware and Software environment 

    --W7500--        --LM75--
   |         |      |        |
   |     SDA |------| SDA    |
   |     SCL |------| SCL    |
   |         |      |        |
   |         |      |        |
    ---------       ---------



LM75 Pin Configuration
       -----
---SDA|1   8|VCC---
---SCL|2   7|A0 ---
---OS |3   6|A1 ---
---GND|4   5|A2 ---
       -----
LM75 Pin Description
-------------------------------------------------------------------------------
PIN | SYMBOL | DESCRIPTION
----|--------|------------------------------------------------------------------
 1  | SDA    | Digital I/O. I2C serial bi-directional data line. Open Drain
 2  | SCL    | Digital input. I2C serial clock input.
 3  | OS     | Overtemp Shutdown output. Open Drain.
 4  | GND    | Ground. To be connected to the system ground.
 5  | A2     | Digital input. User-defined address bit2.
 6  | A1     | Digital input. User-defined address bit1.
 7  | A0     | Digital input. User-defined address bit0.
 8  | VCC    | Power supply.
----|--------|------------------------------------------------------------------

LM75 register 
------------------------------------------------------------------------------------------
REG NAME | Addr   | R/W | RST Value |DESCRIPTION
---------|--------|-----|-----------|--------------------------------------------------
Temp     | 0x00   | R/W |   0x0000  |   Configuration Register.
         |        |     |           |   Contains a single 8-bit data byte. 
         |        |     |           |   To set the device operating condition.
         |        |     |           |   Default = 0.
---------|--------|-----|-----------|-------------------------------------------------------
Conf     | 0x01   | R   |    N/A    |   Temperature Register.
         |        |     |           |   Contains two 8-bit data bytes. 
         |        |     |           |   To store the measured Temp data.
---------|--------|-----|-----------|-------------------------------------------------------
Thyrs    | 0x02   | R/W |   0x5000  |   Over-temp Shutdown threshold Register.
         |        |     |           |   Contains two 8-bit data bytes. 
         |        |     |           |   To store the over-temp shut-down Tos limit.
         |        |     |           |   Default = 80 ��C.
---------|--------|-----|-----------|----------------------------------------------------
Tos      | 0x03   | R/W |   0x4B00  |   Hysteresis Register.
         |        |     |           |   Contains two 8-bit data bytes. 
         |        |     |           |   To store the hysteresis Thyst limit.
         |        |     |           |   Default = 75 ��C.
---------|--------|-----|-----------|--------------------------------------------------

LM75 Device Address
         --- --- --- --- --- --- --- 
        | 1 | 0 | 0 | 1 |A2 | A1| A0|
         --- --- --- --- --- --- --- 
                                  LSB

LM75 Temp register table
-----------------------------------------------|-----------------------------------------------
              Temp MS byte                     |                    Temp LS byte
-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|
 MSB |     |     |     |     |     |     | LSB | MSB |     |     |     |     |     |     | LSB |            
-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|
  B7 |  B6 |  B5 |  B4 |  B3 |  B2 |  B1 |  B0 |  B7 |  B6 |  B5 |  B4 |  B3 |  B2 |  B1 |  B0 |
-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|
                         Temp data(11bits)                       |        Not  Used            |            
-----------------------------------------------|----------------------------------------------- 
 MSB |                                                     | LSB |
-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|
 D10 |  D9 |  D8 |  D7 |  D6 |  D5 |  D4 |  D3 |  D2 |  D1 |  D0 |  X  |  X  |  X  |  X  |  X  |
-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|


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
 - Slave address send from W7500 to LM75
 - START enable
 - Confirm the Ack Receive
 - Send the data from W7500 to LM75
 - Restart enable
 - Confirm the Ack Receive
 - Receive the data
 - Transmit the Ack transmission
 - STOP enable


<h3><center>&copy; COPYRIGHT 2015 WIZnet Co.,Ltd.</center></h3>