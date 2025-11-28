#ifndef TRACE_H
#define TRACE_H

#include "stm32f10x.h"

// 函数声明（仅声明，不定义）
void Trace_Init(void);
void Trace_task(void);
uint8_t Get_X1(void);
uint8_t Get_X2(void);
uint8_t Get_X3(void);
uint8_t Get_X4(void);

#endif // TRACE_H