#include <gui/screen2_screen/Screen2View.hpp>

/*
 * USER LIBRARIES BEGIN
 */

#include "stm32f4xx_hal.h"
#include <string.h>

/*
 * USER LIBRARIES END
 */


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

/*********************************************************************
 * @fn      		  - ToToggleLed
 *
 * @brief             - This function is called when the "LED3" button on the screen is pressed.
 * @brief             - This function toggles LED3.
 *
 * @param[in]         - none
 *
 * @return            - none
 *
 * @Note              - none
 */

void Screen2View::ToToggleLed(){
	// When LED3 toggle button states is on
	if(toggleButton1.getState()){
		// Toggle LED3
		HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_5);
	}

	// When LED3 toggle button states is off
	else{
		// Toggle LED3
		HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_5);
	}
}

/*********************************************************************
 * @fn      		  - ToggleLED4
 *
 * @brief             - This function is called when the "LED4" button on the screen is pressed.
 * @brief             - This function toggles LED4.
 *
 * @param[in]         - none
 *
 * @return            - none
 *
 * @Note              - none
 */

void Screen2View::ToggleLED4(){
	// When LED4 toggle button states is on
	if(toggleButton1.getState()){
		// Toggle LED4
		HAL_GPIO_TogglePin(GPIOK, GPIO_PIN_3);
	}

	// When LED4 toggle button states is off
	else{
		// Toggle LED4
		HAL_GPIO_TogglePin(GPIOK, GPIO_PIN_3);
	}
}
