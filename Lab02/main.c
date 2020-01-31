/*
 * ECE 153B - Winter 2020
 *
 * Name(s):
 * Section:
 * Lab: 2A
 */

#include "stm32l476xx.h"
 
void PWM_Init() {
	// Enable GPIO Port E Clock
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN;
	
	// Enable TIM1 Clock
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	
	// Configure PE8
	GPIOE->MODER |= GPIO_MODER_MODE8_1;
	GPIOE->MODER &= ~GPIO_MODER_MODE8_0;
	
	GPIOE->OSPEEDR |= GPIO_OSPEEDR_OSPEED8;
	
	GPIOE->PUPDR &= ~GPIO_PUPDR_PUPD8;
	
	GPIOE->AFR[1] &= ~GPIO_AFRH_AFSEL8;
	GPIOE->AFR[1] |= GPIO_AFRH_AFSEL8_0;
	//TODO - Step 6. Configure and Select the Alternative Function for PE8 
	//Do I need one for AFR[0]
	// Configure PWM Output for TIM1 CH 1N
	//TODO
	
	// Setting the timer to count up 
  TIM1->CR1 &= ~TIM_CR1_DIR; 
	
	//Setting Pescalar value 
		//Seting availible register to 0s 
	TIM1->PSC &= ~0xFFFF;
		//Setting to value to 7 (ftimimer = 16Mhz/(1+7))
	TIM1-> PSC = 7;
	
	//Set ARR value 
		//Setting availible register to zero
	TIM1-> ARR &= ~0xFFFF;
		//Setting ARR to 100, a arbitary large value that will give resolution
	TIM1-> ARR = 999;
	
	//Set the clear  the compare mode bits for channel 1 and set the PWM
	TIM1->CCMR1 |= TIM_CCMR1_OC1M;
	// Enabling preload in chanel one compare mode Ref. Man. pg.819
	TIM1 -> CCMR1 |= TIM_CCMR1_OC1PE;
	
	//Set the output polarity for channel 1N to active high (active high = 0)
	TIM1 -> CCER  &=  ~TIM_CCER_CC1NP;
	//enable output for chanel 1N
	TIM1 -> CCER |= TIM_CCER_CC1NE;
	
	//Main output enable
	TIM1 -> BDTR |= TIM_BDTR_MOE;
	
	// Settng CCR
	TIM1 -> CCR1 = 500;
	
	//Counter enable (through control regsiter to enable) 1 to enable 
 	TIM1 -> CR1  |= TIM_CR1_CEN;
}
 
int main() {
	// Initialization - We will use the default 4 MHz clock
	PWM_Init();
	
	// Periodic Dimming
	int i;
	while(1) {
		// TODO (changing duty cycle, etc.)
		
		for(i=0; i<1000; ++i); // Some Delay
	}
	
	return 0;
}
