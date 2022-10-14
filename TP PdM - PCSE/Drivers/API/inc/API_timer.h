/**
  ******************************************************************************
  * @file    TP PdM - PCSE/Inc/hw_timer.h
  * @brief   Header for hw_timer..c module
  ******************************************************************************
*/
#ifndef __US_TIMER_H__
#define __US_TIMER_H__


/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "main.h"

/*******************************************************************************
 * Function prototypes
 ******************************************************************************/
void usTimerInit(void);
void usTimerStart(void);
void usTimerStop(void);
void usTimerDelay(uint16_t delay_us);
void msTimerDelay(uint16_t delay_us);


#endif
