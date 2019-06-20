#ifndef __USART_H
#define __USART_H

#include <include.h>
#include <bp_config.h>

void usart_init(void);
void usart1_init(INT32U);
void usart2_init(INT32U);
void uart4_init(INT32U);
void usart_sendstring(USART_TypeDef *usartn, char *format);

#endif
