# nRF51x22 (I2C/TWI Read)
Example for the Nordic nRF51822 (I2C/TWI Read). The code was compiled into the Keil.<br/><br/>

This code show how to request the temperature from the sensor Bosch BMP180.<br/>
1. Sensor's address is 0x77 (0111 0111 in binary). For writing data to the sensor we need to shift the address by one bit and to set the last bit in 0. Result = 1110 1110.
2. Next we need to write two bytes into the sensor: 0xF4 and 0x2E.
3. Write one byte into the sensor: 0xF6.
4. Read the returned data (two bytes).
5. Calculating the data and converting to Celsius.