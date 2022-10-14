/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "hw_valve.h"

/*******************************************************************************
 * Global private variables
 ******************************************************************************/
static bool_t valveErogationState = false, valveFillState = false;


/*******************************************************************************
 * Functions
 ******************************************************************************/
/**
 * @brief   Valves init
 * @details By default, set off the valves
 * @param   none
 * @return 	none
 */
void Valve_init(void)
{
	valveSet(FillValve, false);
	valveSet(ErogationValve, false);
}

/**
 * @brief   Valves state setting
 * @details Turn on or turn off a valve
 * @param   Output_Valve_t valve: valve selected
 * 			bool_t state :	state to set
 * @return 	none
 */
void valveSet(Output_Valve_t valve, bool_t state)
{
	switch(valve)
	{
	case ErogationValve:
		uartSendString(VALVULA_EROGACION_MSJ);
		valveErogationState = state;

		if(true == state)
			uartSendString(ENCENDIDO_MSJ);
		else
			uartSendString(APAGADO_MSJ);

		break;
	case FillValve:
		uartSendString(VALVULA_LLENADO_MSJ);
		valveFillState = state;

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
 * @brief   Valve state reading
 * @details Read the current state of a valve
 * @param   Output_Pump_t valve: valve selected
 * @return 	bool_t:	current state
 */
bool_t getValveState(Output_Valve_t valve)
{
	bool_t returnValue = false;

	switch(valve)
	{
	case ErogationValve:
		returnValue = valveErogationState;
		break;
	case FillValve:
		returnValue = valveFillState;
		break;
	default:
		errorHandler();
		break;
	}

	return returnValue;
}
