#include <gui/screen2_screen/Screen2View.hpp>

#include "stm32f4xx_hal.h"
#include <string.h>

Screen2View::Screen2View()
{

}

void Screen2View::setupScreen()
{
    Screen2ViewBase::setupScreen();
}

void Screen2View::tearDownScreen()
{
    Screen2ViewBase::tearDownScreen();
}

void Screen2View::ToToggleLed(){
	if(toggleButton1.getState()){
		HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_5);
	}
	else{
		HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_5);
	}

}

void Screen2View::ToggleLED4(){
	if(toggleButton1.getState()){
		HAL_GPIO_TogglePin(GPIOK, GPIO_PIN_3);
	}
	else{
		HAL_GPIO_TogglePin(GPIOK, GPIO_PIN_3);
	}

}
