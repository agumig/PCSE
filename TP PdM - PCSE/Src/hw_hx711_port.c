/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "hw_hx711_port.h"

/******************************************************************************
 * Functions
 ******************************************************************************/
/**
 * @brief   Chip HX711 Init
 * @details GPIO init.
 * @return 	none
 */
void HX711_initPort(void)
{
	GPIO_InitTypeDef gpioConfig;

	/* GPIO Ports Clock Enable */
	GPIO_SECTION_D_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(HX711_CLK_GPIO_Port, HX711_CLK_MASK, GPIO_PIN_RESET);


	gpioConfig.Pin = HX711_DATA_MASK;
	gpioConfig.Mode = GPIO_MODE_INPUT;
	gpioConfig.Pull = GPIO_NOPULL;
	gpioConfig.Speed = GPIO_SPEED_FREQ_LOW;

	HAL_GPIO_Init(HX711_DATA_GPIO_Port, &gpioConfig);

	gpioConfig.Pin = HX711_CLK_MASK;
	gpioConfig.Mode = GPIO_MODE_OUTPUT_PP;
	gpioConfig.Pull = GPIO_NOPULL;
	gpioConfig.Speed = GPIO_SPEED_FREQ_LOW;

	HAL_GPIO_Init(HX711_CLK_GPIO_Port, &gpioConfig);

	usTimerInit();	// Initialize timer to use for HX711 comunication (Clk)
	usTimerStart();
}

/**
 * @brief   Set CLK GPIO in low level
 * @return 	none
 */
void HX711_CLK_setLow(void)
{
	HAL_GPIO_WritePin (HX711_CLK_GPIO_Port, HX711_CLK_MASK, GPIO_PIN_RESET);
}

/**
 * @brief   Set CLK GPIO in high level
 * @return 	none
 */
void HX711_CLK_setHigh(void)
{
	HAL_GPIO_WritePin (HX711_CLK_GPIO_Port, HX711_CLK_MASK, GPIO_PIN_SET);
}

/**
 * @brief   Get DATA GPIO level
 * @return 	uint8_t Data pin level
 */
uint8_t HX711_getLevel(void)
{
	return HAL_GPIO_ReadPin (HX711_DATA_GPIO_Port, HX711_DATA_MASK);
}

/**
 * @brief   HX711 delay
 * @param   uint16_t delay [us]
 * @return 	none
 */
void HW711_usdelay(uint16_t delay)
{
	//HAL_Delay(delay);
	usTimerDelay(delay);
}

/**
 * @brief   HX711 delay
 * @param   uint16_t delay [ms]
 * @return 	none
 */
void HW711_msDelay(uint16_t delay)
{
	msTimerDelay(delay);
}
/**
 * @brief   Disable interruptions
 * @return 	none
 */
void HX711_interruptsEnable(void)
{
	//portENABLE_INTERRUPTS();
}

/**
 * @brief   Enable interruptions
 * @return 	none
 */
void HX711_interruptsDisable(void)
{
	//portDISABLE_INTERRUPTS();
}
