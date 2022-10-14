/**
  ******************************************************************************
  * @file    TP PdM - PCSE/Inc/hw_hx711.h
  * @brief   Header for hw_hx711..c module
  ******************************************************************************
*/
#ifndef __HW_HX711_H__
#define __HW_HX711_H__

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "main.h"

/*******************************************************************************
 * Typedef
 ******************************************************************************/
/**
 * eGAIN_128 corresponds to Channel A
 * eGAIN_32 corresponds to Channel B
 * eGAIN_64 corresponds to Channel A
*/
typedef enum HX711_GAIN
{
	eGAIN_128 = 1,		// 1 pulse after LSB (pulse number 25 of CLK)
	eGAIN_32 = 2,		// 2 pulse after LSB (pulse number 26 of CLK)
	eGAIN_64 = 3,		// 3 pulse after LSB (pulse number 27 of CLK)
}HX711_GAIN;

typedef bool bool_t;
/*******************************************************************************
 * Defines
 ******************************************************************************/

#define HX711_ADC_PRECISION			24			// Bits of precision - From datasheet

#define OUTPUT_SETTLING_TIME		400			//[ms]time from power up, reset, input channel change and gain change to valid stable output data.
#define OUTPUT_DATA_RATE			10			//[hz]

#define ADC_MIN_SATURATION			0xFF800000	// Output data saturation value (MIN) - From datasheet
#define ADC_MAX_SATURATION			0x007FFFFF	// Output data saturation value (MAX) - From datasheet

#define POSITIVE_MASK_32_T			0x00FFFFFF	// 32 bits
#define NEGATIVE_MASK_32_T			0xFF000000	// 32 bits

#define HX711_ZERO_OFFSET   		0
#define HX711_REAL_OFFSET			0xFF802bcf

#define BIT_MGR_CONVERTION			0.010448447				//[g/counts]

#define HX711_SCALE_GR         		1						// [g] = 1 [kg] = 1000
#define HX711_SCALE_KG         		(1000 * HX711_SCALE_GR)	// [g] = 1 [kg] = 1000

#define HX711_SCALE					HX711_SCALE_GR

#define CLOCK_DELAY_US      		1		// [us] MIN 0.1  TYP 1 MAX 50 - From datasheet
#define CLOCK_POWER_DOWN_DELAY_US 	60		// [us] Time to stay high to turn off - From datasheet

#define WAIT_FOR_READY_DELAY		10		// [ms] Time to wait for chip ready
#define MAX_WAITING_FOR_READY		1000		// [ms] Maximun time waiting for ready

#define MAX_TIMES_ALLOWED			10		// How many reading are allowed
#define READINGS_TO_GET_TARE		10		// How many readings to do

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

void HX711_init(void);
void HX711_initCalibrationZero(void);
void HX711_readZero(uint8_t times);
void HX711_setGain(HX711_GAIN);
HX711_GAIN HX711_getGain(void);
void HX711_setScale(float scale);
float HX711_getScale();
void HX711_setOffset(int32_t offset);
int32_t HX711_getOffset();
uint32_t HX711_readCounts(uint8_t times);
double HX711_readWeigh(uint8_t times);
void HX711_powerDown();
void HX711_powerUp();


#endif
