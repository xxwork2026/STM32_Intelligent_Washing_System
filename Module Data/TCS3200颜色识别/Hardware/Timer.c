#include "stm32f10x.h" // Device header
#include "Timer.h"
#include "TCS3200.h"

/**
  * @brief  TIM3中断初始化配置
  * @param  arr-重装值 psc-预分频值
  * @retval 无
  */
void TIM3_Int_Init(u16 arr, u16 psc)
{
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
  
   TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

   TIM_TimeBaseStructure.TIM_Period = arr;
   TIM_TimeBaseStructure.TIM_Prescaler = psc;
   TIM_TimeBaseStructure.TIM_ClockDivision = 0;
   TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
   TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

   TIM_ITConfig(TIM3,TIM_IT_Update | TIM_IT_Trigger, ENABLE);

   NVIC_InitTypeDef NVIC_InitStructure; 
   NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);

   TIM_Cmd(TIM3, ENABLE);
}

/**
  * @brief  TIM2初始化配置
  * @param  无
  * @retval 无
  */
void TIM2_Cap_Init(void)
{
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

   GPIO_InitTypeDef GPIO_InitStructure;
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
   GPIO_Init(GPIOA, &GPIO_InitStructure);

   GPIO_ResetBits(GPIOA, GPIO_Pin_0);

   TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
   TIM_TimeBaseStructure.TIM_Period = 0xFFFF;
   TIM_TimeBaseStructure.TIM_Prescaler = 0;
   TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
   TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
   TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
   TIM_ITRxExternalClockConfig(TIM2, TIM_TS_ETRF);
   TIM_ETRClockMode2Config(TIM2, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0);
   TIM_SetCounter(TIM2, 0);

   TIM_Cmd(TIM2, ENABLE);
}

void TIM3_IRQHandler(void)
{
   if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
   {
      TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
      count = TIM_GetCounter(TIM2);
      switch (flag)
      {
      case 0:
         TSC_WB(0, 0); //选择让红色光线通过滤波器的模式
         break;
      case 1:
         cnt[0] = count;//存储100ms内的红光通过滤波器时，TCS3200输出的脉冲个数
         TSC_WB(1, 1);//选择让绿色光线通过滤波器的模式
         break;
      case 2:
         cnt[1] = count; //存储100ms内的绿光通过滤波器时，TCS3200输出的脉冲个数
         TSC_WB(0, 1);//选择让蓝色光线通过滤波器的模式
         break;
      case 3:
         cnt[2] = count;//存储1s内的蓝光通过滤波器时，TCS3200输出的脉冲个数
         TSC_WB(1, 0); //选择无滤波器的模式  
         break;
      default:
         count = 0;//计数值清零
         break;
      }
      TIM_SetCounter(TIM2, 0);
   }
}
