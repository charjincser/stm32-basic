#include <dma.h>

extern char USART12_BUF[][SENDBUFSIZE];
extern DMA_InitTypeDef DMA_InitStructure4;
extern DMA_InitTypeDef DMA_InitStructure7;

/**
 * 课本P32
 * DMA4 配置函数
 * 通道4为串口1数据发送
 */
void dma4_configuration(void)
{
    DMA_DeInit(DMA1_Channel4);
    DMA_InitStructure4.DMA_PeripheralBaseAddr = (u32)SRC_USART1_DR;
    DMA_InitStructure4.DMA_MemoryBaseAddr = (u32)(USART12_BUF[0]);
    //设置内存地址为发送缓冲区首地址
    DMA_InitStructure4.DMA_DIR = DMA_DIR_PeripheralDST;
    //方向，从内存到外设,外设是目的地
    DMA_InitStructure4.DMA_BufferSize = SENDBUFSIZE;
    //DMA缓冲大小为发送缓冲大小
    DMA_InitStructure4.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    //外设地址寄存器不增长,为固定模式
    DMA_InitStructure4.DMA_MemoryInc = DMA_MemoryInc_Enable;
    //内存地址每次发送都增加
    DMA_InitStructure4.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    //外设按字节发送
    DMA_InitStructure4.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    //内存也按字节传输
    DMA_InitStructure4.DMA_Mode = DMA_Mode_Normal;
    //DMA常规模式
    DMA_InitStructure4.DMA_Priority = DMA_Priority_High;
    //DMA中优先级
    DMA_InitStructure4.DMA_M2M = DMA_M2M_Disable;
    //不是内存到内存
    DMA_Init(DMA1_Channel4, &DMA_InitStructure4);
    //按以上参数执行初始化
}

/**
 * 课本P32
 * DMA7 配置函数
 * 通道7为串口2数据发送
 */
void dma7_configuration(void)
{
    DMA_DeInit(DMA1_Channel7); //复位DMA通道7配置
    DMA_InitStructure7.DMA_PeripheralBaseAddr = (u32)SRC_USART2_DR;
    //设置DMA7外设基地址为串口2发送地址
    DMA_InitStructure7.DMA_MemoryBaseAddr = (u32)(USART12_BUF[1]);
    //设置内存地址为发送缓冲区首地址
    DMA_InitStructure7.DMA_DIR = DMA_DIR_PeripheralSRC;
    //方向,从外设到内存,外设是源头
    DMA_InitStructure7.DMA_BufferSize = SENDBUFSIZE;
    //DMA缓冲大小为发送缓冲大小
    DMA_InitStructure7.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    //外设地址寄存器不增长,为固定模式
    DMA_InitStructure7.DMA_MemoryInc = DMA_MemoryInc_Enable;
    //内存地址每次发送都增加
    DMA_InitStructure7.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    //外设按字节发送
    DMA_InitStructure7.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    //内存也按字节传输
    DMA_InitStructure7.DMA_Mode = DMA_Mode_Circular;
    //DMA循环模式
    DMA_InitStructure7.DMA_Priority = DMA_Priority_High;
    //DMA中优先级
    DMA_InitStructure7.DMA_M2M = DMA_M2M_Disable;
    //不是内存到内存
    DMA_Init(DMA1_Channel7, &DMA_InitStructure7);
    //按以上参数执行初始化
}
