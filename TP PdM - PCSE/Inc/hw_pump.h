/**
  ******************************************************************************
  * @file    TP PdM - PCSE/Inc/hw_pump.h
  * @brief   Header for hw_pump.c module for managing transistorized pumps
  ******************************************************************************
*/
#ifndef __HW_PUMP_H__
#define __HW_PUMP_H__

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "main.h"
#include "API_uart.h"
#include "API_error.h"

/*******************************************************************************
 * Typedefs
 ******************************************************************************/
typedef bool bool_t;

/* Pumps on the system */
typedef enum{
	ErogationPump,
	FillPump
}Output_Pump_t;

/*******************************************************************************
 * Function prototypes
 ******************************************************************************/
void Pump_init(void);
void pumpSet(Output_Pump_t pump, bool_t state);
bool_t getPumpState(Output_Pump_t pump);

#endif
