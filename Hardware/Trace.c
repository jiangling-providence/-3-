#include "stm32f10x.h"
#include "Delay.h"
#include "Trace.h"
#include "Motor.h"
#include "Botton.h"

uint8_t i=0;
uint8_t wdf = 0;
extern uint8_t KeyNum;

// 1. 传感器引脚
void Trace_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;  // 下拉输入（根据传感器实际输出调整）
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12; // 修正引脚，去掉PB12
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

// 2. 实现传感器读取函数（对应修正后的引脚）
uint8_t Get_X1(void) { return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_9); }   // 左传感器
uint8_t Get_X2(void) { return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_10); }  // 左中传感器
uint8_t Get_X3(void) { return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11); }  // 右中传感器
uint8_t Get_X4(void) { return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12); }  // 右传感器

// 3. 修复switch缺break，档位正常切换
void Trace_task(void)
{
    switch (KeyNum)            
    {    
        case 0 : i = 0;    break;  // 加break，避免穿透
        case 1 : i = 10;   break;
        case 2 : i = 50;   break;
        case 3 : i = 90;   break;
        default: i = 0;    break;  // 默认停转
    }
    
    uint8_t x1 = Get_X1();
    uint8_t x2 = Get_X2();
    uint8_t x3 = Get_X3();
    uint8_t x4 = Get_X4();

    // 循迹逻辑保留，仅确保速度i有效
    if(x2 == 1 && (x1 == 0 && x3 == 0) && x4 == 1) { // 直行
        Motor_SetSpeed1(i);
        Motor_SetSpeed2(i);
    }
    else if(x2 == 1 && x1 == 0 && x3 == 1 && x4 == 1) { // 左转
        Motor_SetSpeed1(0);
        Motor_SetSpeed2(i);
    }
    else if(x2 == 1 && x1 == 1 && x3 == 0 && x4 == 1) { // 右转
        Motor_SetSpeed1(i);
        Motor_SetSpeed2(0);
    }
    else if(x2 == 0 && (x1 == 1 || x1 == 0) && x3 == 1 && x4 == 1) { // 急左转
        Motor_SetSpeed1(-i);
        Motor_SetSpeed2(i);
    }
    else if(x2 == 1 && x1 == 1 && (x3 == 1 || x3 == 0) && x4 == 0) { // 急右转
        Motor_SetSpeed1(i);
        Motor_SetSpeed2(-i);
    }
    else if(x2 == 0 && x1 == 0 && x3 == 0 && x4 == 0) { // 全触发直行
        Motor_SetSpeed1(i);
        Motor_SetSpeed2(i);
    }
    else if (x2 == 1 && x1 == 1 && x3 == 1 && x4 == 1){ // 无触发停转
        Motor_SetSpeed1(0);
        Motor_SetSpeed2(0);
    }
}