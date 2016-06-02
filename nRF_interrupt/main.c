#include <stdbool.h>
#include "nrf.h"
#include "nrf_gpio.h"


bool state = 0;
uint16_t i = 0;


void GPIOTE_IRQHandler(void){
	if(NRF_GPIOTE->EVENTS_IN[0] == 1) NRF_GPIOTE->EVENTS_IN[0] = 0;   // Clear every interrupt-event
	nrf_gpio_pin_toggle(29);																					// Toogle LED on every interrupt
	state = !state;																										// Inverting variable (only for indication)
	++i;																															// Incrementing variable (only for indication)
}


int main(void){
	nrf_gpio_cfg_input(1, NRF_GPIO_PIN_PULLUP);
	nrf_gpio_cfg_output(29);
	NVIC_EnableIRQ(GPIOTE_IRQn);
	NRF_GPIOTE->CONFIG[0] =  (GPIOTE_CONFIG_POLARITY_HiToLo << GPIOTE_CONFIG_POLARITY_Pos)
                   | (1 << GPIOTE_CONFIG_PSEL_Pos)
                   | (GPIOTE_CONFIG_MODE_Event << GPIOTE_CONFIG_MODE_Pos);
	NRF_GPIOTE->INTENSET = GPIOTE_INTENSET_IN0_Enabled << GPIOTE_INTENSET_IN0_Pos;
	
	while(1){
		
	}
}
