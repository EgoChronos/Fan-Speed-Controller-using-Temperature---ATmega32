/*
 * seven7seg.h
 *
 *  Created on: 30 May 2024
 *      Author: ahmed
 */

#ifndef SEVEN7SEG_H_
#define SEVEN7SEG_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define NUM_OF_SEGMENTS 7
#define MAX_DIGIT 9
/*Choose port and first pin of the 7segment*/
#define SEVEN7SEG_PORT_ID PORTA_ID
#define SEVEN7SEG_PORT PORTA
#define FIRST_PIN_SEVEN7SEG_ID PIN1_ID

/*ENABLE PIN using transistor*/
#define ENABLE_7SEG_PORT_ID PORTC_ID
#define ENABLE_7SEG_PIN_ID PIN6_ID

/*choose hardware*/
#define COMMON_CATHODE
//#define COMMON_ANODE
//#define DECODER

#ifndef DECODER
/*choose DOT pin*/
#define SEVEN7SEG_DOT_PORT_ID PORTB_ID
#define DOT_PIN_SEVEN7SEG PIN0_ID
#endif /*NOT DECODER*/

#ifdef DECODER
#define DECODER_INPUT_NUM_PINS 4
#endif /*DECODER*/

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*initialise the 7SEG*/
void SEVEN7SEG_init(void);

/*display digit on 7segment*/
void SEVEN7SEG_Display(const uint8 digit);

#endif
