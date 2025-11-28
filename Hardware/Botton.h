#ifndef BOTTON_H
#define BOTTON_H

#include "stm32f10x.h"

// 函数声明
void menu_Init1(void);
void menu_Init2(void);
void Button_Init(void);
uint8_t Key_GetNum(void);
void Update_Menu_Display(void);
extern uint8_t KeyNum; // 外部变量声明

#endif // BOTTON_H