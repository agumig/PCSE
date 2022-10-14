
/**
  ******************************************************************************
  * @file    UART/UART_Printf/Inc/main.h
  * @author  MCD Application Team
  * @brief   Header for main.c module
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H


/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdio.h>
#include "stm32f4xx_hal.h"  		/* <- HAL include */
#include "stm32f4xx_nucleo_144.h" 	/* <- BSP include */
#include <stdint.h>
#include <stdbool.h>
#include "API_error.h"

/*******************************************************************************
 * Defines
 ******************************************************************************/
//#define _CALIBRATION__	// Enable HX711 calibration

/* Definition for USARTx clock resources */
#define USARTx                           USART3
#define USARTx_CLK_ENABLE()              __HAL_RCC_USART3_CLK_ENABLE();
#define USARTx_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOD_CLK_ENABLE()
#define USARTx_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOD_CLK_ENABLE()

#define USARTx_FORCE_RESET()             __HAL_RCC_USART3_FORCE_RESET()
#define USARTx_RELEASE_RESET()           __HAL_RCC_USART3_RELEASE_RESET()

/* Definition for USARTx Pins */
#define USARTx_TX_PIN                    GPIO_PIN_8
#define USARTx_TX_GPIO_PORT              GPIOD
#define USARTx_TX_AF                     GPIO_AF7_USART3
#define USARTx_RX_PIN                    GPIO_PIN_9
#define USARTx_RX_GPIO_PORT              GPIOD
#define USARTx_RX_AF                     GPIO_AF7_USART3


/* GPIO */
#define GPIO_SECTION_D_ENABLE() 		__HAL_RCC_GPIOD_CLK_ENABLE();

/* Celda de carga */
#define RESERVORY_LIMIT_MIN				1000	// [cm3] Minimum reservoir content.
#define RESERVORY_LIMIT_MAX				3000	// [cm3] Maximum reservoir content.
#define WEIGHT_READINGS					10	// [times] Readings to average the weight.


/* UART MESSAGES */
#define BOMBA_EROGACION_MSJ		((uint8_t *)"BOMBA EROGACION ")
#define VALVULA_EROGACION_MSJ	((uint8_t *)"VALVULA EROGACION ")
#define	BOMBA_LLENADO_MSJ		((uint8_t *)"BOMBA LLENADO ")
#define	VALVULA_LLENADO_MSJ		((uint8_t *)"VALVULA LLENADO ")
#define ENCENDIDO_MSJ			((uint8_t *)"- ON\n")
#define	APAGADO_MSJ				((uint8_t *)"- OFF\n")
#define TIMER1_CONFIG_MSJ		((uint8_t *)"INIT TIMER 1 SUCESS\n")

#define BINARY_BASE				2
#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
