/**
  ******************************************************************************
  * @file    TP PdM - PCSE/Inc/hw_timer_port.h.h
  * @brief   Header for hw_timer_port.c module
  ******************************************************************************
*/
#ifndef __US_TIMER_PORT_H__
#define __US_TIMER_PORT_H__

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "stdbool.h"
#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */
#include "stm32f4xx_hal_tim.h"
#include "API_error.h"

/*******************************************************************************
 * Typedefs
 ******************************************************************************/
typedef bool bool_t;

/*******************************************************************************
 * Defines
 ******************************************************************************/
#define MAX_TIMEOUT 100000

/*******************************************************************************
 * Function prototypes
 ******************************************************************************/
bool_t usTimerInit_port(void);
bool_t usTimerStart_port(void);
bool_t usTimerStop_port(void);
void usTimerDelay_port(uint16_t delay_us);
void msTimerDelay_port(uint16_t delay_us);



#endif
