/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "hw_pump.h"

/*******************************************************************************
 * Global private variables
 ******************************************************************************/
static bool_t pumpErogationState = false, pumpFillState = false;

/*******************************************************************************
 * Functions
 ******************************************************************************/
/**
 * @brief   Pumps init
 * @details By default, set off the pumps
 * @param   none
 * @return 	none
 */
void Pump_init(void)
{
	pumpSet(FillPump, false);
	pumpSet(ErogationPump, false);
}

/**
 * @brief   Pumps state setting
 * @details Turn on or turn off a pump
 * @param   Output_Pump_t pump: pump selected
 * 			bool_t state :	state to set
 * @return 	none
 */
void pumpSet(Output_Pump_t pump, bool_t state)
{
	switch(pump)
	{
	case ErogationPump:
		uartSendString(BOMBA_EROGACION_MSJ);
		pumpErogationState = state;

		if(true == state)
			uartSendString(ENCENDIDO_MSJ);
		else
			uartSendString(APAGADO_MSJ);
		break;
	case FillPump:
		uartSendString(BOMBA_LLENADO_MSJ);
		pumpFillState = state;

		if(true == state)
			uartSendString(ENCENDIDO_MSJ);
		else
			uartSendString(APAGADO_MSJ);
		break;
	default:
		errorHandler();
		break;
	}
}

/**
 * @brief   Pumps state reading
 * @details Read the current state of a pump
 * @param   Output_Pump_t pump: pump selected
 * @return 	bool_t:	current state
 */
bool_t getPumpState(Output_Pump_t pump)
{
	bool_t returnValue = false;

	switch(pump)
	{
	case ErogationPump:
		returnValue = pumpErogationState;
		break;
	case FillPump:
		returnValue = pumpFillState;
		break;
	default:
		errorHandler();
		break;
	}
	return returnValue;
}
