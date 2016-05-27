#include <stdint.h>
#include <string.h>
#include "nrf.h"
#include "nrf_gpio.h"
#include "nrf_delay.h"
#include "twi_master.h"                 // NordicSemiconductor::nRF_Drivers:twi_master

/*
Slave Address (7bit).
For testing was used Arduino as I2C-slave device.
Arduino's I2C-address = 7 (in DEC) = 0x07 (in HEX) = 0000 0111 (in BIN).
*/
#define TWI_ADDRESS 0x07


int main(void){
	nrf_gpio_cfg_output(0);
	nrf_gpio_cfg_output(1);
	nrf_gpio_cfg_output(2);
	nrf_gpio_pin_clear(0);
	nrf_gpio_pin_clear(1);
	nrf_gpio_pin_clear(2);
	
	
	/*
	Setting for the I2C write.
	We need to shift the device's I2C-address on 1 bit: 0000 0111 -> 0000 1110.
	And set the last bit to 1 (for I2C writing): 0000 1111.
	For the I2C reading we need to set the last bit to 0: 0000 1110.
	*/
	uint8_t addressWrite;
	//addressRead = (TWI_ADDRESS << 1) | 1;   // Read
	addressWrite = (TWI_ADDRESS << 1) | 0;  // Write
	
	
	bool twi_result;
	twi_result = twi_master_init();
	if(!twi_result) nrf_gpio_pin_toggle(2); // Error
	
	
	while(1){
		nrf_delay_ms(1000);
		twi_result = twi_master_transfer(addressWrite, "hohoho!", 7, TWI_ISSUE_STOP); // Write
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

