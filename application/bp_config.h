#ifndef __BPCONFIG_H
#define __BPCONFIG_H

#include <include.h>

#define led_gpio GPIOC
#define beep_gpio GPIOE //蜂鸣器在E组端口
#define led1 GPIO_Pin_6
#define led2 GPIO_Pin_7
#define led3 GPIO_Pin_8
#define led4 GPIO_Pin_9
#define beep GPIO_Pin_0

// Wakeup
#define button_wakeup_gpio GPIOA //gpio A组端口
#define button_wakeup GPIO_Pin_0 //A组端口的0号引脚
#define button_wakeup_port_source GPIO_PortSourceGPIOA
#define button_wakeup_source GPIO_PinSource0
#define button_wakeup_exti_line EXTI_Line0
#define button_wakeup_irqn EXTI0_IRQn //中断响应的入口为0号

/*
 *	Button
 */
#define button_gpio GPIOB
#define button_port_source GPIO_PortSourceGPIOB
#define button_irqn EXTI9_5_IRQn
// button1
#define button1 GPIO_Pin_8
#define button1_source GPIO_PinSource8
#define buttonl_exti_line EXTI_Line8
// button2
#define button2 GPIO_Pin_9
#define button2_source GPIO_PinSource9
#define button2_exti_line EXTI_Line9

void exti_config(void);
void delay_ms(INT8U ms);

/**
 * SPI
 */

#define spi1_gpio GPIOA
#define spi1_clk GPIO_Pin_5
#define spi1_mosi GPIO_Pin_7
#define spi1_miso GPIO_Pin_6
#define spi1_nss GPIO_Pin_4

#define spi2_gpio GPIOB
#define spi2_clk GPIO_Pin_13
#define spi2_mosi GPIO_Pin_15
#define spi2_miso GPIO_Pin_14
#define spi2_nss GPIO_Pin_12
#define spi2_selectgpio GPIOC
#define spi2_selectpin GPIO_Pin_12

#define spi3_gpio GPIOB
#define spi3_clk GPIO_Pin_3
#define spi3_mosi GPIO_Pin_5
#define spi3_miso GPIO_Pin_4
#define spi3_cs GPIO_Pin_11

#endif
