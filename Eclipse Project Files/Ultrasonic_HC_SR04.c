 /******************************************************************************
 *
 * Module: HC-SR04 Ultra-sonic
 *
 * File Name: Ultrasonic_HC_SR04.c
 *
 *  Description: Source file for the HC-SR04 Ultra-sonic  driver
 *
 * Created on: Mar 1, 2024
 *
 * Author: Karim Amr
 *
******************************************************************************/

/*******************************************************************************
 *                           Required Libraries                                *
 *******************************************************************************/

#include "Ultrasonic_HC_SR04.h"
#include "std_types.h"
#include "icu.h"
#include "gpio.h"
#include <util/delay.h>


/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
	/*The variable holds the ICR1 value
	 * ( also known to be the time take for the Echo to travel time) */
	uint16 pulseTime = 0 ;

/*******************************************************************************
 *                              Functions Definitions                           *
 *******************************************************************************/

/*Description :
 * Initialize the Ultra-sonic sensor and it's required modules such as :
 * - Initialize ICU Driver and its configuration
 * - Setting the required callback function
 * - Configure the Trigger pin as OUTPUT  */
void Ultrasonic_init(void)
{
	/*Set the ICU configuration into its type structure */
	ICU_ConfigType ICU_Config = {F_CPU_8,RISING};

	/*Initialize ICU Driver with its configuration*/
	ICU_init(&ICU_Config);

	/*Current Edge detecting method = RISING*/
	ICU_currentEdge=RISING;

	/*Set callback function to : Ultra-sonic edge processing*/
	ICU_setCallBack(Ultrasonic_edgeProcessing);

	/*Setup Trigger pin as Output*/
	GPIO_setupPinDirection(ULTRASONIC_TRIG_PORT,ULTRASONIC_TRIG_PIN,PIN_OUTPUT);
}

/* Description :
 * Sends a trigger pulse of 10us to the Ultra-sonic
 * to initiate the eight 40 kHz sound wave  */
void Ultrasonic_Trigger(void)
{
	GPIO_writePin(ULTRASONIC_TRIG_PORT,ULTRASONIC_TRIG_PIN,LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(ULTRASONIC_TRIG_PORT,ULTRASONIC_TRIG_PIN,LOGIC_LOW);

}

/* Description :
 * Returns the traveled distance between the Ultra-sonic and
 * object by sending trigger pulse , and measuring the time
 * at which Echo pin is reading HIGH where it indicates the
 * distance through according calculations */
uint16 Ultrasonic_readDistance(void)
{
	/*Initiate the trigger pulse*/
	Ultrasonic_Trigger();

	/* Speed of sound = 340 m/s
	 * and we know Distance = Time * Speed
	 * So , D = (TIME OF ECHO at HIGH * 340) / 2 cm
	 * ("Total time is divided by 2 to get only one way travel")
	 *
	 * As we have selected internal frequency of  8 MHz and F_CPU/8 pre-scalar
	 * so the time to execute one instruction is 1x10^-6
	 * We multiply that by our time and get the following equation
	 * Distance = (Time / 58.8) cm
	 * we add ONE as a correction value */
	return (uint16)(((float)(pulseTime) / (58.8)) + 1) ;
}


/* Description :
 * It's used to switch the edge detecting method of ICU Timer.
 * This function is called by ICU driver through callback function.
 *
 * First Step :
 * The detecting method is = RAISING ,
 * in which it starts the ICU timer and sets timer start
 * value at ICR1 , which means it the Timer value should be cleared
 * from the counter to start counting from the rising edge
 * and switch the detecting method to FALLING
 *
 * Second Step :
 * when ICU detect Falling edge indicating the end of
 * ECHO pulse , it sets the timer value at ICR which
 * is then saved to pulseTimer variable ,
 * flip the detecting method back to rising
 * and ready for another pulse*/
void Ultrasonic_edgeProcessing(void)
{

	if(FALLING == ICU_currentEdge) 	/*Current Edge detecting method = FALLING*/
	{
		/*Save the ICR1 value into the variable*/
		pulseTime = ICU_getInputCaptureValue();

		/*Edge detecting method set to = RISING*/
		ICU_setEdgeDetectionType(RISING);
		ICU_currentEdge=RISING;


	}
	else /*Current Edge detecting method = RISING*/

	{
		/*Clear TIMER counter*/
		ICU_clearTimerValue();

		/*Edge detecting set to method = RISING*/
		ICU_setEdgeDetectionType(FALLING);
		ICU_currentEdge=FALLING;

	}

}

/*******************************************************************************/
