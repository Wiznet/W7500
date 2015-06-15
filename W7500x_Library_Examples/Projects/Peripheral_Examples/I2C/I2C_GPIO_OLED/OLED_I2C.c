/************************************************************************************
*  Copyright (c), 2014, HelTec Automatic Technology co.,LTD.
*            All rights reserved.
*
* Http:    www.heltec.cn
* Email:   cn.heltec@gmail.com
* WebShop: heltec.taobao.com
*
* File name: OLED_I2C.c
* Project  : HelTec.uvprij
* Processor: STM32F103C8T6
* Compiler : MDK fo ARM
* 
* Author : 小林
* Version: 1.00
* Date   : 2014.4.8
* Email  : hello14blog@gmail.com
* Modification: none
* 
* Description:128*64点阵的OLED显示屏驱动文件，仅适用于惠特自动化(heltec.taobao.com)的SD1306驱动IIC通信方式显示屏
*
* Others: none;
*
* Function List:
*	1. void I2C_Configuration(void) -- 配置CPU的硬件I2C
* 2. void I2C_WriteByte(uint8_t addr,uint8_t data) -- 向寄存器地址写一个byte的数据
* 3. void WriteCmd(unsigned char I2C_Command) -- 写命令
* 4. void WriteDat(unsigned char I2C_Data) -- 写数据
* 5. void OLED_Init(void) -- OLED屏初始化
* 6. void OLED_SetPos(unsigned char x, unsigned char y) -- 设置起始点坐标
* 7. void OLED_Fill(unsigned char fill_Data) -- 全屏填充
* 8. void OLED_CLS(void) -- 清屏
* 9. void OLED_ON(void) -- 唤醒
* 10. void OLED_OFF(void) -- 睡眠
* 11. void OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize) -- 显示字符串(字体大小有6*8和8*16两种)
* 12. void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N) -- 显示中文(中文需要先取模，然后放到codetab.h中)
* 13. void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]) -- BMP图片
*
* History: none;
*
*************************************************************************************/

#include "OLED_I2C.h"
#include "codetab.h"

void startIIC(GPIO_TypeDef* GPIOx)
{
    digitalWrite(GPIOx, SCL,Bit_SET);
    digitalWrite(GPIOx, SDA,Bit_SET);
    digitalWrite(GPIOx, SDA,Bit_RESET);
    digitalWrite(GPIOx, SCL,Bit_RESET);
}

void stopIIC(GPIO_TypeDef* GPIOx)
{
    digitalWrite(GPIOx, SCL,Bit_RESET);
    digitalWrite(GPIOx, SDA,Bit_RESET);
    digitalWrite(GPIOx, SCL,Bit_SET);
    digitalWrite(GPIOx, SDA,Bit_SET);
}

void writeByte(GPIO_TypeDef* GPIOx,uint8_t val)
{
    unsigned char i;
	for(i=0;i<8;i++)
	{
		if((val << i) & 0x80){
			digitalWrite(GPIOx,SDA, Bit_SET);
		}else{
			digitalWrite(GPIOx,SDA, Bit_RESET);
		}
		digitalWrite(GPIOx,SCL, Bit_SET);
        delay_us(2);
		digitalWrite(GPIOx,SCL, Bit_RESET);
        delay_us(1);
		//    IIC_Byte<<=1;
	}
	digitalWrite(GPIOx,SDA, Bit_SET);
	digitalWrite(GPIOx,SCL, Bit_SET);
	delay_us(1);
	digitalWrite(GPIOx,SCL, Bit_RESET);
    delay_us(2);
}

void writecmd(GPIO_TypeDef* GPIOx,uint8_t cmd)
{
    startIIC(GPIOx);
    writeByte(GPIOx,0x78);
    writeByte(GPIOx,0x00);
    writeByte(GPIOx,cmd);
    stopIIC(GPIOx);
}
void writedat(GPIO_TypeDef* GPIOx,uint8_t dat)
{
    startIIC(GPIOx);
    writeByte(GPIOx,0x78);
    writeByte(GPIOx,0x40);
    writeByte(GPIOx,dat);
    stopIIC(GPIOx);
}

void OLED_Init(GPIO_TypeDef* GPIOx)
{
	delay_ms(10); //这里的延时很重要
	
	writecmd(GPIOx,0xAE); //display off
	writecmd(GPIOx,0x20);	//Set Memory Addressing Mode	
	writecmd(GPIOx,0x10);	//00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
	writecmd(GPIOx,0xb0);	//Set Page Start Address for Page Addressing Mode,0-7
	writecmd(GPIOx,0xc8);	//Set COM Output Scan Direction
	writecmd(GPIOx,0x00); //---set low column address
	writecmd(GPIOx,0x10); //---set high column address
	writecmd(GPIOx,0x40); //--set start line address
	writecmd(GPIOx,0x81); //--set contrast control register
	writecmd(GPIOx,0xff); //亮度调节 0x00~0xff
	writecmd(GPIOx,0xa1); //--set segment re-map 0 to 127
	writecmd(GPIOx,0xa6); //--set normal display
	writecmd(GPIOx,0xa8); //--set multiplex ratio(1 to 64)
	writecmd(GPIOx,0x3F); //
	writecmd(GPIOx,0xa4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	writecmd(GPIOx,0xd3); //-set display offset
	writecmd(GPIOx,0x00); //-not offset
	writecmd(GPIOx,0xd5); //--set display clock divide ratio/oscillator frequency
	writecmd(GPIOx,0xf0); //--set divide ratio
	writecmd(GPIOx,0xd9); //--set pre-charge period
	writecmd(GPIOx,0x22); //
	writecmd(GPIOx,0xda); //--set com pins hardware configuration
	writecmd(GPIOx,0x12);
	writecmd(GPIOx,0xdb); //--set vcomh
	writecmd(GPIOx,0x20); //0x20,0.77xVcc
	writecmd(GPIOx,0x8d); //--set DC-DC enable
	writecmd(GPIOx,0x14); //
	writecmd(GPIOx,0xaf); //--turn on oled panel
}

void OLED_SetPos(GPIO_TypeDef* GPIOx,unsigned char x, unsigned char y) //设置起始点坐标
{ 
	writecmd(GPIOx,0xb0+y);
	writecmd(GPIOx,((x&0xf0)>>4)|0x10);
	writecmd(GPIOx,(x&0x0f)|0x01);
}

void OLED_Fill(GPIO_TypeDef* GPIOx,unsigned char fill_Data)//全屏填充
{
	unsigned char m,n;
	for(m=0;m<8;m++)
	{
		writecmd(GPIOx,0xb0+m);		//page0-page1
		writecmd(GPIOx,0x00);		//low column start address
		writecmd(GPIOx,0x10);		//high column start address
		for(n=0;n<128;n++)
			{
				writedat(GPIOx,fill_Data);
			}
	}
}

void OLED_CLS(GPIO_TypeDef* GPIOx)//清屏
{
	OLED_Fill(GPIOx,0x00);
}

//--------------------------------------------------------------
// Prototype      : void OLED_ON(void)
// Calls          : 
// Parameters     : none
// Description    : 将OLED从休眠中唤醒
//--------------------------------------------------------------
void OLED_ON(GPIO_TypeDef* GPIOx)
{
	writecmd(GPIOx,0X8D);  //设置电荷泵
	writecmd(GPIOx,0X14);  //开启电荷泵
	writecmd(GPIOx,0XAF);  //OLED唤醒
}

//--------------------------------------------------------------
// Prototype      : void OLED_OFF(void)
// Calls          : 
// Parameters     : none
// Description    : 让OLED休眠 -- 休眠模式下,OLED功耗不到10uA
//--------------------------------------------------------------
void OLED_OFF(GPIO_TypeDef* GPIOx)
{
	writecmd(GPIOx,0X8D);  //设置电荷泵
	writecmd(GPIOx,0X10);  //关闭电荷泵
	writecmd(GPIOx,0XAE);  //OLED休眠
}

//--------------------------------------------------------------
// Prototype      : void OLED_ShowChar(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize)
// Calls          : 
// Parameters     : x,y -- 起始点坐标(x:0~127, y:0~7); ch[] -- 要显示的字符串; TextSize -- 字符大小(1:6*8 ; 2:8*16)
// Description    : 显示codetab.h中的ASCII字符,有6*8和8*16可选择
//--------------------------------------------------------------
void OLED_ShowStr(GPIO_TypeDef* GPIOx,unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize)
{
	unsigned char c = 0,i = 0,j = 0;
	switch(TextSize)
	{
		case 1:
		{
			while(ch[j] != '\0')
			{
				c = ch[j] - 32;
				if(x > 126)
				{
					x = 0;
					y++;
				}
				OLED_SetPos(GPIOx,x,y);
				for(i=0;i<6;i++)
					writedat(GPIOx,F6x8[c][i]);
				x += 6;
				j++;
			}
		}break;
		case 2:
		{
			while(ch[j] != '\0')
			{
				c = ch[j] - 32;
				if(x > 120)
				{
					x = 0;
					y++;
				}
				OLED_SetPos(GPIOx,x,y);
				for(i=0;i<8;i++)
					writedat(GPIOx,F8X16[c*16+i]);
				OLED_SetPos(GPIOx,x,y+1);
				for(i=0;i<8;i++)
					writedat(GPIOx,F8X16[c*16+i+8]);
				x += 8;
				j++;
			}
		}break;
	}
}

//--------------------------------------------------------------
// Prototype      : void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char N)
// Calls          : 
// Parameters     : x,y -- 起始点坐标(x:0~127, y:0~7); N:汉字在codetab.h中的索引
// Description    : 显示codetab.h中的汉字,16*16点阵
//--------------------------------------------------------------
void OLED_ShowCN(GPIO_TypeDef* GPIOx,unsigned char x, unsigned char y, unsigned char N)
{
	unsigned char wm=0;
	unsigned int  adder=32*N;
	OLED_SetPos(GPIOx,x , y);
	for(wm = 0;wm < 30;wm++)
	{
            writedat(GPIOx,WIZnet[adder]);
            adder += 1;
      
	}
/*	OLED_SetPos(GPIOx,x,y + 1);
	for(wm = 0;wm < 18;wm++)
	{
		writedat(GPIOx,WIZnet[adder]);
		adder += 1;
	}*/
    
}

//--------------------------------------------------------------
// Prototype      : void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);
// Calls          : 
// Parameters     : x0,y0 -- 起始点坐标(x0:0~127, y0:0~7); x1,y1 -- 起点对角线(结束点)的坐标(x1:1~128,y1:1~8)
// Description    : 显示BMP位图
//--------------------------------------------------------------
void OLED_DrawBMP(GPIO_TypeDef* GPIOx,unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[])
{
	unsigned int j=0;
	unsigned char x,y;

  if(y1%8==0)
		y = y1/8;
  else
		y = y1/8 + 1;
	for(y=y0;y<y1;y++)
	{
		OLED_SetPos(GPIOx,x0,y);
    for(x=x0;x<x1;x++)
		{
			writedat(GPIOx,BMP[j++]);
		}
	}
}

