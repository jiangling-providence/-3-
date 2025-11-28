#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"

uint8_t KeyNum = 0;

void menu_Init1(void) { // PA1 下按键（档位切换）
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void menu_Init2(void) { // PC15 确认按键（暂未用）
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}



// 4. 保留单套按键检测（防抖有效），删除冗余逻辑
uint8_t Key_GetNum(void) {
    if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == 0) {
        Delay_ms(20); // 防抖
        while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) == 0);
        Delay_ms(20);
        KeyNum++;
        if(KeyNum == 4) KeyNum = 0; // 0-3循环切换档位
    }
    return KeyNum;
}

void Update_Menu_Display(void) { // OLED显示正常，无需修改
    OLED_Clear();
    switch (KeyNum) 
    {
        case 0 : OLED_ShowString(1, 1, ">Start");OLED_ShowString(2, 1, "speed=10");OLED_ShowString(3, 1, "speed=50");OLED_ShowString(4, 1, "speed=90");break;
        case 1 : OLED_ShowString(1, 1, "Start");OLED_ShowString(2, 1, ">speed=10");OLED_ShowString(3, 1, "speed=50");OLED_ShowString(4, 1, "speed=90");break;
        case 2 : OLED_ShowString(1, 1, "Start");OLED_ShowString(2, 1, "speed=10");OLED_ShowString(3, 1, ">speed=50");OLED_ShowString(4, 1, "speed=90");break;
        case 3 : OLED_ShowString(1, 1, "Start");OLED_ShowString(2, 1, "speed=10");OLED_ShowString(3, 1, "speed=50");OLED_ShowString(4, 1, ">speed=90");break;
    }
}

// 新增外部中断服务函数（PA1按键触发，可选，与Key_GetNum二选一即可）
