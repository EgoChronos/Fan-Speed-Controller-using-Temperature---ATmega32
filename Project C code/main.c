/*
 * main.c
 *
 *  Title: Fan Controller
 *  Created on: 30 May 2024
 *      Author: ahmed
 */

#include "adc.h"
#include "lcd.h"
#include "avr/delay.h"
#include "tempSensor_LM35.h"
#include "dcmotor.h"




uint8 temp = 0;
int main()
{
uint8 currentTemp = 0;

/*the Configurations of the ADC*/
ADC_ConfigType configAdc = {ADC_REF_INTERNAL_REF, ADC_FREQ_PRESCALER_8,ADC_AUTO_TRIGGER_OFF, 0};

/*initialise the LCD*/
LCD_init();
DcMotor_Init();


while (1)
{

/*get temperature of the temperature sensor on channel 2*/
currentTemp = TEMPSENSOR_LM35_getTemp(&configAdc, ADC_Channel2);

/*display fan mode*/
LCD_displaystringRowColumn(0,3, "FAN is ");

if (currentTemp < 30)
{
	DcMotor_Rotate(DC_Motor_OFF, 0);
	LCD_displayString("OFF");
}
else if (currentTemp < 60)
{
	DcMotor_Rotate(DC_Motor_CW, 25);
	LCD_displayString("ON ");
}
else if (currentTemp < 90)
{
	DcMotor_Rotate(DC_Motor_CW, 50);
	LCD_displayString("ON ");
}
else if (currentTemp < 120)
{
	DcMotor_Rotate(DC_Motor_CW, 75);
	LCD_displayString("ON ");
}
else
{
	DcMotor_Rotate(DC_Motor_CW, 100);
	LCD_displayString("ON ");
}

 /* display current temperature*/
LCD_displaystringRowColumn(1,3,"Temp = ");
LCD_displayIntegerToString(currentTemp);
LCD_displayString(" C ");
}

}


