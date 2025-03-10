/*
 * dcmotor.c
 *
 *  Created on: 19 Jun 2024
 *      Author: ahmed
 */
#include "gpio.h"
#include "dcmotor.h"
#include "timer0pwm.h"
#include <avr/delay.h>


/* Description
 * setup the direction of the two motor pins
 * turn the motor off at the start
 */
void DcMotor_Init(void)
{
	/*setup the 2 motor pins direction as output pins*/
	GPIO_setupPinDirection(DC_MOTOR_PORT, DC_MOTOR_RIGHTHAND_PIN, PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_PORT, DC_MOTOR_LEFTHAND_PIN, PIN_OUTPUT);

	/*Turn the motor off at the start by setting both pins to logic low*/
	GPIO_writePin(DC_MOTOR_PORT, DC_MOTOR_RIGHTHAND_PIN, LOGIC_LOW);
	GPIO_writePin(DC_MOTOR_PORT, DC_MOTOR_LEFTHAND_PIN, LOGIC_LOW);

}


void DcMotor_Rotate(DcMotor_State state, uint8 speedPercentage)
{
	_delay_ms(20);
	if (state == DC_Motor_OFF)
	{
		Timer0_PWM_deinit();
	}
	else
	{
		Timer0_PWM_Init(speedPercentage);
	}
}
