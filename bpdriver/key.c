#include <key.h>

void key_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = button1 | button2 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;	//上拉模式  低电平有效.
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;
	GPIO_Init(button_gpio, &GPIO_InitStructure) ;
	
	GPIO_InitStructure.GPIO_Pin = button_wakeup ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD ;	//下拉模式  高电平有效.
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;
	GPIO_Init(button_wakeup_gpio, &GPIO_InitStructure) ;
}
