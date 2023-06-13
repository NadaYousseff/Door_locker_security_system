/******************************************************************************
 *
 * Module: BUZZER
 *
 * File Name: buzzer.c
 *
 * Description: Source file for the AVR BUZZER driver
 *
 * Author:  Nada Youssef
 *
 *******************************************************************************/
#include "buzzer.h"
#include "gpio.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*
 * Description :
 *  - Setup the direction for the buzzer pin as output pin through the GPIO driver.
 *  - Turn off the buzzer through the GPIO.
 */
void Buzzer_init(void){

	/* setting the direction of the buzzer pin as output */
	GPIO_setupPinDirection(BUZZER_PORT, BUZZER_PIN, PIN_OUTPUT);
	/* turn off the buzzer at the beginning */
	GPIO_writePin(BUZZER_PORT, BUZZER_PIN, LOGIC_LOW);

}
/*
 * Description :
 * Function to enable the Buzzer through the GPIO.
 */
void Buzzer_on(void){

	/* turn on the buzzer */
	GPIO_writePin(BUZZER_PORT, BUZZER_PIN, LOGIC_HIGH);

}
/*
 * Description :
 * Function to disable the Buzzer through the GPIO.
 */
void Buzzer_off(void){

	/* turn off the buzzer */
	GPIO_writePin(BUZZER_PORT, BUZZER_PIN, LOGIC_LOW);

}
