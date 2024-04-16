 /******************************************************************************
 *
 * Module: HC-SR04 Ultra-sonic
 *
 * File Name: Ultrasonic_HC_SR04.h
 *
 *  Description: Header file for the HC-SR04 Ultra-sonic  driver
 *
 * Created on: Mar 1, 2024
 *
 * Author: Karim Amr
 *
******************************************************************************/

#ifndef ULTRASONIC_HC_SR04_H_
#define ULTRASONIC_HC_SR04_H_


/*******************************************************************************
 *                           Required Libraries                                *
 *******************************************************************************/


#include "std_types.h"
#include "icu.h"

extern ICU_EdgeType ICU_currentEdge ;

/*******************************************************************************
 *                                    Definitions                               *
 *******************************************************************************/

#define ULTRASONIC_TRIG_PORT	PORTB_ID
#define ULTRASONIC_TRIG_PIN		PIN5_ID

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/


/* Description :
 * Initialize the Ultra-sonic sensor and it's required modules */
void Ultrasonic_init(void);

/* Description :
 * Sends a trigger pulse of 10us to the Ultra-sonic
 * to initiate the eight 40 kHz sound wave  */
void Ultrasonic_Trigger(void);

/* Description :
 * Returns the traveled distance between the Ultra-sonic and object */
uint16 Ultrasonic_readDistance(void);

/* Description :
 * It's used to switch the edge detecting method of ICU Timer.
 * This function is called by ICU driver through callback function.*/
void Ultrasonic_edgeProcessing(void);


#endif /* ULTRASONIC_HC_SR04_H_ */
