/**
  ******************************************************************************
  * @file    TP PdM - PCSE/Inc/hw_valve.h
  * @brief   Header for hw_valve.c module for managing solenoid valves
  ******************************************************************************
*/
#ifndef __HW_VALVE_H__
#define __HW_VALVE_H__

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "main.h"
#include "API_uart.h"

/*******************************************************************************
 * Typedefs
 ******************************************************************************/
typedef bool bool_t;

/* Valves on the system */
typedef enum{
	ErogationValve,
	FillValve
}Output_Valve_t;

/*******************************************************************************
 * Function prototypes
 ******************************************************************************/
void Valve_init(void);
void valveSet(Output_Valve_t valve, bool_t state);
bool_t getValveState(Output_Valve_t valve);

#endif
