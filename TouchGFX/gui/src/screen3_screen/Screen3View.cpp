#include <gui/screen3_screen/Screen3View.hpp>

#include "stm32f4xx_hal.h"
#include <string.h>

extern UART_HandleTypeDef huart6;
extern char *TxBuffer;
extern uint16_t len_of_data;
extern char RxBuffer[10];
extern lft_flags lftflg;

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

void Screen3View::handleTickEvent(){
	if(lftflg.uart6_rx_flag == 1){
		Unicode::strncpy(textArea2Buffer, RxBuffer, strlen(RxBuffer));
		Unicode::snprintf(textArea2Buffer, TEXTAREA2_SIZE, "%s", textArea2Buffer);
		textArea2.invalidate();
		HAL_UART_Transmit(&huart6, (uint8_t*)RxBuffer, 10, HAL_MAX_DELAY);
		lftflg.uart6_rx_flag = 0;
	}
}

void Screen3View::sendHello(){
	len_of_data = strlen(TxBuffer);
	HAL_UART_Transmit(&huart6, (uint8_t*)TxBuffer, len_of_data, HAL_MAX_DELAY);
}
