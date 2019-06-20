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

extern int USART_NUM; //表示串口编号(即哪一个串口(1或2)发送数据)

/**
 * 用以表示串口1(或2)是否处于发送状态
 * 1:可以进行发送 0:发送完毕
 * 在main中由该值决定led1(或2)熄灭操作是否执行
 * while(DMASEND);
 *    DMASEND = 1; //可以进行发送,等待下一次发送命令
 *    led1(或2)熄灭;
 */
extern u8 DMASEND;

/**
 * 判断是否产生了点击事件(在button中断响应程序中做改变)
 * 如果产生了一次点击事件,则is_click标记为1,在main中由该值决定是否执行
 * if(is_click){
 *      is_click = 0;
 *      串口的发送与led的亮起与熄灭;
 * }
 */
extern int is_click;
/**
 * 标记当前需要亮起或熄灭的led编号
 * (在USART1,2的发送缓冲区空中断响应程序中做改变)
 * 串口1: led_flag = 1, 串口2: led_flag = 2
 * 通过该值在main中判断,哪一led灯亮起与熄灭
 * if(led_flag == 1) led1_on();
 * else led2_on();
 * if(led_flag == 1) led1_off();
 * else led2_off();
 * 
 */
extern int led_flag;

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

/*
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
*/

//	button1,2 中断线路对应的中断服务程序
void EXTI9_5_IRQHandler(void)
{
  if ((EXTI_GetITStatus(button1_exti_line) != RESET) | (EXTI_GetITStatus(button2_exti_line) != RESET))
  {
    delay_ms(20); //消抖
    if (GPIO_ReadInputDataBit(button_gpio, button1) == 0x00)
    {
      USART_NUM = 1; //button1 按下后, 串口1发送数据
      led_flag = 1;  //led1亮起或熄灭
    }
    if (GPIO_ReadInputDataBit(button_gpio, button2) == 0x00)
    {
      USART_NUM = 2; //button2 按下后, 串口2发送数据
      led_flag = 2;  //led2亮起或熄灭
    }

    DMASEND = 1; //将该标志位置为1,表明允许使用DMA发送数据

    EXTI_ClearITPendingBit(button1_exti_line);
    EXTI_ClearITPendingBit(button2_exti_line);
  }
}

/**
//	串口通信之中断服务程序
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

void DMA1_Channel5_IRQHandler(void)
{

  u8 t;
  if (DMA_GetITStatus(DMA1_IT_TC5)) //通道5传输完成中断

    DMA_ClearITPendingBit(DMA1_IT_GL5); //清除中断等待标志
  if (TFT_SUPPORT)
    LcdPrintStr("DMAINTERUPED", 50, 200, BLACK, WHITE, 1);

  t = RECEBUF;
  RECEBUF = SENDBUF;
  SENDBUF = t; //典型的交换
  DMA_InitStructure5.DMA_MemoryBaseAddr = (u32)(&(USART1_BUF[RECEBUF][0]));
  DMA_Init(DMA1_Channel5, &DMA_InitStructure5); //重新配置缓冲区
}
*/

/**
 * 课本P32: DMA1通道4 对应USART1_TX(即发送)
 * 发送完成后触发该中断
 */
void DMA1_Channel4_IRQHandler(void)
{
  DMA_ClearITPendingBit(DMA1_IT_TC4); //清除中断标志
  DMASEND = 0;                        //通知主程序,数据发送已完成
}

/**
 * 课本P32: DMA1通道7 对应USART2_TX(即发送)
 * 发送完成后触发该中断
 */
void DMA1_Channel7_IRQHandler(void)
{
  DMA_ClearITPendingBit(DMA1_IT_TC7); //清除中断标志
  DMASEND = 0;                        //通知主程序,数据发送已完成
}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
