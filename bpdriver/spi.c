#include <spi.h>
#include <bp_config.h>

void spi_initn(SPI_TypeDef *spi_n)
{
    SPI_InitTypeDef SPI_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;

    switch ((u32)spi_n)
    {
    case (u32)SPI1:
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

        GPIO_InitStructure.GPIO_Pin = spi1_clk | spi1_mosi | spi1_miso;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(spi1_gpio, &GPIO_InitStructure);

        GPIO_InitStructure.GPIO_Pin = spi1_nss;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_Init(spi1_gpio, &GPIO_InitStructure);
        break;

    case (u32)SPI2:
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI2, ENABLE);

        GPIO_InitStructure.GPIO_Pin = spi2_clk | spi2_mosi | spi2_miso;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(spi2_gpio, &GPIO_InitStructure);

        GPIO_InitStructure.GPIO_Pin = spi2_nss;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_Init(spi2_gpio, &GPIO_InitStructure);
        GPIO_InitStructure.GPIO_Pin = spi2_selectpin;
        GPIO_Init(spi2_selectgpio, &GPIO_InitStructure);
        GPIO_ResetBits(spi2_selectgpio, spi2_selectpin);
        break;

    case (u32)SPI3:
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

        GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

        GPIO_InitStructure.GPIO_Pin = spi3_clk | spi3_mosi | spi3_miso;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(spi3_gpio, &GPIO_InitStructure);
        GPIO_InitStructure.GPIO_Pin = spi3_cs;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_Init(spi3_gpio, &GPIO_InitStructure);

        SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
        SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
        SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;

        SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
        break;
    default:
    }

    SPI_Init(spi_n, &SPI_InitStructure);
    SPI_Cmd(spi_n, &SPI_InitStructure);
    SPI_Cmd(spi_n, ENABLE);
    spi_sendrece(spi_n, 0xFF);
}

/**
 * 发送数据，随即接收
 */
u8 spi_sendrece(SPI_TypeDef *spi_n, u8 data)
{
    u8 rece = 0;
    u8 timeout = SPI_TIMEOUT;
    // 等待 SPI 发送缓冲区为空
    while (SPI_I2S_GetFlagStatus(spi_n, SPI_I2S_FLAG_TXE) == RESET)
    {
        if (timeout-- < 1)
        {
            // print error
            return 0;
        }
    }
    SPI_I2S_SendData(spi_n, data);
    timeout = SPI_TIMEOUT;
    while (SPI_I2S_GetFlagStatus(spi_n, SPI_I2S_FLAG_RXNE) == RESET)
    {
        if (timeout-- < 1)
        {
            //print error
            return 0;
        }
    }

    return (SPI_I2S_ReceiveData(spi_n));
}

/**
 * 设置SPI频率 
 */
void spi_setspeed(SPI_TypeDef *spi_n, u8 speed)
{
    uint16_t tmpreg = 0;
    SPI_Cmd(spi_n, DISABLE);
    tmpreg = spi_n->CR1;
    tmpreg &= 0xFFC7;
    tmpreg |= speed;
    SPI_Cmd(spi_n, ENABLE);
}