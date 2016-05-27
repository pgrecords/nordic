#include <stdint.h>
#include <string.h>
#include "nrf.h"
#include "nrf_gpio.h"
#include "nrf_delay.h"
#include "twi_master.h"


/*
Slave Address (7bit).
Sensor's I2C-address = 119 (in DEC) = 0x77 (in HEX) = 0111 0111 (in BIN).
*/
#define TWI_ADDRESS 0x77
uint8_t dataW1[2] = {0xF4, 0x2E};
uint8_t dataW2[1] = {0xF6};
uint8_t dataR[2] = {0x00, 0x00};


int main(void){
	nrf_gpio_cfg_output(0);
	nrf_gpio_cfg_output(1);
	nrf_gpio_cfg_output(2);
	nrf_gpio_pin_clear(0);
	nrf_gpio_pin_clear(1);
	nrf_gpio_pin_clear(2);
	
	
	/*
	Settings for the I2C address.
	We need to shift the device's I2C-address by 1 bit: 0111 0111 -> 1110 1110.
	Set the last bit in 0 for I2C writing: 1110 1111.
	Set the last bit in 1 for I2C reading: 1110 1110.
	*/
	uint8_t addressWrite, addressRead;
	addressRead = (TWI_ADDRESS << 1) | 1;   // Read
	addressWrite = (TWI_ADDRESS << 1) | 0;  // Write
	
	
	bool twi_result;
	twi_result = twi_master_init();
	if(!twi_result) nrf_gpio_pin_toggle(2); // Error
	
	
	while(1){
		nrf_delay_ms(500);
    if(twi_master_transfer(addressWrite, dataW1, 2, TWI_DONT_ISSUE_STOP)){
			if(twi_master_transfer(addressWrite, dataW2, 1, TWI_DONT_ISSUE_STOP)){
				// Read requested bytes and finish I2C-transaction.
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

