/******************************************************************************
 *
 * Module: PWM
 *
 * File Name: PWM.h
 *
 * Description: Header file for the ATmega16 PWM driver
 *
 * Author: Nada Youssef
 *
 *******************************************************************************/
#ifndef PWM_H_
#define PWM_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define TIMER_MAXIMUM_VALUE    255
#define TIMER_DATA_REG         TCNT0
#define TIMER_COMP_REG         OCR0
#define TIMER_CONTROL_REG      TCCR0

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description : The function responsible for trigger the Timer0 with the PWM Mode.
 * Setup the PWM mode
 * Setup the prescaler
 * Setup the compare value
 * Setup the direction for OC0 as output pin
 */
void PWM_Timer0_Start(uint8 duty_cycle);

#endif /* PWM_H_ */
