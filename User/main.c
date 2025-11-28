#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "Motor.h"
#include "PWM.h"
#include "Botton.h"
#include "Trace.h"

// 删除冗余变量（keynum、mode、state，无实际作用）
extern uint8_t KeyNum;

int main(void)
{
    OLED_Init();
    Motor_Init();
    PWM_Init();
    menu_Init1();
    menu_Init2();
    Trace_Init();
    
    while (1)
    {
        Key_GetNum(); // 按键检测（档位切换）
        Update_Menu_Display(); // OLED档位显示
        Trace_task(); // 循迹控制核心
    }
}