#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "adc.h"

/*
	stm32    YW01	
	PA1 ---- A0
	+5V ---- VCC
	GND ---- GND
*/
u16 yewei_baifen, yewei;

int main(void)
{
	OLED_Init();
	Adc_Init();
	
	while (1)
	{
		yewei = Get_Adc_Average(1, 40); // ADC采集40次，取平均值
		if (yewei >= 2440) //1100 根据检测值，换算成对应液位高度0%-100%
		{
			yewei_baifen = 100;
		}
		else if (yewei >= 2150)//1000
		{
			yewei_baifen = 90;
		}
		else if (yewei >= 1220)//700
		{
			yewei_baifen = 80;
		}
		else if (yewei >= 820)//540
		{
			yewei_baifen = 70;
		}
		else if (yewei >= 628)//400
		{
			yewei_baifen = 60;
		}
		else if (yewei >= 510)//370
		{
			yewei_baifen = 50;
		}
		else if (yewei >= 415)//330
		{
			yewei_baifen = 40;
		}
		else if (yewei >= 360)//307
		{
			yewei_baifen = 30;
		}
		else if (yewei >= 320)//260
		{
			yewei_baifen = 20;
		}
		else if (yewei >= 253)//194
		{
			yewei_baifen = 10;
		}
		else // 液位的百分比换算
		{
			yewei_baifen = 0;
		}
		OLED_ShowNum(1,1,yewei,5);// 显示测试结果
		OLED_ShowNum(2,1,yewei_baifen,5);// 显示转换结果
		Delay_ms(300);
	}
}
