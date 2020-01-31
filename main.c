/*
 * ECE 153B - Winter 2020
 *
 * Name(s):
 * Section:
 * Lab: 1C
 */

#include "stm32l476xx.h"
#include "LED.h"
#include "SysTimer.h"

void System_Clock_Init(void) {
	// Select MSI as system clock source
	RCC->CFGR |= RCC_CFGR_SW_MSI; // Replace with value that will make MSI the system clock source
	
	// Set MSI clock range
	RCC->CR &= ~RCC_CR_MSIRANGE;
	RCC->CR |= RCC_CR_MSIRANGE_7; // TODO - Replace with value that will make range 8 MHz ...already done 
	
	// Use the MSI clock range that is defined in RCC_CR
	RCC->CR |= RCC_CR_MSIRGSEL; // TODO - Replace with value that will select range in RCC->CR
	
	// Enable MSI oscillator
	RCC->CR |= RCC_CR_MSION; // Replace with value that will enable MSI
	
	// Wait until MSI is ready
	while((RCC->CR & RCC_CR_MSIRDY /* Replace with value that checks whether MSI is ready */) == 0);
}

int main() {
	// Initialization 
	System_Clock_Init();
	SysTick_Init();
	LED_Init();
	


	//Enable the clock of the PB6 
	RCC ->AHB2ENR =| RCC_AHB2ENR_GPIOBEN;   
	//set PB6 to alternative function mode (10)
	GPIOB -> MODER &= ~GPIO_MODER_MODE6_0; 
	GPIOB -> MODER |=  GPIO_MODER_MODE6_1;  

	//we are PB6 so we use AFR"L" (0-7) set to alternative function 2 
	GPIOB -> AFRL  |= GPIO_AFRL_AFSEL2;

	//No pull up no pull down (00)
	GPIOB -> PUPDR &= ~GPIO_PUPDR_PUPDR6_0; 
	GPIOB -> PUPDR &= ~GPIO_PUPDR_PUPDR6_1; 

	//enabling timer 4 in regsiter 1
	RCC-> APB1ENR1 |= RCC_APB1ENR1_TIM4EN; 

	//enable auto reload pre load ??
	// set ARR value (to maximum)
	TIM4 -> ARR = 65535;

	//mapping value to TIM1
	//In the capture/compare mode register, set the input capture mode bits such that the input capture is mapped to timer input 1.
    //Note: CC2S bits are writable only when the channel is OFF (CC2E = ‘0’ in TIMx_CCER).
	//01: CC1 channel is configured as input, IC1 is mapped on TI1
	TIM4->CCMR1 |= TIM_CCMR1_CC1S_0;
	TIM4->CCMR1 &= ~TIM_CCMR1_CC1S_1;

	//In the capture/compare enable register, set bits to capture both rising/falling edges and enable capturing.
	//(11) The circuit is sensitive to both TIxFP1 rising and falling edges
	TIM4 -> CCER |= TIM_CCER_CC1NP;
	TIM4 -> CCER |= TIM_CCER_CC1P;
	//enable, 1: Capture enabled.
	TIM4 ->CCER =| TIM_CCER_CC1E;

	while(1) { //Delay for 1 second and toggle red LED every time
		delay(1000);
		Red_LED_Toggle();
	}


}
