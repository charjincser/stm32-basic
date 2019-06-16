#include <bp_config.h>
#include <include.h>
#include <funcs.h>
#include <dma.h>

//INT8U delaytime;
extern void led_init(void);
extern void key_init(void);
extern void clock_config(void);

extern void show_led_flow(void);
extern void show_led_twinkle(void);
extern void show_led_13_24(void);

int fun_num = 0; // 0 1 2 不同的序号代表执行不同的功能.

//全局变量定义
u8 USART1_BUF[2][RECEBUFSIZE]; //缓冲区，二维数组

u8 RECEBUF = 0; //目前接收缓冲
u8 SENDBUF = 1; //目前发送缓冲
u8 DMASEND = 0; //0表示目前DMA不在发送状态
	//I表示在发送
u8 DMARECE = 0; //0表示串口接收DMA中断未发生，即从上次接收到一组数据并处理后，未接收完一组新的数据
	//I表示串口 DMA中断刚发生,数据等待处理

DMA_InitTypeDef DMA_InitStructure4;
DMA_InitTypeDef DMA_InitStructure5;

int main(void)
{
	clock_config();
	led_init();
	key_init();
	usart_init(); //串口初始化

	dma4_configuration(); //DMA初始化
	dma5_configuration();
	exti_config();

	DMASEND = 1; // 发送缓冲区为USART1_BUF[1]
	DMARECE = 0; // 发送缓冲区为USART1_BUF[0]

	while (1)
	{
		if (DMARECE)
		{
			DMARECE = 0; // 清除接收标志
			DMA_InitStructure4.DMA_MemoryBaseAddr = (u32)(USART1_BUF[SENDBUF]);
			DMA_Init(DMA1_Channel1, &DMA_InitStructure4);
			// 更改发送缓冲区

			DMA_Cmd(DMA1_Channel4, ENABLE);
			// 开始DMA方式串口发送接收收到的数据

			led_on1();
			while (DMASEND)
				;		 // 等待发送完成,可以加入其它处理代码
			DMASEND = 1; // 发送完成
			led1_off();
		}

		delay_ms(100);
	}
}

// if (fun_num == 0)
// 	show_led_flow();
// if (fun_num == 1)
// 	show_led_twinkle();
// if (fun_num == 2)
// 	show_led_13_24();