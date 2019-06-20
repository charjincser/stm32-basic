#ifndef __BPLED_H
#define __BPLED_H

#include <include.h>
#include <bp_config.h>

void show_led_flow(void);    //流水灯
void show_led_twinkle(void); //闪烁显示
void show_led_13_24(void);   //点击按键13,24灯交替亮起

void send_by_usart1_led_on(void); //串口1发送,led1对应亮起与熄灭
void send_by_usart2_led_on(void); //串口2发送,led2对应亮起与熄灭

#endif
