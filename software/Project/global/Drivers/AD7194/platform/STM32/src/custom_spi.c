
/*.......................INCLUDES......................................*/
#include "custom_spi.h"

/*.........................PRIVATE_VARIABLES...........................*/

SPI_InitTypeDef SPI_InitStructure;
  /* Create SPIs struct */
SPI_HandleTypeDef SPI_Handle;
	/* Create GPIOs struct */
GPIO_InitTypeDef GPIO_InitStructure;



void spi_init ( void ){


	/* Activate Clock */
  __HAL_RCC_GPIOB_CLK_ENABLE();

  __HAL_RCC_SPI2_CLK_ENABLE();

  /* Config GPIOs */

  /* Configure spi GPIOs */
	GPIO_InitStructure.Pin 				= EXT_ADC_MISO_PIN | EXT_ADC_MOSI_PIN;
  GPIO_InitStructure.Speed 			= GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStructure.Mode 			= GPIO_MODE_AF_PP;
  GPIO_InitStructure.Pull 			= GPIO_PULLDOWN;
	GPIO_InitStructure.Alternate 	= EXT_ADC_SPI_ALT;


  HAL_GPIO_Init(EXT_ADC_SPI_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.Pin  	=	EXT_ADC_SCK_PIN;
	GPIO_InitStructure.Pull 	= GPIO_PULLUP;

	HAL_GPIO_Init(EXT_ADC_SPI_PORT, &GPIO_InitStructure);

		
	/*Configure NSS port*/

	GPIO_InitStructure.Pin  = EXT_ADC_NSS_PIN;
  GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStructure.Pull = GPIO_PULLUP;
  
	HAL_GPIO_Init(EXT_ADC_NSS_PORT, &GPIO_InitStructure);
	spi_disNSS();



  SPI_Handle.Instance 			= EXT_ADC_SPI;
  SPI_Handle.Init.Mode 			= SPI_MODE_MASTER;
  SPI_Handle.Init.Direction = SPI_DIRECTION_2LINES;
  SPI_Handle.Init.DataSize 	= SPI_DATASIZE_8BIT;
  SPI_Handle.Init.CLKPolarity 	= SPI_POLARITY_HIGH;
  SPI_Handle.Init.CLKPhase 	= SPI_PHASE_2EDGE;
  SPI_Handle.Init.NSS 			= SPI_NSS_SOFT;
  SPI_Handle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
  SPI_Handle.Init.FirstBit 	= SPI_FIRSTBIT_MSB;
  SPI_Handle.Init.TIMode 		= SPI_TIMODE_DISABLE;
  SPI_Handle.Init.CRCCalculation 	= SPI_CRCCALCULATION_DISABLE;
  SPI_Handle.Init.CRCPolynomial 	= 7;

  if (HAL_SPI_Init(&SPI_Handle) != HAL_OK)
  {
    while(1);
		
  }


}

void spi_deInit ( void )
{

  /* Deconfig GPIOs */
  /* Deconfigure SCK as Alternative Function PP */
  HAL_GPIO_DeInit(EXT_ADC_SCK_PORT, EXT_ADC_SCK_PIN);

  /* Deinitialize previous SPI configurations */
  if(HAL_SPI_DeInit(&SPI_Handle) != HAL_OK)
  {
    while(1);
  }

  /* Deselect extADC module on SPI bus */
  HAL_GPIO_WritePin(EXT_ADC_NSS_PORT, EXT_ADC_NSS_PIN, GPIO_PIN_SET);
}

void spi_enNSS(){
	HAL_GPIO_WritePin(EXT_ADC_NSS_PORT, EXT_ADC_NSS_PIN, GPIO_PIN_RESET);
}

void spi_disNSS(){
	HAL_GPIO_WritePin(EXT_ADC_NSS_PORT, EXT_ADC_NSS_PIN, GPIO_PIN_SET);
}

void spi_Transmit(uint8_t* data, uint8_t size){
	HAL_SPI_Transmit(&SPI_Handle, data, size, HAL_MAX_DELAY);
}

void spi_Receive(uint8_t* data, uint8_t size){
	HAL_SPI_Receive(&SPI_Handle, data, size, HAL_MAX_DELAY);
}

void spi_delay(uint32_t millis){
	HW_RTC_DelayMs(millis);
}