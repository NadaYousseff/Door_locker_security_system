/******************************************************************************
 *
 * Module: TIMER1
 *
 * File Name: timer1.h
 *
 * Description: Header file for the AVR Timer1 driver
 *
 * Author:  Nada Youssef
 *
 *******************************************************************************/

#ifndef TIMER1_H_
#define TIMER1_H_
#include "std_types.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum{
	normal_mode,compare_mode=4
}Timer1_Mode;

typedef enum{
	no_clock,no_prescaler,prescaler_8,prescaler_64,prescaler_256,prescaler_1024,
	external_falling_edge,external_rising_edge
}Timer1_Prescaler;

typedef struct {
 uint16 initial_value;
 uint16 compare_value;
 Timer1_Prescaler prescaler;
 Timer1_Mode mode;
} Timer1_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for initializing the Timer driver
 */
void Timer1_init(const Timer1_ConfigType * Config_Ptr);
/*
 * Description :
 * Functional responsible for disable the Timer1.
 */
void Timer1_deInit(void);
/*
 * Description :
 * Functional responsible for setting the Call Back function address.
 */
void Timer1_setCallBack(void(*a_ptr)(void));
#endif /* TIMER1_H_ */
