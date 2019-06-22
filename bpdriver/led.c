#include <led.h>

void led_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	//LED 初始化led1,2为输出模式
	GPIO_InitStructure.GPIO_Pin = led1 | led2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(led_gpio, &GPIO_InitStructure);
}

/**
 * 根据下标决定点亮哪一led灯
 */
void led_on(int index)
{
	switch (index)
	{
		case 1 : GPIO_SetBits(led_gpio, 0x0040);break;	// 0000 0000 0100 0000
		case 2 : GPIO_SetBits(led_gpio, 0x0080);break;	// 0000 0000 1000 0000
		case 3 : GPIO_SetBits(led_gpio, 0x0100);break;	// 0000 0001 0000 0000
		case 4 : GPIO_SetBits(led_gpio, 0x0200);break;	// 0000 0010 0000 0000
		default: break;
	}
}

/**
 * 熄灭所有led灯
 */
void led_all_off(void)
{
	GPIO_SetBits(led_gpio, 0x0000);
}

// void beep_run(INT8U runtime)
// {
// 	GPIO_SetBits(beep_gpio, beep);
// 	delay_ms(runtime);
// 	GPIO_ResetBits(beep_gpio, beep);
// }
