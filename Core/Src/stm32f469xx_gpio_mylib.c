/*
 * stm32f469xx_gpio_mylib.c
 *
 */

#include "stm32f469xx_gpio_mylib.h"

/*
 * Peripheral clock setup
 */

void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIO, uint8_t EnorDi){
	if(EnorDi == ENABLE){
		if(pGPIO == GPIOA){
			GPIOA_PCLK_EN();
		}
		else if(pGPIO == GPIOB){
			GPIOB_PCLK_EN();
		}
		else if(pGPIO == GPIOC){
			GPIOC_PCLK_EN();
		}
		else if(pGPIO == GPIOD){
			GPIOD_PCLK_EN();
		}
		else if(pGPIO == GPIOE){
			GPIOE_PCLK_EN();
		}
		else if(pGPIO == GPIOF){
			GPIOF_PCLK_EN();
		}
		else if(pGPIO == GPIOG){
			GPIOG_PCLK_EN();
		}
		else if(pGPIO == GPIOH){
			GPIOH_PCLK_EN();
		}
		else if(pGPIO == GPIOI){
			GPIOI_PCLK_EN();
		}
		else if(pGPIO == GPIOJ){
			GPIOJ_PCLK_EN();
		}
		else if(pGPIO == GPIOK){
			GPIOK_PCLK_EN();
		}
	}
	else{
		if(pGPIO == GPIOA){
			GPIOA_PCLK_DI();
		}
		else if(pGPIO == GPIOB){
			GPIOB_PCLK_DI();
		}
		else if(pGPIO == GPIOC){
			GPIOC_PCLK_DI();
		}
		else if(pGPIO == GPIOD){
			GPIOD_PCLK_DI();
		}
		else if(pGPIO == GPIOE){
			GPIOE_PCLK_DI();
		}
		else if(pGPIO == GPIOF){
			GPIOF_PCLK_DI();
		}
		else if(pGPIO == GPIOG){
			GPIOG_PCLK_DI();
		}
		else if(pGPIO == GPIOH){
			GPIOH_PCLK_DI();
		}
		else if(pGPIO == GPIOI){
			GPIOI_PCLK_DI();
		}
		else if(pGPIO == GPIOJ){
			GPIOJ_PCLK_DI();
		}
		else if(pGPIO == GPIOK){
			GPIOK_PCLK_DI();
		}
	}
}

/*
 * Init and De-Init
 */

void GPIO_Init(GPIO_Handle_t *pGPIOHandle){
	uint32_t temp=0;

	GPIO_PeriClockControl(pGPIOHandle->pGPIOx, ENABLE);

	//1.configure mode
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG){
		temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
		pGPIOHandle->pGPIOx->MODER &= ~(3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
		pGPIOHandle->pGPIOx->MODER |= temp;
		temp = 0;
	}
	else{
		if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT){
			EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			EXTI->RTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}
		else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT){
			EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			EXTI->FTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}
		else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT){
			EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}

		uint8_t temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 4;
		uint8_t temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 4;
		uint8_t portcode = GPIO_BASEADDR_TO_CODE(pGPIOHandle->pGPIOx);
		SYSCFG_PCLK_EN();
		SYSCFG->EXTICR[temp1] = (portcode << (temp2 * 4));

		EXTI->IMR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	}
	temp = 0;

	//2.configure speed
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->OSPEEDR &= ~(3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->OSPEEDR |= temp;

	temp = 0;

	//3.configure pupd
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->PUPDR &= ~(3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->PUPDR |= temp;

	temp = 0;

	//4.configure optype
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->OTYPER &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandle->pGPIOx->OTYPER |= temp;

	temp = 0;

	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN){
		uint8_t temp1 ,temp2;
		temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8;
		temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8;
		pGPIOHandle->pGPIOx->AFR[temp1] &= ~(0xF << (4 * temp2));
		pGPIOHandle->pGPIOx->AFR[temp1] |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << (4 * temp2));
	}

}

void GPIO_DeInit(GPIO_RegDef_t *pGPIO){
	if(pGPIO == GPIOA){
		GPIOA_REG_RESET();
	}
	else if(pGPIO == GPIOB){
		GPIOB_REG_RESET();
	}
	else if(pGPIO == GPIOC){
		GPIOC_REG_RESET();
	}
	else if(pGPIO == GPIOD){
		GPIOD_REG_RESET();
	}
	else if(pGPIO == GPIOE){
		GPIOE_REG_RESET();
	}
	else if(pGPIO == GPIOF){
		GPIOF_REG_RESET();
	}
	else if(pGPIO == GPIOG){
		GPIOG_REG_RESET();
	}
	else if(pGPIO == GPIOH){
		GPIOH_REG_RESET();
	}
	else if(pGPIO == GPIOI){
		GPIOI_REG_RESET();
	}
	else if(pGPIO == GPIOJ){
		GPIOJ_REG_RESET();
	}
	else if(pGPIO == GPIOK){
		GPIOK_REG_RESET();
	}
}

/*
 * Data read and write
 */

uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber){
	uint8_t value;
	value = (uint8_t) ((pGPIOx->IDR >> PinNumber) & 0x00000001);
	return value;
}

uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx){
	uint16_t value;
	value = (uint16_t) (pGPIOx->IDR);
	return value;
}

void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value){
	if(Value == GPIO_PIN_SET){
		pGPIOx->ODR |= (1 << PinNumber);
	}
	else{
		pGPIOx->ODR &= ~(1 << PinNumber);
	}
}

void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value){
	pGPIOx->ODR = Value;
}

void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber){
	pGPIOx->ODR ^= (1 << PinNumber);
}

/*
 * IRQ Configuration and ISR handling
 */

void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi){
	if(EnorDi == ENABLE){
		if(IRQNumber <= 31){
			*NVIC_ISER0 |= (1 << IRQNumber);
		}
		else if(IRQNumber > 31 && IRQNumber < 64){
			*NVIC_ISER1 |= (1 << (IRQNumber % 32));
		}
		else if(IRQNumber >= 64 && IRQNumber < 96){
			*NVIC_ISER3 |= (1 << (IRQNumber % 64));
		}
	}
	else{
		if(IRQNumber <= 31){
			*NVIC_ICER0 |= (1 << IRQNumber);
		}
		else if(IRQNumber > 31 && IRQNumber < 64){
			*NVIC_ICER1 |= (1 << (IRQNumber % 32));
		}
		else if(IRQNumber >= 64 && IRQNumber < 96){
			*NVIC_ICER3 |= (1 << (IRQNumber % 64));
		}
	}
}

void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority){
	uint8_t iprx = IRQNumber / 4;
	uint8_t iprx_section = IRQNumber % 4;
	uint8_t shift_amount = (iprx_section * 8) + (8 - NO_PR_BITS_IMPLEMENTED);
	*(NVIC_PR_BASE_ADDR + iprx) |= (IRQPriority << shift_amount);
}

void GPIO_IRQHandling(uint8_t PinNumber){
	if(EXTI->PR & (1 << PinNumber)){
		EXTI->PR |= (1 << PinNumber);
	}
}
