/******************************************************************************
 *
 * Project: Fan control using temperature sensor LM35
 *
 * File Name: app.c
 *
 * Description:  In this project, the LM35 temperature sensor will give continuous analog output
 * corresponding to the temperature sensed by it. This analog signal is given to the ADC,
 * which converts the analog values to digital values.
 *
 * Author: Abdelrahman Saeed
 *
 *******************************************************************************/

#include "lcd.h" /* to use the LCD module */
#include "dc_motor.h" /* to us the DC Motor module */
#include "adc.h" /* to use the ADC module */
#include "lm35_sensor.h" /* to use the LM35 sensor module */

int main(void) {

	/*
	 * configure the ADC to work with internal reference voltage
	 * and pre-scaler equals to 8
	 */
	ADC_ConfigType configType = { INTERNAL, PRESCALER_8 };

	/*
	 * initialize the modules used in the system
	 */
	LCD_init();
	DcMotor_init();
	ADC_init(&configType);

	/*
	 * variable used to store the reading of the LM35 sensor
	 */
	uint8 temperature;

	/*
	 * display the state of the fan
	 * and the temperature on the LCD
	 */
	LCD_moveCursor(0, 3);
	LCD_displayString("Fan is ");

	LCD_moveCursor(1, 3);
	LCD_displayString("Temp =    C");

	while (1) {
		/*
		 * get the reading of the LM35 sensor
		 */
		temperature = LM35_getTemperature();

		LCD_moveCursor(1, 10);
		if (temperature >= 100) {
			LCD_intgerToString(temperature);
		} else {
			LCD_intgerToString(temperature);
			LCD_displayCharacter(' ');
		}

		LCD_moveCursor(0, 11);

		/*
		 * control the fan according the the temperature obtained
		 * from the LM35 sensor
		 */
		if (temperature < 30) {
			LCD_displayString("OFF");
			/*
			 * turn off the fan
			 */
			DcMotor_rotate(STOP, 0);
		} else {
			LCD_displayString("ON ");
			if (temperature >= 30 && temperature < 60) {
				/*
				 * turn on the fan with only 25% of its max speed
				 * with clockwise
				 */
				DcMotor_rotate(CLOCKWISE, 25);
			} else if (temperature >= 60 && temperature < 90) {
				/*
				 * turn on the fan with only 50% of its max speed
				 * with clockwise
				 */
				DcMotor_rotate(CLOCKWISE, 50);
			} else if (temperature >= 90 && temperature < 120) {
				/*
				 * turn on the fan with only 75% of its max speed
				 * with clockwise
				 */
				DcMotor_rotate(CLOCKWISE, 75);
			} else {
				/*
				 * turn on the fan with max speed
				 * with clockwise
				 */
				DcMotor_rotate(CLOCKWISE, 100);
			}
		}
	}

	return 0;
}

