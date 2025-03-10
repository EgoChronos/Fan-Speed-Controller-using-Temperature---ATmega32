/*
 * adc.h
 *
 *  Created on: 3 Jun 2024
 *      Author: ahmed
 */

#ifndef ADC_H_
#define ADC_H_

#include "common_macros.h"
#include "std_types.h"


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
/*Choose betweem INTERRUPT OR POLLING modes*/
//#define ADC_INTERRUPT_MODE
#define ADC_POLLING_MODE

/*Reference Selection AVCC, AREF or internal 2.56V*/
#define ADC_VOLT_REF_VALUE 				2.56

/*max output from the 10 bin adc*/
#define ADC_MAX_OUTPUT_VALUE 		   (1023u)

/*left adjust the result or keep it right adjusted*/
//#define ADC_LEFT_ADJUST_RESULT

/*select PORT of the channels*/
#define ADC_CHANNEL_PORT 			   PORTA_ID
/*ADC channels*/
#define ADC_CHANNEL_0 				       0
#define ADC_CHANNEL_1 					   1
#define ADC_CHANNEL_2 					   2
#define ADC_CHANNEL_3 				       3
#define ADC_CHANNEL_4					   4
#define ADC_CHANNEL_5    				   5
#define ADC_CHANNEL_6 	 				   6
#define ADC_CHANNEL_7    				   7

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/
/*ADC frequencies return to data sheet to choose it*/
typedef enum
{
	ADC_FREQ_PRESCALER_2, ADC_FREQ_PRESCALER_4, ADC_FREQ_PRESCALER_8,
	ADC_FREQ_PRESCALER_16, ADC_FREQ_PRESCALER_32, ADC_FREQ_PRESCALER_128,
}ADC_prescalerSelect;

/*channels of ADC*/
typedef enum
{
	ADC_Channel0, ADC_Channel1, ADC_Channel2, ADC_Channel3,
	ADC_Channel4, ADC_Channel5, ADC_Channel6, ADC_Channel7,
}ADC_SelectedChannel;

/*Auto trigger mode On or off*/
typedef enum
{
	ADC_AUTO_TRIGGER_OFF, ADC_AUTO_TRIGGER_ON,
}ADC_AutoTriggerState;
/*Source of auto trigger mode if ON*/
typedef enum
{
	ADC_FREE_RUNNING_MODE, ADC_ANALOG_COMPARATOR, ADC_EXTERNAL_INTERRUPT_REQUEST,
	ADC_TIMER_COUNTER0_COMPARE_MATCH, ADC_TIMER_COUNTER0_OVERFLOW, ADC_TIMER_COUNTER1_COMPARE_MATCH_B,
	ADC_TIMER_COUNTER1_OVERFLOW, ADC_TIMER_COUNTER1_CAPTURE_EVENT,
}ADC_AutoTriggerSource;

/*ADC Ref source*/
typedef enum
{
	ADC_REF_AVCC, ADC_REF_AREF, ADC_REF_INTERNAL_REF,
}ADC_RefSource;

/*Config struct to init the ADC*/
typedef struct
{
	ADC_RefSource adcRefSource;
	ADC_prescalerSelect prescalerSelection;
	ADC_AutoTriggerState autoTriggerState;
	ADC_AutoTriggerSource autoTriggersource;

}ADC_ConfigType;

/*******************************************************************************
 *                              Functions Prototypes                           *
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
void ADC_init(ADC_ConfigType* Config_ptr);

#ifdef ADC_POLLING_MODE
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
uint16 ADC_readChannel(ADC_SelectedChannel a_channel);
#endif

#ifdef ADC_INTERRUPT_MODE

/*Description
 * Give the ISR the address of the call back fcn*/
void ADC_setCallBackFcn(volatile void (*fcn_ptr)(void));

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
void ADC_readChannel(ADC_SelectedChannel a_channel);
#endif /*ADC_INTERRUPT_MODE*/

#endif /* ADC_H_ */
