/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <API_timer_port.h>

/*******************************************************************************
 * Private global variable
 ******************************************************************************/
static TIM_HandleTypeDef htim1;

/*******************************************************************************
 * Private function prototypes
 ******************************************************************************/

/*******************************************************************************
 * Functions
 ******************************************************************************/
/**
 * @brief   Initialize Timer
 * @details Initialize timer for 1 us period
 * @param   none
 * @return 	bool_t:	true if the initialization was successful. False if not.
 */
bool_t usTimerInit_port(void)
{
	bool_t returnValue = false;

	TIM_ClockConfigTypeDef sClockSourceConfig = {0};
	TIM_MasterConfigTypeDef sMasterConfig = {0};

	/* Properties of the timer*/
	htim1.Instance = TIM1;

	htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim1.Init.Period = 65535;
	htim1.Init.Prescaler = 168;
	htim1.Init.RepetitionCounter = 0;

	if (HAL_TIM_Base_Init(&htim1) == HAL_OK)
	{
		returnValue = true;
	}

	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) == HAL_OK)
	{
		returnValue = true;
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) == HAL_OK)
	{
		returnValue = true;
	}

	return returnValue;
}

/**
 * @brief   Start of timer counting
 * @param   none
 * @return 	bool_t:	true if the start was successful. False if not.
 */
bool_t usTimerStart_port(void)
{
	bool_t returnValue = false;

	if(HAL_TIM_Base_Start(&htim1) == HAL_OK)
	{
		returnValue = true;
	}

	return returnValue;
}

/**
 * @brief   Stop of timer counting
 * @param   none
 * @return 	bool_t:	true if the stop was successful. False if not.
 */
bool_t usTimerStop_port(void)
{
	bool_t returnValue = false;

	if(HAL_TIM_Base_Stop(&htim1) == HAL_OK)
	{
		returnValue = true;
	}

	return returnValue;
}

/**
 * @brief   Delay in [us]
 * @details	Blocking delay in [us]
 * @param   uint16_t: delay [us]
 * @return 	none
 */
void usTimerDelay_port(uint16_t delay_us)
{
	uint32_t timeout = 0;

	__HAL_TIM_SET_COUNTER(&htim1, 0);	// start of counting at zero

	while((__HAL_TIM_GET_COUNTER(&htim1) < delay_us) && timeout < MAX_TIMEOUT)
	{
		timeout++;
	}

	if(timeout >= MAX_TIMEOUT)
		errorHandler();
}

/**
 * @brief   Delay in [ms]
 * @details	Blocking delay in [ms]
 * @param   uint16_t: delay [ms]
 * @return 	none
 */
void msTimerDelay_port(uint16_t delay_us)
{
	HAL_Delay(delay_us);
}





