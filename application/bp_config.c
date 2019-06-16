#include <bp_config.h>

void exti_config(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_EXTILineConfig(button_port_source, button1_source);
	GPIO_EXTILineConfig(button_port_source, button2_source);
	GPIO_EXTILineConfig(button_wakeup_port_source, button_wakeup_source);

	EXTI_InitStructure.EXTI_Line = buttonl_exti_line | button2_exti_line;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;		//模式为中断
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发中断
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	EXTI_InitStructure.EXTI_Line = button_wakeup_exti_line;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	//模式为中断
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //上升沿触发中断
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = button_irqn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = button_wakeup_irqn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0E;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/**
	 * 由此断开  哈哈
	 */

	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	//设置DMAI通道5先占优先级1，子优先级2,使能！

	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	//设置DMAI通道4先占优先级1,子优先级2,使能！不让它们互相抢占！

	USART_DMACmd(USART1, USART_DMAReq_Rx | USART_DMAReq_Tx, ENABLE);
	//开启DMA方式的串口发送和接收
	DMA_Cmd(DMA1_Channel5, ENABLE);
	//启动DMA接收
	DMA_ITConfig(DMA1_Channel5, DMA_IT_TC, ENABLE);
	DMA_ITConfig(DMA1_Channel4, DMA_IT_TC, ENABLE);
	//使能这两个DMA通道的中断
}

void clock_config()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC |
							   RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE | RCC_APB2Periph_AFIO |
							   RCC_APB1Periph_PWR | RCC_APB1Periph_BKP,
						   ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB1Periph_USART2 | RCC_APB1Periph_UART4, ENABLE);
}
