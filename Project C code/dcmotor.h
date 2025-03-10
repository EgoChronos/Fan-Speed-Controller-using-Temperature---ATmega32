/*
 * dcmotor.h
 *
 *  Created on: 19 Jun 2024
 *      Author: ahmed
 */

#ifndef DCMOTOR_H_
#define DCMOTOR_H_

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define DC_MOTOR_PORT 					PORTB_ID
#define DC_MOTOR_RIGHTHAND_PIN 			PIN7_ID
#define DC_MOTOR_LEFTHAND_PIN 			PIN3_ID


/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

/*the states of any dc motor*/
typedef enum
{
	DC_Motor_OFF, DC_Motor_CW, DC_MOTOR_ACW,
}DcMotor_State;


/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/
/* Description
 * setup the direction of the two motor pins
 * turn the motor off at the start
 */
void DcMotor_Init(void);

void DcMotor_Rotate(DcMotor_State state, uint8 dutyCycle);

#endif /* DCMOTOR_H_ */
