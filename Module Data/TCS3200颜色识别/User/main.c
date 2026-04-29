/*
	TCS3200      STM32
	VCC -------- 3V3
	GND -------- GND
	S0  -------- 直接接GND
	S1  -------- 直接接3V3 输出频率定标为2%
	S2  -------- PB8
	S3  -------- PB9
	LED -------- 直接接3V3 点亮四个LED灯
	OUT -------- PA0
*/
#include "stm32f10x.h" // Device header
#include "Delay.h"
#include "OLED.h"
#include "TCS3200.h"
#include "Timer.h"

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	OLED_Init();

	TCS3200_Init();
	TIM3_Int_Init(9999, 719); // 100ms
	TIM2_Cap_Init();

	Delay_ms(5000);

	RGB_Scale[0] = 255.0 / cnt[0];//红色光比例因子
	RGB_Scale[1] = 255.0 / cnt[1];//绿色光比例因子
	RGB_Scale[2] = 255.0 / cnt[2];//蓝色光比例因子
	OLED_ShowString(1,1,"Init");
	OLED_ShowString(2,1,"R:");
	OLED_ShowString(3,1,"G:");
	OLED_ShowString(4,1,"B:");
	OLED_ShowNum(2, 4, (int)(cnt[0] * RGB_Scale[0]), 3);////红、绿、蓝三色光分别对应的100ms内TCS3200输出脉冲数乘以相应的比例因子就是RGB标准值
	OLED_ShowNum(3, 4, (int)(cnt[1] * RGB_Scale[1]), 3);
	OLED_ShowNum(4, 4, (int)(cnt[2] * RGB_Scale[2]), 3);
	while (1)
	{
		flag = 0;
		count = 0;
		Delay_ms(2000);
		OLED_ShowNum(2, 4, (int)(cnt[0] * RGB_Scale[0]), 3);
		OLED_ShowNum(3, 4, (int)(cnt[1] * RGB_Scale[1]), 3);
		OLED_ShowNum(4, 4, (int)(cnt[2] * RGB_Scale[2]), 3);
	}
}
