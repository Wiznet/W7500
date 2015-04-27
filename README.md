#Library and Periphral Example

##Overview
W7500 provides the CMSIS, driver and Peripheral Example.
The W7500 Standard Peripherals library provides a rich set of examples covering the main features of each peripheral. All the examples are independent from the Wizwiki-w7500. Only source files are provided for each example and user can tailor the provided project template to run the selected example with his preferred toolchain. 

  - Directory Structure
  
![Fig.directory_structure](http://wizwiki.net/wiki/lib/exe/fetch.php?media=products:w7500:directory_structure.png "Fig.directory_structure")

  - Libraies
    - CMSIS :CMSIS Library
    - W7500x_stdPeriph_Driver
		- Each peripheral has a source code file W7500x_XXX.c and a header file W7500x_XXX.h. The W7500x_XXX.c file contains all the firmware functions required to use the XXX peripheral.
		- A single memory mapping file, W7500x.h, is supplied for all peripherals. It contains all the register declarations and bit definition. This is the only file that needs to be included in the user application to interface with the library.
			
- Projects
	- peripheral_Examples
		- The W7500 standard Peripherals library provides a rich set of examples covering the main features of eash peripheral. 

##Peripheral description and examples
- [Peripherals](http://wizwiki.net/wiki/doku.php?id=products:w7500:peripherals)
