#include "spi.h"
#include "mcu.h"

//TODO rework to STM32L mcu's

void initSPI2(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

	//PB13 - SPI2_SCK
	//PB14 - SPI2_MISO
	//PB15 - SPI2_MOSI
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_SPI2);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_SPI2);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_SPI2);

	SPI_InitTypeDef  SPI_InitStructure;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CRCPolynomial = SPI_CRC_Rx;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;

	/* Apply SPI configuration after enabling it */
	SPI_Init(SPI2, &SPI_InitStructure);
	/* SPI Peripheral Enable */
	SPI_Cmd(SPI2, ENABLE);
}

unsigned char readWriteSPI2(unsigned char txData)
{
	SPI2->DR = txData;
	// wait until TXE = 1
	while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_TXE) != SET);
	// wait until RXNE = 1
	while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_RXNE) != SET);
	// read the rx buff to clear the RXNE flag (garbage)
	unsigned char  rxData = SPI2->DR;
	return rxData;
}

void initCS_Pin(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void device_Select(void)
{
	GPIOB->BSRRH = GPIO_Pin_12;
}

void device_Unselect(void)
{
	GPIOB->BSRRL = GPIO_Pin_12;
}

