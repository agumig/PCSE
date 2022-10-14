/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "main.h"
#include "API_delay.h"

/*******************************************************************************
 * Public functions
 ******************************************************************************/
/**
 * @brief   Initialize the delay structure
 * @param   delay 		Pointer to the delay structure
 * @param	duration 	Delay in milliseconds
 * @return  None
 */
void delayInit( delay_t * delay, tick_t duration )
{
	if(delay != NULL && 0 < duration && duration < MAX_DELAY)
	{
		delay->running = false;
		delay->duration = duration;
	}
	else
	{
		while(1);
	}
}

/**
 * @brief   Read the delay state
 * @param   delay 		Pointer to the delay structure
 * @return  True if the delay happened, false if not.
 */
bool_t delayRead( delay_t * delay )
{
	bool_t returnValue = false;

	if(delay == NULL)
		while(1);

	if(delay->running)
	{
		if((HAL_GetTick() - delay->startTime) >= delay->duration)
		{
			delay->running = false;		// At the next delayRead, it will be runned again.
			returnValue = true;

		}
		else
			returnValue = false;
	}
	else
	{
		delay->startTime = HAL_GetTick();
		delay->running = true;
	}

	return returnValue;
}

/**
 * @brief   Change the delay value
 * @param   delay 		Pointer to the delay structure
 * @param	duration 	Delay in milliseconds
 * @return  None
 */
void delayWrite( delay_t * delay, tick_t duration )
{
	if(delay != NULL && 0 < duration && duration < MAX_DELAY)
	{
		delay->duration = duration;
	}
	else
	{
		while(1);
	}
}
