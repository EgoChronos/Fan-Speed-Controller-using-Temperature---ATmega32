/*
 * interrupt0.c
 *
 *  Created on: 14 Jun 2024
 *      Author: ahmed
 */



/*
 * interrupt0.c
 *
 *  Created on: 14 Jun 2024
 *      Author: ahmed
 */

#include "interrupt0.h"
#include "gpio.h"
#include "common_macros.h"
#include <avr/io.h>
#include <avr/interrupt.h>

/*******************************************************************************
 *                              Private Global variables                           *
 *******************************************************************************/
static volatile void (*g_callbackFcn_ptr)(void) = NULL_PTR;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/
ISR (INT0_vect)
{
	/* Call the Call Back function in the application after the edge is detected*/
	(*g_callbackFcn_ptr)();
}

/*******************************************************************************
 *                              Functions Definition                           *
 *******************************************************************************/

/*
 * Description: Function to set the Call Back function address.
 */
void INT0_setCallbackFcn(void (*ptr2Fcn)(void))
{
	g_callbackFcn_ptr = ptr2Fcn;
}

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the direction of INT0 pin as input
 * 2. Set the sense of the interrupt
 * 3. Make Global interrupt enable of needed INT
 */
void INT0_init(void)
{

	/*setup the direction of INT0 pin as input*/
	GPIO_setupPinDirection(INT0_PORT_ID, INT0_PIN_ID, PIN_INPUT);

	/************************** MCUCR Description **************************
	 * Interrupt Sense Control ISC01, ISC00 to choose sense of INT0
	 * INT0 of GICR = 1  to enable the interrupt of INT0
	 ***********************************************************************/
	MCUCR = (MCUCR& 0xFC) | (INT0_SENSE & (0x03));
	SET_BIT(GICR, INT0);
}
