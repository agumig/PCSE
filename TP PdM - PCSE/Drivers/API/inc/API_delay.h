#ifndef __API_DELAY_H_
#define __API_DELAY_H_

/*******************************************************************************
 * Defines
 ******************************************************************************/
/* Delay values*/
#define MAX_DELAY		30000	//	[ms] max time accepted for delay

/*******************************************************************************
 * Typedef
 ******************************************************************************/
/* Delay variables */
typedef uint32_t tick_t;
typedef bool bool_t;

typedef struct{
   tick_t startTime;
   tick_t duration;
   bool_t running;
}delay_t;

/*******************************************************************************
 * Functions prototypes
 ******************************************************************************/

void delayInit( delay_t * delay, tick_t duration );
bool_t delayRead( delay_t * delay );
void delayWrite( delay_t * delay, tick_t duration );

#endif
