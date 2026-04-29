#include "stm32f10x.h" // Device header
#include "Delay.h"
#include "OLED.h"
#include "HX711.h"

/*
	用330ML的可口可乐测了一下，显示实际重量340g左右
*/
int main(void)
{
	OLED_Init();	 // OLED初始化
	Init_HX711pin(); // HX711传感器初始化

	Get_Maopi(); // 称取初始化状态，此状态下可获得最开始的值
	Delay_ms(2000);
	Get_Maopi(); // 重新获取初始化状态

	while (1)
	{
		Get_Weight();//获取重量
		
		OLED_ShowNum(1, 1, Weight_Maopi, 5); // 显示毛皮重量
		OLED_ShowNum(2, 1, Weight_Shiwu, 5); // 显示实际重量
		Delay_ms(200);
	}
}
