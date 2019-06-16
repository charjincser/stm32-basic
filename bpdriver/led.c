#include <led.h>

void led_init(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	
	//led 
	GPIO_InitStructure.GPIO_Pin = led1 | led2 | led3 | led4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(led_gpio,&GPIO_InitStructure);
	
	//beep
	GPIO_InitStructure.GPIO_Pin = beep;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
}

void beep_run(INT8U runtime){
	GPIO_SetBits(beep_gpio,beep);
	delay_ms(runtime);
	GPIO_ResetBits(beep_gpio,beep);
}

