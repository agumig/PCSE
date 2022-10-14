/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "API_uart.h"

/*******************************************************************************
 * Function prototypes
 ******************************************************************************/
//static void Error_Handler(void);

/*******************************************************************************
 * Private global variables
 ******************************************************************************/
static UART_HandleTypeDef UartHandle;

/*******************************************************************************
 * Public functions
 ******************************************************************************/

/**
 * @brief	UART Initialization
 * @details
 * @param	none
 * @return	true if the initialization was success, false if not
 */
bool_t uartInit(void)
{
	bool_t returnValue = false;

	  /* UART configured as follows:
	      - Word Length = 8 Bits (7 data bit + 1 parity bit) :
		                  BE CAREFUL : Program 7 data bits + 1 parity bit in PC HyperTerminal
	      - Stop Bit    = One Stop bit
	      - Parity      = ODD parity
	      - BaudRate    = 9600 baud
	      - Hardware flow control disabled (RTS and CTS signals) */
	  UartHandle.Instance        = USARTx;

	  UartHandle.Init.BaudRate   = 9600;
	  UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
	  UartHandle.Init.StopBits   = UART_STOPBITS_1;
	  UartHandle.Init.Parity     = UART_PARITY_ODD;
	  UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
	  UartHandle.Init.Mode       = UART_MODE_TX_RX;
	  UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;
	  if (HAL_UART_Init(&UartHandle) == HAL_OK)
	  {
		  uartSendString((uint8_t*)"Initialization finished successfully\n");

		  returnValue = true;
	  }

	  return returnValue;
}

/**
 * @brief	UART Send function
 * @details	Send all the string
 * @param	uint8_t * string to send
 * @return	none
 */
void uartSendString(uint8_t * pstring)
{
	if(NULL != pstring)
		HAL_UART_Transmit(&UartHandle, pstring, strlen((const char *)pstring), UART_TRANSMIT_MAX_DELAY);

}

/**
 * @brief	UART Send function
 * @details	Send a part selected of the string
 * @param	uint8_t * 	string to send
 * @param	uint16_t	size of bytes to send
 * @return	none
 */
void uartSendStringSize(uint8_t * pstring, uint16_t size)
{
	if((NULL != pstring) && (strlen((const char *)pstring) >= size))
		  HAL_UART_Transmit(&UartHandle, pstring, size, UART_TRANSMIT_MAX_DELAY);
}

/**
 * @brief	UART receive function
 * @details	REceive a part selected of the data
 * @param	uint8_t * 	string to save data
 * @param	uint16_t	size of bytes to receive
 * @return	none
 */
void uartReceiveStringSize(uint8_t * pstring, uint16_t size)
{
	if(NULL != pstring)
	{
		HAL_UART_Receive(&UartHandle, pstring, size, UART_RECEIVE_MAX_DELAY);
	}
}

/*******************************************************************************
 * Private functions
 ******************************************************************************/

