/******************************************************************************
 *
 * Module: PWM
 *
 * File Name: PWM.c
 *
 * Description: Source file for the ATmega16 PWM driver
 *
 * Author: Nada Youssef
 *
 *******************************************************************************/

#include "pwm.h"
#include "gpio.h"


#include "common_macros.h"
#include <avr/io.h>

void PWM_Timer0_Start(uint8 duty_cycle){
	/* Set Timer0 Initial Value to 0 */
	TIMER_DATA_REG = 0;
	/* Set Compare Value */
	TIMER_COMP_REG  = (uint8)((uint32)(duty_cycle*TIMER_MAXIMUM_VALUE)/100);
	/* Configure PB3/OC0 as output pin --> pin where the PWM signal is generated from MC*/
	GPIO_setupPinDirection(PORTB_ID, PIN3_ID,PIN_OUTPUT);
	//SET_BIT(DDRB,PB3);
	/* Configure timer control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
	 */
	TIMER_CONTROL_REG  = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS01);

}

