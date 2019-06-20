#ifndef __DAM_H
#define __DAM_H

#define SENDBUFSIZE 15 //发送缓冲区大小

#include <include.h>
#include <stm32f10x_dma.h>
#include <bp_config.h> 

void dma4_configuration(void);
void dma7_configuration(void);

#endif
