#include <gui/screen3_screen/Screen3View.hpp>

/*
 * USER LIBRARIES BEGIN
 */

#include "stm32f4xx_hal.h"
#include <string.h>

/*
 * USER LIBRARIES END
 */

/*
 *	Variables taken from main.c file BEGIN
 */

extern UART_HandleTypeDef huart6;
extern char *TxBuffer;
extern uint16_t len_of_data;
extern char RxBuffer[10];
extern lft_flags lftflg;

/*
 *	Variables taken from main.c file END
 */

Screen3View::Screen3View()
{

}

void Screen3View::setupScreen()
{
    Screen3ViewBase::setupScreen();
}

void Screen3View::tearDownScreen()
{
    Screen3ViewBase::tearDownScreen();
}

/*********************************************************************
 * @fn      		  - handleTickEvent
 *
 * @brief             - This function allows data from USART6 to be printed on the TFT screen.
 *
 * @param[in]         - none
 *
 * @return            - none
 *
 * @Note              - This function is called on every clock
 */

void Screen3View::handleTickEvent(){
	// Check the status of the USART6 interrupt
	if(lftflg.uart6_rx_flag == 1){
		// Data from USART6 is copied to textArea2Buffer array
		Unicode::strncpy(textArea2Buffer, RxBuffer, strlen(RxBuffer));

		// The textArea2Buffer array is printed to the textArea2 section on the screen
		Unicode::snprintf(textArea2Buffer, TEXTAREA2_SIZE, "%s", textArea2Buffer);

		// initialize textArea2
		textArea2.invalidate();

		// Send data from USART6 back to USART6
		HAL_UART_Transmit(&huart6, (uint8_t*)RxBuffer, 10, HAL_MAX_DELAY);

		// Reset USART6 interrupt flag
		lftflg.uart6_rx_flag = 0;
	}
}

/*********************************************************************
 * @fn      		  - sendHello
 *
 * @brief             - This function is called when the "Send "Hello"" button on the screen is pressed.
 * @brief             - This function transmits TxBuffer from USART6.
 *
 * @param[in]         - none
 *
 * @return            - none
 *
 * @Note              - none
 */

void Screen3View::sendHello(){
	// Calculate TxBuffer length
	len_of_data = strlen(TxBuffer);

	// Send TxBuffer array from USART6
	HAL_UART_Transmit(&huart6, (uint8_t*)TxBuffer, len_of_data, HAL_MAX_DELAY);
}
