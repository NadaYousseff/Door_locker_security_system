/******************************************************************************
 *
 * Module: TIMER1
 *
 * File Name: timer1.c
 *
 * Description: source file for the AVR Timer1 driver
 *
 * Author:  Nada Youssef
 *
 *******************************************************************************/

#include "timer1.h"
#include "common_macros.h" /* To use the macros like SET_BIT */
#include <avr/io.h> /* To use ICU/Timer1 Registers */
#include <avr/interrupt.h> /* For ICU ISR */
/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;
/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/
ISR(TIMER1_OVF_vect){
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

ISR(TIMER1_COMPA_vect){
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

/*
 * Description :
 * Functional responsible for initializing the Timer driver
 */
void Timer1_init(const Timer1_ConfigType * Config_Ptr){
	TCNT1=Config_Ptr->initial_value;              /* setting Timer1 initial value to 0 */
	SET_BIT(TCCR1A,FOC1A);                           /* setting to 1 if non_PWM mode */

	if(Config_Ptr->mode==normal_mode){
		SET_BIT(TIMSK,TOIE1);   /* Enable Timer1 overflow Interrupt*/
		/* mode 0: WGM13=0, WGM12=0, WGM11=0, WGM10=0 */
		CLEAR_BIT(TCCR1B,WGM10);
		CLEAR_BIT(TCCR1B,WGM11);
		CLEAR_BIT(TCCR1B,WGM12);
		CLEAR_BIT(TCCR1B,WGM13);

	}
	else if(Config_Ptr->mode==compare_mode){
		SET_BIT(TIMSK,OCIE1A);     /* Enable Timer1 Compare A Interrupt*/
		OCR1A=Config_Ptr->compare_value;          /* setting Timer1 Compare A value */
		/* mode 4: WGM13=0, WGM12=1, WGM11=0, WGM10=0 */
		CLEAR_BIT(TCCR1B,WGM10);
		CLEAR_BIT(TCCR1B,WGM11);
		SET_BIT(TCCR1B,WGM12);
		CLEAR_BIT(TCCR1B,WGM13);
	}
	TCCR1B=(TCCR1B&0xF8)|(Config_Ptr->prescaler&0x07);  /* setting the prescaler */
}
/*
 * Description :
 * Functional responsible for disable the Timer1.
 */
void Timer1_deInit(void){
	/* Clear All Timer1 Registers */
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	/* Disable timer1 interrupts */
	CLEAR_BIT(TIMSK,TOIE1);
	CLEAR_BIT(TIMSK,OCIE1A);

}
/*
 * Description :
 * Functional responsible for setting the Call Back function address.
 */
void Timer1_setCallBack(void(*a_ptr)(void)){
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr = a_ptr;
}


