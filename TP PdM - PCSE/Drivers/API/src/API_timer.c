/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <API_timer.h>
#include <API_timer_port.h>

/*******************************************************************************
 * Functions
 ******************************************************************************/
/**
 * @brief   Initialize Timer
 * @param   none
 * @return 	none
 */
void usTimerInit(void)
{
	if(usTimerInit_port() != true)
		errorHandler();
}

/**
 * @brief   Start of timer counting
 * @param   none
 * @return 	none
 */
void usTimerStart(void)
{
	usTimerStart_port();
}

/**
 * @brief   Stop of timer counting
 * @param   none
 * @return 	none
 */
void usTimerStop(void)
{
	usTimerStop_port();
}

/**
 * @brief   Delay in [us]
 * @details	Blocking delay in [us]
 * @param   uint16_t: delay [us]
 * @return 	none
 */
void usTimerDelay(uint16_t delay_us)
{
	usTimerDelay_port(delay_us);
}
/**
 * @brief   Delay in [ms]
 * @details	Blocking delay in [ms]
 * @param   uint16_t: delay [ms]
 * @return 	none
 */
void msTimerDelay(uint16_t delay_us)
{
	msTimerDelay_port(delay_us);
}


