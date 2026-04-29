#ifndef __TCS3200_H
#define __TCS3200_H

#define S2_L	GPIO_WriteBit(GPIOB, GPIO_Pin_8, Bit_RESET)
#define S2_H	GPIO_WriteBit(GPIOB, GPIO_Pin_8, Bit_SET)
#define S3_L	GPIO_WriteBit(GPIOB, GPIO_Pin_9, Bit_RESET)
#define S3_H	GPIO_WriteBit(GPIOB, GPIO_Pin_9, Bit_SET)

extern float RGB_Scale[3];
extern int cnt[3];
extern int flag;
extern int count;

void TCS3200_Init(void);
void filter(int s2, int s3);
void TSC_WB(int s2, int s3);

#endif
