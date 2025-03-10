/*
 * tempSensor_LM35.c
 *
 *  Created on: 3 Jun 2024
 *      Author: ahmed
 */
#include "adc.h"
#include "tempSensor_LM35.h"
#define SENSOR_MAX_TEMP (150u)
#define SENSOR_MAX_VOLT (1.5)

/* Description:
 * Read ADC channel where the temperature sensor is connected
 * Do MATH
 * Return the tempValue
 */
#ifdef ADC_POLLING_MODE
uint8 TEMPSENSOR_LM35_getTemp(ADC_ConfigType* Config_ptr, ADC_SelectedChannel a_tempSensorChannel)
{

	/*Stores the temp value that we measured*/
	uint8 tempValue = 0;
	/*stores the adc value of the sensor that was read*/
	uint16 adcValue = 0;

	ADC_init(Config_ptr);


	/* Read ADC channel where the temperature sensor is connected */
	adcValue = ADC_readChannel(a_tempSensorChannel);

	/* Multiply the adcValue to (ADC volt Ref) and divide the result by 1023 to get the input volt
	 * then multiply the input voltage to sensor max temp and divide the result by max sensor volt
	 * to get the sensed Temperature
	 */
	tempValue = (uint8)(((uint32)adcValue * ADC_VOLT_REF_VALUE * SENSOR_MAX_TEMP) / (ADC_MAX_OUTPUT_VALUE * SENSOR_MAX_VOLT));
	return tempValue;
}
#endif /*ADC_POLLING_MODE*/

#ifdef ADC_INTERRUPT_MODE
void TEMPSENSOR_LM35_getTemp(ADC_ConfigType* Config_ptr, ADC_SelectedChannel a_tempSensorChannel)
{
	ADC_init(Config_ptr);

	/* Read ADC channel where the temperature sensor is connected */
	ADC_readChannel(a_tempSensorChannel);

	/*Equation for the ISR*/
	/* Multiply the adcValue to (ADC volt Ref) and divide the result by 1023 to get the input volt
	 * then multiply the input voltage to sensor max temp and divide the result by max sensor volt
	 * to get the sensed Temperature
	 */
	 /* tempValue = (uint8)(((uint32)adcValue * ADC_VOLT_REF_VALUE * SENSOR_MAX_TEMP) / (ADC_MAX_OUTPUT_VALUE * SENSOR_MAX_VOLT));
	 */
}
#endif /*ADC_INTERRUPT_MODE*/
