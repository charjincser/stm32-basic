#include <bp_config.h>

void exti_config(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	// 课本P29 优先级分组为2 先占优先级,从优先级各2位(0-3)
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	GPIO_EXTILineConfig(button_port_source, button1_source);
	GPIO_EXTILineConfig(button_port_source, button2_source);
	// GPIO_EXTILineConfig(button_wakeup_port_source, button_wakeup_source);

	// 配置button1 和 button2 外部线路等信息
	EXTI_InitStructure.EXTI_Line = button1_exti_line | button2_exti_line;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;		//模式为中断
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发中断
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	// button 设置外部中断通道和优先级
	NVIC_InitStructure.NVIC_IRQChannel = button_irqn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel7_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	//设置DMAI通道7先占优先级1，子优先级2,使能！

	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	//设置DMAI通道4先占优先级1,子优先级2,使能！不让它们互相抢占！

	USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
	USART_DMACmd(USART2, USART_DMAReq_Tx, ENABLE);
	//只开启DMA方式的串口1,2的发送

	DMA_ITConfig(DMA1_Channel7, DMA_IT_TC, ENABLE);
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
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
}
