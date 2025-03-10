/*
 * interrupt0.h
 *
 *  Created on: 14 Jun 2024
 *      Author: ahmed
 */

#ifndef INTERRUPT0_H_
#define INTERRUPT0_H_

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define INT_SENSE_LOGICAL_CHANGE 				1
#define INT_SENSE_FALLING_EDGE   				2
#define INT_SENSE_RISING_EDGE					3
#define INT0_SENSE  					INT_SENSE_RISING_EDGE /*controls the interrupt sense*/

#define INT0_PORT_ID						  PORTD_ID
#define INT0_PIN_ID							  PIN2_ID


/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description: Function to set the Call Back function address.
 */
void INT0_setCallbackFcn(void (*ptr2Fcn)(void));

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the direction of INT0 pin as input
 * 2. Set the sense of the interrupt
 * 3. Make Global interrupt enable of needed INT
 */
void INT0_init(void);

#endif /* INTERRUPT0_H_ */
