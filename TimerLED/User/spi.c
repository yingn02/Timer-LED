#include <ch32v00x.h>
#include "debug.h"
#include "spi.h"
#include "ram.h"
#include "mode_function.h"



void spi_led_init(void) //spi, gpio
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    SPI_InitTypeDef  SPI_InitStructure = {0};

    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD | RCC_APB2Periph_SPI1, ENABLE );

    SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master; //master or slave
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b; //8bit
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low; //clock steady state.
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge; //SPI_CPHA_1Edge: when clock up, read
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft; //NSS(CS) signal is managed by Software or Hardware
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64; //baud rate prescaler value
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; //MSB or LSB
    SPI_InitStructure.SPI_CRCPolynomial = 7; //polynomial for the CRC
    SPI_Init(SPI1, &SPI_InitStructure);

    SPI_Cmd(SPI1, ENABLE); //SPI enable or disable

    //SCK
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_30MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    //DO
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_30MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    //switch
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_30MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

}



void spi_write(u8*color_data)
{   
    for(u8 i=0; i<4; i++) 
    {
        while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
        SPI_I2S_SendData(SPI1, 0);
    }

    for(u8 i=0; i<COLOR_DATA_LEN; i++) 
    {
        while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
        SPI_I2S_SendData(SPI1, color_data[i]);
    }

    for(u8 i=0; i<4; i++) 
    {
        while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
        SPI_I2S_SendData(SPI1, 255); 
    }  
    
}