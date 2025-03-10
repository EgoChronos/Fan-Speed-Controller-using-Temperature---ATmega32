/*
 * adc..c
 *
 *  Created on: 3 Jun 2024
 *      Author: ahmed
 */
#include <avr/io.h>
#include <avr/delay.h>
#include"gpio.h"
#include "adc.h"
#include <avr/interrupt.h>

/*******************************************************************************
 *                              Private Global Variables                            *
 *******************************************************************************/
#ifdef ADC_INTERRUPT_MODE
/*pointer of the call back fcn for the ISR to use*/
static volatile void (*g_ADC_callBackFcn_ptr)(void) = NULL_PTR;
#endif /*ADC_INTERRUPT_MODE*/

/*******************************************************************************
 *                              Functions Definition                           *
 *******************************************************************************/

/*Description
 * Initialise the ADC by:
 * 1.Choosing the REF
 * 2.Clearing Channel selecting bits
 * 3.Make the result LEFT adjusted or leave it to remain RIGHT adjusted
 * 4.Choose AUTO TRIGGER MODE or remain Single conversion mode
 * 5.Set up interrupt mode if configured
 * 6.choose pre-scaler as configured
 */
void ADC_init(ADC_ConfigType* Config_ptr)
{

/*Reference Selection Bits  AVCC, AREF or internal 2.65V*/
if (Config_ptr->adcRefSource == ADC_REF_AREF)
{
	CLEAR_BIT(ADMUX, REFS0);
	CLEAR_BIT(ADMUX, REFS1);
}
else if (Config_ptr->adcRefSource == ADC_REF_AVCC)
{
	SET_BIT(ADMUX,REFS0);
	CLEAR_BIT(ADMUX,REFS1);
}
else if (Config_ptr->adcRefSource == ADC_REF_INTERNAL_REF)
{
	SET_BIT(ADMUX,REFS0);
	SET_BIT(ADMUX,REFS1);
}

	/*Clear all bits of Selecting channel by setting channel 0*/
	ADMUX = (ADMUX & 0xE0) | (ADC_CHANNEL_0 & (0x1F));

	/*Clear the ADLAR bit to make the result right adjusted as default
	 * Set the ADLAR to left adjust the result if needed*/
	CLEAR_BIT(ADMUX, ADLAR);

#ifdef ADC_LEFT_ADJUST_RESULT
	SET_BIT(ADMUX, ADLAR);
#endif

if (Config_ptr->autoTriggerState == ADC_AUTO_TRIGGER_ON)
{
	/*ADC Auto Trigger Enable by setting ADATE bit*/
	SET_BIT(ADCSRA, ADATE);
	/*determine the ADC Auto Trigger Source*/
	SFIOR = (SFIOR & 0x1F) | ((Config_ptr->autoTriggersource << 5) & 0xE0);
}
else
{
	/*ADC Auto Trigger Disable by clearing ADATE bit*/
	CLEAR_BIT(ADCSRA, ADATE);
	/*Clear all bits of autoTriggerSourceSelection*/
	SFIOR &= 0x1F;
}

#ifdef ADC_INTERRUPT_MODE
/*Set ADC Interrupt Enable*/
SET_BIT(ADCSRA, ADIE);
#endif /*ADC_INTERRUPT_MODE*/

/*ADC Pre-scaler Select Bits*/
ADCSRA = (ADCSRA & 0xF8) | (Config_ptr->prescalerSelection & 0x07);
}

/*Description
 * Read the selected channel and return the 10 bits that represent it:
 * 1. Make ADC disables to choose a new channel
 * 2. Make the channel pin as input and choose a new channel
 * 3. make ADC enable
 * 4. start ADC conversion
 * 5.wait until the flag of complete conversion is raised
 * 6.Clear the flag of complete conversion
 * 7.return result
 */
#ifdef ADC_POLLING_MODE
uint16 ADC_readChannel(ADC_SelectedChannel a_channel)
{

	/*Make ADC disabled by clearing ADEN bit to setup a new channel*/
	CLEAR_BIT(ADCSRA, ADEN);

	/*setup selected channel as input*/
	GPIO_setupPinDirection(ADC_CHANNEL_PORT, a_channel, PIN_INPUT);

	/*Setup Selected channel for ADC*/
	ADMUX = (ADMUX & 0xE0) | (a_channel & (0x1F));

	/*Make ADC enable by setting ADEN bit*/
	SET_BIT(ADCSRA, ADEN);

	/*ADC start conversion by setting ADSC bit*/
	SET_BIT(ADCSRA, ADSC);


	/*Check ADC Interrupt Flag loop until the conversion completes*/
	while (BIT_IS_CLEAR(ADCSRA, ADIF));

	/* Clear ADIF by write '1' to it :) */
	SET_BIT(ADCSRA,ADIF);
	_delay_ms(1);
	return ADC;
}
#endif /*ADC_POLLING_MODE*/

#ifdef ADC_INTERRUPT_MODE
/*Description
 * Read the selected channel and return the 10 bits that represent it:
 * 1. Make ADC disables to choose a new channel
 * 2. Make the channel pin as input and choose a new channel
 * 3. make ADC enable
 * 4. start ADC conversion
 * 5. return
 */
void ADC_readChannel(ADC_SelectedChannel a_channel)
{

	/*Make ADC disabled by clearing ADEN bit to setup a new channel*/
	CLEAR_BIT(ADCSRA, ADEN);

	/*setup selected channel as input*/
	GPIO_setupPinDirection(ADC_CHANNEL_PORT, a_channel, PIN_INPUT);

	/*Setup Selected channel for ADC*/
	ADMUX = (ADMUX & 0xE0) | (a_channel & (0x1F));

	/*Make ADC enable by setting ADEN bit*/
	SET_BIT(ADCSRA, ADEN);

	/*ADC start conversion by setting ADSC bit*/
	SET_BIT(ADCSRA, ADSC);
}

/* Description:
 * call the callback fcn that was given to it*/
ISR(ADC_vect)
{
	(g_ADC_callBackFcn_ptr)();
}

/*Description
 * Give the ISR the address of the call back fcn*/
void ADC_setCallBackFcn(void (*ptr2fcn)(void))
{
	g_ADC_callBackFcn_ptr = ptr2fcn;
}
#endif /*ADC_INTERRUPT_MODE*/
