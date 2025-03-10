/*
 * seven7seg.c
 *
 *  Created on: 30 May 2024
 *      Author: ahmed
 */

#include <avr/io.h>
#include <avr/delay.h>
#include "common_macros.h"
#include "gpio.h"
#include "seven7seg.h"


/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

#ifdef COMMON_CATHODE
/*Send digit to the seven segment of type common cathode*/
static void SEVEN7SEG_Display_CommonCathode(const uint8 digit);
#endif

#ifdef COMMON_ANODE
/*send digit to the seven segment of type common anode*/
static void SEVEN7SEG_Display_CommonAnode(const uint8 digit);
#endif

#ifdef DECODER
/*Send digit to the decoder*/
static void SEVEN7SEG_Display_DECODER(const uint8 digit);
#endif

/*******************************************************************************
 *                              Functions Definition                           *
 *******************************************************************************/

/*initialise the 7SEG*/
void SEVEN7SEG_init(void)
{
	uint8 pinNum = FIRST_PIN_SEVEN7SEG_ID;

	//make pin output to enable the 7seg
	GPIO_setupPinDirection(ENABLE_7SEG_PORT_ID, ENABLE_7SEG_PIN_ID, PIN_OUTPUT);
	//make pin High so it enable transistor to display on DIG1
	GPIO_writePin(ENABLE_7SEG_PORT_ID, ENABLE_7SEG_PIN_ID, LOGIC_HIGH);

#ifndef DECODER
	/*SETUP 7SEG pins as output and write them LOGIC_LOW 0*/
	for (pinNum = FIRST_PIN_SEVEN7SEG_ID; pinNum < (FIRST_PIN_SEVEN7SEG_ID + NUM_OF_SEGMENTS); ++pinNum)
	{
		GPIO_setupPinDirection(SEVEN7SEG_PORT_ID,pinNum, PIN_OUTPUT);
		GPIO_writePin(FIRST_PIN_SEVEN7SEG_ID,pinNum,LOGIC_LOW);
	}

	/*setup DOT pin as output and write it LOGIC_LOW 0*/
	GPIO_setupPinDirection(SEVEN7SEG_DOT_PORT_ID,DOT_PIN_SEVEN7SEG, PIN_OUTPUT);
	GPIO_writePin(SEVEN7SEG_DOT_PORT_ID,DOT_PIN_SEVEN7SEG,LOGIC_LOW);

	/*Display 0 at the start*/
#ifdef COMMON_CATHODE
	SEVEN7SEG_PORT |= (0x3F<<FIRST_PIN_SEVEN7SEG_ID);
#endif
#ifdef COMMON_ANODE
	SEVEN7SEG_PORT |= (0xC0<<FIRST_PIN_SEVEN7SEG_ID);
#endif

#endif /*DECODER_NOT_DEFINDED*/

#ifdef DECODER
	/*SETUP 7SEG pins as output and write them LOGIC_LOW 0*/
	for (pinNum = FIRST_PIN_SEVEN7SEG_ID; pinNum < (FIRST_PIN_SEVEN7SEG_ID + DECODER_INPUT_NUM_PINS); ++pinNum)
	{
		GPIO_setupPinDirection(SEVEN7SEG_PORT_ID,pinNum, PIN_OUTPUT);
		/*display zero at the start*/
		GPIO_writePin(FIRST_PIN_SEVEN7SEG_ID,pinNum,LOGIC_HIGH);
	}
#endif /*DECODER*/

}

void SEVEN7SEG_Display(const uint8 digit)
{
#ifdef COMMON_CATHODE
/*Send digit to the seven segment of type common cathode*/
SEVEN7SEG_Display_CommonCathode(digit);
#endif

#ifdef COMMON_ANODE
/*send digit to the seven segment of type common anode*/
SEVEN7SEG_Display_CommonAnode(digit);
#endif

#ifdef DECODER
/*Send digit to the decoder*/
SEVEN7SEG_Display_DECODER(digit);
#endif

}
/*send digit to the seven segment of type common cathode*/
#ifdef COMMON_CATHODE
/*Display digit on the 7SEG*/
static void SEVEN7SEG_Display_CommonCathode(const uint8 digit)
{
	_delay_ms(30);
/*clear all bits*/
#if (FIRST_PIN_SEVEN7SEG_ID == PIN1_ID)
	SEVEN7SEG_PORT &= 0x01;
#elif (FIRST_PIN_SEVEN7SEG_ID == PIN0_ID)
	SEVEN7SEG_PORT &= 0x80;
#endif

	/*draw the number on the 7Seg*/
	switch (digit)
		{
		case 0:
			SEVEN7SEG_PORT |= (0x3F<<FIRST_PIN_SEVEN7SEG_ID);
			break;
		case 1:
			SEVEN7SEG_PORT |= (0x06<<FIRST_PIN_SEVEN7SEG_ID);
			break;
		case 2:
			SEVEN7SEG_PORT |= (0x5B<<FIRST_PIN_SEVEN7SEG_ID);
			break;
		case 3:
			SEVEN7SEG_PORT |= (0x4F<<FIRST_PIN_SEVEN7SEG_ID);
			break;
		case 4:
			SEVEN7SEG_PORT |= (0x66<<FIRST_PIN_SEVEN7SEG_ID);
			break;
		case 5:
			SEVEN7SEG_PORT |= (0x6D<<FIRST_PIN_SEVEN7SEG_ID);
			break;
		case 6:
			SEVEN7SEG_PORT |= (0x7D<<FIRST_PIN_SEVEN7SEG_ID);
			break;
		case 7:
			SEVEN7SEG_PORT |= (0x07<<FIRST_PIN_SEVEN7SEG_ID);
			break;
		case 8:
			SEVEN7SEG_PORT |= (0x7F<<FIRST_PIN_SEVEN7SEG_ID);
			break;
		case 9:
			SEVEN7SEG_PORT |= (0x6F<<FIRST_PIN_SEVEN7SEG_ID);
			break;
		default:
			break;
		}
}
#endif

/*send digit to the seven segment of type common anode*/
#ifdef COMMON_ANODE
static void SEVEN7SEG_Display_CommonAnode(const uint8 digit)
{
	_delay_ms(30);
/*clear all bits*/
#if (FIRST_PIN_SEVEN7SEG_ID == PIN1_ID)
	SEVEN7SEG_PORT &= 0x01;
#elif (FIRST_PIN_SEVEN7SEG_ID == PIN0_ID)
	SEVEN7SEG_PORT &= 0x80;
#endif

	/*draw the number on the 7Seg*/
	switch (digit)
		{
	case 0:
		SEVEN7SEG_PORT |= (0xC0<<FIRST_PIN_SEVEN7SEG_ID);
		break;
	case 1:
		SEVEN7SEG_PORT |= (0xF9<<FIRST_PIN_SEVEN7SEG_ID);
		break;
	case 2:
		SEVEN7SEG_PORT |= (0xA4<<FIRST_PIN_SEVEN7SEG_ID);
		break;
	case 3:
		SEVEN7SEG_PORT |= (0xB0<<FIRST_PIN_SEVEN7SEG_ID);
		break;
	case 4:
		SEVEN7SEG_PORT |= (0x99<<FIRST_PIN_SEVEN7SEG_ID);
		break;
	case 5:
		SEVEN7SEG_PORT |= (0x92<<FIRST_PIN_SEVEN7SEG_ID);
		break;
	case 6:
		SEVEN7SEG_PORT |= (0x82<<FIRST_PIN_SEVEN7SEG_ID);
		break;
	case 7:
		SEVEN7SEG_PORT |= (0xF8<<FIRST_PIN_SEVEN7SEG_ID);
		break;
	case 8:
		SEVEN7SEG_PORT |= (0x80<<FIRST_PIN_SEVEN7SEG_ID);
		break;
	case 9:
		SEVEN7SEG_PORT |= (0x90<<FIRST_PIN_SEVEN7SEG_ID);
		break;
	default:
		break;
	}
}
#endif

#ifdef DECODER
/*Send digit to the decoder*/
static void SEVEN7SEG_Display_DECODER(const uint8 digit)
{
	_delay_ms(30);
	/*check the num to make sure it is a digit*/
	if (digit > MAX_DIGIT)
	{
		/*Do Nothing*/
	}
	else
	{
		/*display the digit*/
		GPIO_writePin(SEVEN7SEG_PORT_ID,FIRST_PIN_SEVEN7SEG_ID, GET_BIT(digit, BIT0_ID));
		GPIO_writePin(SEVEN7SEG_PORT_ID,FIRST_PIN_SEVEN7SEG_ID+1, GET_BIT(digit, BIT1_ID));
		GPIO_writePin(SEVEN7SEG_PORT_ID,FIRST_PIN_SEVEN7SEG_ID+2, GET_BIT(digit, BIT2_ID));
		GPIO_writePin(SEVEN7SEG_PORT_ID,FIRST_PIN_SEVEN7SEG_ID+3, GET_BIT(digit, BIT3_ID));
	}
}
#endif
