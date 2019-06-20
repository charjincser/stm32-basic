#include <bp_config.h>
#include <include.h>
#include <funcs.h>
#include <dma.h>

extern void led_init(void);
extern void key_init(void);
extern void clock_config(void);
extern void led_on(int);
extern void led_all_off(void);

int led_flag; // 标记当前需要亮起或熄灭的led编号(1..4号)

// 串口1,2只做发送操作,一维数组表示
char USART12_BUF[][SENDBUFSIZE] = {"press button1", "press button2"};

/*
	u8 RECEBUF = 0; //目前接收缓冲
	u8 SENDBUF = 1; //目前发送缓冲
	u8 DMASEND = 0; //0表示目前DMA不在发送状态 1表示在发送
	u8 DMARECE = 0; //0表示串口接收DMA中断未发生，即从上次接收到一组数据并处理后，未接收完一组新的数据 1表示串口 DMA中断刚发生,数据等待处理
*/
int USART_NUM;   //表示串口编号(即哪一个串口(1或2)发送数据)
u8 DMASEND = 0; // 1:处于发送状态, 0:不在发送状态(已发送完成)

DMA_InitTypeDef DMA_InitStructure4; //串口1发送
DMA_InitTypeDef DMA_InitStructure7; //串口2发送

int main(void)
{
	clock_config();
	led_init();
	key_init();
	usart_init(); //串口初始化

	dma4_configuration(); //DMA1 通道4初始化
	dma7_configuration(); //DMA1 通道7初始化
	exti_config();		  // 初始化中断配置

	while (1)
	{
		if (DMASEND)
		{
			DMASEND = 0; // 清除发送标志

			if (USART_NUM == 1)
				DMA_Cmd(DMA1_Channel4, ENABLE); // 开始DMA方式串口1发送数据(通道4)
			else if (USART_NUM == 2)
				DMA_Cmd(DMA1_Channel7, ENABLE); // 开始DMA方式串口2发送数据(通道7)

			led_on(led_flag); //点亮对应的led灯(1或2)
			while (DMASEND)
				;		 // 等待发送完成,可以加入其它处理代码
			led_all_off();
		}
		delay_ms(100);
	}
}
