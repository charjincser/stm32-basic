#include <usart.h>
#include <include.h>

void usart_init()
{
	usart1_init(9600);
	usart2_init(9600);
}

void usart_sendstring(USART_TypeDef *usartn, char *format)
{
	while (*format)
	{
		USART_SendData(USART1, *format);
		while (USART_GetITStatus(USART1, USART_IT_TXE) != RESET)
			; //发送寄存器为empty
		format++;
	}
}

void usart1_init(INT32U Baud)
{
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	// PA9 发送, 仅初始化发送口
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// 串口初始化
	USART_InitStructure.USART_BaudRate = Baud;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

	USART_InitStructure.USART_Mode = USART_Mode_Tx; //发送

	USART_Init(USART1, &USART_InitStructure);
	USART_Cmd(USART1, ENABLE); // 使能串口1

	//解决第一个字符不能发送
	USART_GetFlagStatus(USART1, USART_FLAG_TC);

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0; //从优先级等级最高
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		 //IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);						 // 初始化外设NVIC寄存器

	USART_ITConfig(USART1, USART_IT_TXE, ENABLE); //串口2中断寄存器空时产生中断,这里即发送寄存器为空(数据发送完毕)
}

void usart2_init(INT32U Baud)
{
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	// PA2 发送, 仅初始化发送口
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// 串口初始化
	USART_InitStructure.USART_BaudRate = Baud;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

	USART_InitStructure.USART_Mode = USART_Mode_Tx; //发送

	USART_Init(USART2, &USART_InitStructure);
	USART_Cmd(USART2, ENABLE); //使能串口

	//清除接收中断,防止第一个字节无法发送的问题
	USART_GetFlagStatus(USART2, USART_FLAG_TC);

	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	USART_ITConfig(USART2, USART_IT_TXE, ENABLE); //串口2中断寄存器空时产生中断,这里即发送寄存器为空(数据发送完毕)
}

void uart4_init(INT32U Baud)
{
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	//	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	// PC10 发送
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	// PC11 接收
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	// 串口初始化
	USART_InitStructure.USART_BaudRate = Baud;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //发送 和 接收

	USART_Init(UART4, &USART_InitStructure);
	USART_Cmd(UART4, ENABLE); //使能串口

	//清除接收中断,防止第一个字节无法发送的问题
	USART_GetFlagStatus(UART4, USART_FLAG_TC);

	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE); //中断寄存器满时产生中断
}
