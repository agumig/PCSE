/**
 ******************************************************************************
 * @file    UART/UART_Printf/Src/main.c
 * @author  MCD Application Team
 * @brief   This example shows how to retarget the C library printf function
 *          to the UART.
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

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <API_timer.h>
#include "main.h"
#include "API_debounce.h"
#include "API_delay.h"
#include "API_uart.h"
#include "hw_hx711.h"
#include "hw_pump.h"
#include "hw_valve.h"

/*******************************************************************************
 * Private Typedef
 ******************************************************************************/

// States of MAIN Fine State Machine
typedef enum{
	IDLE,
	FILL,
	EROGATION
}FSM_State_t;

/*******************************************************************************
 * Private function prototypes
 ******************************************************************************/
static void SystemClock_Config(void);
static void mainFSM_update(void);
/*******************************************************************************
 * Private global variables
 ******************************************************************************/
static FSM_State_t state = IDLE;
static double reservoirWeight = 0;
static bool_t erogationButton = false;
/**
 * @brief  Main program
 * @param  None
 * @return None
 */
int main(void)
{

	/* STM32F4xx HAL library initialization:
       - Configure the Flash prefetch
       - Systick timer is configured by default as source of time base, but user 
         can eventually implement his proper time base source (a general purpose 
         timer for example or other time source), keeping in mind that Time base 
         duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and 
         handled in milliseconds basis.
       - Set NVIC Group Priority to 4
       - Low Level Initialization
	 */
	HAL_Init();

	/* Configure the system clock to 180 MHz */
	SystemClock_Config();

	/* Initialize BSP PB for BUTTON_USER */
	BSP_PB_Init(BUTTON_USER, BUTTON_MODE_GPIO);

	/* Initialize anti-debounce */
	debounceFSM_init();

	/* Initialize UART to send */
	if(!uartInit())
		errorHandler();

	/* For calibration it's necessary initializing the IC and reading the TARE value.
	 * After that we need to set HX711_REAL_OFFSET (in hw_hx711.h) with the TARE value*/
#ifdef _CALIBRATION__
	HX711_initCalibrationZero();
#endif

#ifndef _CALIBRATION__
	/* Initialize */
	HX711_init();
#endif

	Pump_init();
	Valve_init();

	/* Infinite loop */
	while (1)
	{

		debounceFSM_update();	// Read the button user state with anti debounce applied

		reservoirWeight = HX711_readWeigh(WEIGHT_READINGS);
		erogationButton = readKeyPressed();		// ¿Was the Button User pressed?

		mainFSM_update();
	}
}

/**
 * @brief   Main "Fine State Machine" updating
 * @param	none
 * @return 	void
 */
static void mainFSM_update(void)
{
	switch(state)
	{
	case IDLE:
		if(RESERVORY_LIMIT_MIN > reservoirWeight)	// Empty reservoir
		{
			state = FILL;
		}else
		{
			if(erogationButton)		// User demand of erogation
			{
				state = EROGATION;
			}
		}

		break;
	case FILL:

		if(erogationButton && (RESERVORY_LIMIT_MIN < reservoirWeight))	// Erogation demand and content of reservoir OK
		{
			state = EROGATION;

			// End of FILL
			if(getValveState(FillValve))
				valveSet(FillValve, false);
			if(getPumpState(FillPump))
				pumpSet(FillPump,false);
		}else
		{
			if(RESERVORY_LIMIT_MAX > reservoirWeight)	// Reservoir is not completely full
			{
				// Start of FILL
				if(!getValveState(FillValve))
					valveSet(FillValve, true);
				if(!getPumpState(FillPump))
					pumpSet(FillPump,true);
			}else
			{
				// End of FILL
				if(getValveState(FillValve))
					valveSet(FillValve, false);
				if(getPumpState(FillPump))
					pumpSet(FillPump,false);

				state = IDLE;
			}
		}
		break;
	case EROGATION:
		if(erogationButton && (RESERVORY_LIMIT_MIN < reservoirWeight))	// Erogation demand and content of reservoir OK
		{
			// Start of EROGATION
			if(!getValveState(ErogationValve))
				valveSet(ErogationValve, true);
			if(!getPumpState(ErogationPump))
				pumpSet(ErogationPump,true);
		}
		else
		{
			// End of EROGATION
			if(getValveState(ErogationValve))
				valveSet(ErogationValve, false);
			if(getPumpState(ErogationPump))
				pumpSet(ErogationPump,false);

			if(RESERVORY_LIMIT_MIN > reservoirWeight)	// Empty reservoir
			{
				state = FILL;
			}
			else
			{
				if(!erogationButton)
					state = IDLE;
			}
		}
		break;
	default:
		errorHandler();
		break;
	}
}
/**
 * @brief  System Clock Configuration
 *         The system Clock is configured as follow :
 *            System Clock source            = PLL (HSE)
 *            SYSCLK(Hz)                     = 180000000
 *            HCLK(Hz)                       = 180000000
 *            AHB Prescaler                  = 1
 *            APB1 Prescaler                 = 4
 *            APB2 Prescaler                 = 2
 *            HSE Frequency(Hz)              = 8000000
 *            PLL_M                          = 8
 *            PLL_N                          = 360
 *            PLL_P                          = 2
 *            PLL_Q                          = 7
 *            PLL_R                          = 2
 *            VDD(V)                         = 3.3
 *            Main regulator output voltage  = Scale1 mode
 *            Flash Latency(WS)              = 5
 * @param  None
 * @retval None
 */
static void SystemClock_Config(void)
{
	RCC_ClkInitTypeDef RCC_ClkInitStruct;
	RCC_OscInitTypeDef RCC_OscInitStruct;

	/* Enable Power Control clock */
	__HAL_RCC_PWR_CLK_ENABLE();

	/* The voltage scaling allows optimizing the power consumption when the device is
     clocked below the maximum system frequency, to update the voltage scaling value 
     regarding system frequency refer to product datasheet.  */
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	/* Enable HSE Oscillator and activate PLL with HSE as source */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLM = 8;
	RCC_OscInitStruct.PLL.PLLN = 360;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 7;
	if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		/* Initialization Error */
		errorHandler();
	}

	if(HAL_PWREx_EnableOverDrive() != HAL_OK)
	{
		/* Initialization Error */
		errorHandler();
	}

	/* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
     clocks dividers */
	RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
	if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
	{
		/* Initialization Error */
		errorHandler();
	}
}


#ifdef  USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
	/* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

	/* Infinite loop */
	while (1)
	{
	}
}
#endif

/**
 * @}
 */

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
