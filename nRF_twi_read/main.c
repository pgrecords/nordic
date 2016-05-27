#include <stdint.h>
#include <string.h>
#include "nrf.h"
#include "nrf_gpio.h"
#include "nrf_delay.h"
#include "twi_master.h"


#define TWI_ADDRESS 0x77 /* Slave Address  (7bit) */
uint8_t dataW[2] = {0xF4, 0x2E};
uint8_t dataWW[1] = {0xF6};
uint8_t dataR[2] = {0x00, 0x00};


int main(void){
	nrf_gpio_cfg_output(0);
	nrf_gpio_cfg_output(1);
	nrf_gpio_cfg_output(2);
	nrf_gpio_pin_clear(0);
	nrf_gpio_pin_clear(1);
	nrf_gpio_pin_clear(2);
	
	
	uint8_t addressWrite, addressRead;
	addressRead = (TWI_ADDRESS << 1) | 1;   // Read
	addressWrite = (TWI_ADDRESS << 1) | 0;  // Write
	
	
	bool twi_result;
	twi_result = twi_master_init();
	if(!twi_result) nrf_gpio_pin_toggle(2); // Error
	
	
	//temp_read(&a, &b);
	//twi_master_transfer(address, uint8_t * data, uint8_t   data_length, bool      issue_stop_condition)
	
	
	while(1){
		nrf_delay_ms(500);
    if(twi_master_transfer(addressWrite, dataW, 2, TWI_DONT_ISSUE_STOP)){
			if(twi_master_transfer(addressWrite, dataWW, 1, TWI_DONT_ISSUE_STOP)){
        // read bytes and finish transaction
        twi_result = twi_master_transfer(addressRead, dataR, 2, TWI_ISSUE_STOP);
			}
    }
		
		if (!twi_result){
			// Error
			nrf_gpio_pin_set(1);
			nrf_delay_ms(200);
			nrf_gpio_pin_clear(1);
			nrf_delay_ms(200);
			nrf_gpio_pin_set(1);
			nrf_delay_ms(200);
			nrf_gpio_pin_clear(1);
			nrf_delay_ms(200);
			nrf_gpio_pin_set(1);
			nrf_delay_ms(200);
			nrf_gpio_pin_clear(1);
			nrf_delay_ms(200);
		}
		else nrf_gpio_pin_toggle(0);
	}
}

