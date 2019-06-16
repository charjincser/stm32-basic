#include <funcs.h>

INT16U led_flow = 0x1;
INT8U delaytime = 50;
int flag = 0;	//控制led灯亮起 0:13,1:24

/*
 *	led流水灯
 */
void show_led_flow(void){
	GPIO_ResetBits(led_gpio,0x03c0);	//0000 0011 1100 0000
	GPIO_SetBits(led_gpio,led_flow<<6);	//对应了以上4位
	led_flow <<= 1;
	if(led_flow == 0x10) led_flow = 0x1;	//8 左移位4次后重置
	delay_ms(delaytime);
}

/*
 *	led灯闪烁
 */
void show_led_twinkle(void){
	GPIO_ResetBits(led_gpio,0x03c0);
	delay_ms(delaytime);
	GPIO_SetBits(led_gpio,0x03c0);
	delay_ms(delaytime);
}

/*
 *	led 13,24灯闪烁
 */
void show_led_13_24(void){
	GPIO_ResetBits(led_gpio,0x03c0);
	if(flag == 0){
			GPIO_SetBits(led_gpio,0x0140);	// 0000 0001 0100 0000
	}else{
			GPIO_SetBits(led_gpio,0x0280);	// 0000 0010 1000 0000
	}
}
