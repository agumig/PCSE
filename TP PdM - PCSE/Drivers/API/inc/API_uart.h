#ifndef _API_UART_H__
#define _API_UART_H__

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "main.h"
#include "string.h"

/*******************************************************************************
 * Defines
 ******************************************************************************/
#define UART_TRANSMIT_MAX_DELAY	100
#define UART_RECEIVE_MAX_DELAY	100

typedef bool bool_t;

/*******************************************************************************
 * Function prototypes
 ******************************************************************************/
bool_t uartInit();
void uartSendString(uint8_t * pstring);
void uartSendStringSize(uint8_t * pstring, uint16_t size);
void uartReceiveStringSize(uint8_t * pstring, uint16_t size);


#endif
