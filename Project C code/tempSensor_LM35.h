/*
 * tempSensor_LM35.h
 *
 *  Created on: 3 Jun 2024
 *      Author: ahmed
 */

/* A 3 terminal device that provide analog Voltage proportional to Temperature.
 * the higher the Temperature, the higher the Voltage
 * can measure temperature in range of -55C to 150C
 * The sensitivity of LM35 is 10mV per Celsius degree
 * So if Temperature = 27 then sensor output = 270mV.
 *
 */

#ifndef TEMPSENSOR_LM35_H_
#define TEMPSENSOR_LM35_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define SENSOR_LM35_CHANNEL_ID 			ADC_CHANNEL_2
#define SENSOR_MAX_TEMP (150u)
#define SENSOR_MAX_VOLT (1.5)

#define ADC_POLLING_MODE
//#define ADC_INTERRUPT_MODE

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/* Description:
 * Read ADC channel where the temperature sensor is connected
 * Do MATH
 * Return the tempValue
 */
#ifdef ADC_POLLING_MODE
uint8 TEMPSENSOR_LM35_getTemp(ADC_ConfigType* Config_ptr, ADC_SelectedChannel a_tempSensorChannel);
#endif /*ADC_POLLING_MODE*/

#ifdef ADC_INTERRUPT_MODE
void TEMPSENSOR_LM35_getTemp(ADC_ConfigType* Config_ptr, ADC_SelectedChannel a_tempSensorChannel);
#endif /*ADC_INTERRUPT_MODE*/

#endif /* TEMPSENSOR_LM35_H_ */
