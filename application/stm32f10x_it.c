/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include <bp_config.h>

extern INT8U delaytime;
extern void beep_run(INT8U runtime);
extern int fun_num;
extern int flag;

/**
 * DMA 全局变量
 */

extern u8 DMASEND; 
extern u8 DMARECE; 

/*
	My functions.
 */
extern void show_led_flow(void);
extern void show_led_twinkle(void);
extern void show_led_13_24(void);

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */

//	wakeup 中断线路对应的中断服务程序
void EXTI0_IRQHandler(void)
{
  if (EXTI_GetITStatus(button_wakeup_exti_line) != RESET)
  {
    if (GPIO_ReadInputDataBit(button_gpio, button_wakeup) == 0x1)
    {
      delay_ms(20);

      fun_num = 2;
      flag = !flag;

      EXTI_ClearITPendingBit(button_wakeup_exti_line);
    }
  }
}

//	button1,2 中断线路对应的中断服务程序
void EXTI9_5_IRQHandler(void)
{
  if ((EXTI_GetITStatus(buttonl_exti_line) != RESET) | (EXTI_GetITStatus(button2_exti_line) != RESET))
  {
    delay_ms(20); //消抖
    if (GPIO_ReadInputDataBit(button_gpio, button2) == 0x00)
    {
      fun_num = 1;
    }
    if (GPIO_ReadInputDataBit(button_gpio, button1) == 0x00)
    {
      fun_num = 0;
    }
    beep_run(200); //来一段蜂鸣声 说明中断响应成功了.
    EXTI_ClearITPendingBit(buttonl_exti_line);
    EXTI_ClearITPendingBit(button2_exti_line);
  }
}

/*
 *	串口通信之中断服务程序
 */
void USART1_IRQHandler(void)
{
  u8 Rece;
  if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) //判断是不是usart1满产生的中断
  {
    Rece = USART_ReceiveData(USART1); //串口1接收数据
    USART_SendData(USART2, Rece);     //从串口2发送数据
  }
}

void USART2_IRQHandler(void)
{
  u8 Rece;                                               // 存放接收的8位数据
  if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) // 是否发生中断
  {
    Rece = USART_ReceiveData(USART1); //串口1接收数据
    USART_SendData(USART2, Rece);     //从串口2发送数据
  }
}

void UART4_IRQHandler(void)
{
  u8 Rece;
  if (USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)
  {
    Rece = USART_ReceiveData(UART4);
    USART_SendData(UART4, Rece); // 把收到的数据重新发回去
  }
}

// void DMA1_Channel5_IRQHandler(void)
// {

//   u8 t;
//   if (DMA_GetITStatus(DMA1_IT_TC5)) //通道5传输完成中断

//     DMA_ClearITPendingBit(DMA1_IT_GL5); //清除中断等待标志
//   if (TFT_SUPPORT)
//     LcdPrintStr("DMAINTERUPED", 50, 200, BLACK, WHITE, 1);

//   t = RECEBUF;
//   RECEBUF = SENDBUF;
//   SENDBUF = t; //典型的交换
//   DMA_InitStructure5.DMA_MemoryBaseAddr = (u32)(&(USART1_BUF[RECEBUF][0]));
//   DMA_Init(DMA1_Channel5, &DMA_InitStructure5); //重新配置缓冲区
// }

void DMA1_Channel4_IRQHandler(void)
{
  DMA_ClearITPendingBit(DMA1_IT_TC4); //清除中断标志
  DMASEND = 0;                        //通知主程序,数据发送刚刚完成
}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
