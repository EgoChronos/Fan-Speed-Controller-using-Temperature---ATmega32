/*
 * timer0pwm.c
 *
 *  Created on: 19 Jun 2024
 *      Author: ahmed
 */

#include <avr/io.h>
#include "std_types.h"

void Timer0_PWM_Init(uint8 dutyCycPercentage)
{
	uint8 dutyCycle = (uint8)(((uint16)dutyCycPercentage * 255)/ 100);
	DDRB |= (1<<PB3);
	TCNT0 = 0;
	OCR0 = dutyCycle;
	TCCR0 = (1<<WGM01) | (1<<WGM00) | (1<<COM01) | (1<<CS01);
}

void Timer0_PWM_deinit(void)
{
	TCCR0 &= ~((1<<WGM01) | (1<<WGM00) | (1<<COM01) | (1<<CS01));
	TCNT0 = 0;
	OCR0 = 0;
}
