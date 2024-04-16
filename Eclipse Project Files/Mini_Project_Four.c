/*
 * Title	  : MINI PROJECT FOUR
 *
 * File Name  : Mini_Project_Four.c
 *
 * Created on : Feb 29, 2024
 *
 * Author	  : Karim Amr
 *
 * Group 	  : 84
 *
 * Description : Application that gets the the distance between Ultra-soinc
 * 				 and object , controls and reads the Ultra-sonic sensor
 *				 to send and receive sound wave and accordingly gets the
 *				 traveled distance by the wave
 */

/********************************************************************/
/*				Libraries required for project application 			*/
/********************************************************************/
#include "Ultrasonic_HC_SR04.h"
#include "LCD.h"
#include <avr/io.h> /*For I-BIT Enable*/
#include "std_types.h"

/*******************************************************************/


int main()
{
	/********************************************************************/
	/*						Initializations of Drivers					*/
	/********************************************************************/

	Ultrasonic_init();
	LCD_init();
	SREG |=(1<<7); /*I-BIT enable*/

	/********************************************************************/
	/*						Program Variables 							*/
	/********************************************************************/

	uint16 measuredDistance = 0;

	/*LCD : The word 'Distance = ' is written once on the screen
	 *		at the beginning of the runtime only*/
	LCD_displayString("Distance = ");

	/********************************************************************/
	/*							Program Loop							*/
	/********************************************************************/
	while(1)
	{
		/********************************************************************/
		/* 								ULTRA-SONIC
		* 			Get the measure distance from ultra-sonic &
		* 			set it into 'measuredDistance' variable			 		*/
		/********************************************************************/

		measuredDistance = Ultrasonic_readDistance();

		/********************************************************************/
		/* 									LCD
		* 			converts the value of measuredDistance into an
		* 		array to type it on the screen followed by 'cm' unit
		* 		move cursor back again to the first digit of the number
		* 		for value updating in the next loop .						*/
		/********************************************************************/

		LCD_intgerToString(measuredDistance);
		LCD_displayString("cm   ");
		LCD_moveCursor(0,11);
	}
}
