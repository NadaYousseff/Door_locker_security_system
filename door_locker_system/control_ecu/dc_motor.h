/******************************************************************************
 *
 * Module: DC_Motor
 *
 * File Name: DC_Motor.h
 *
 * Description: Header file for the ATmega16 DC Motor driver
 *
 * Author: Nada Youssef
 *
 *******************************************************************************/

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "std_types.h"
#include <avr/io.h>

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define MOTOR_PORT    PORTD_ID
#define MOTOR_PIN0    PIN6_ID
#define MOTOR_PIN1    PIN7_ID

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum{
	Stop,Clock_Wise,Anti_Clock_Wise
}DcMotor_State;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description : Function to set up the motor pins direction
 * and stop the motor at the beginning.
 */

void DcMotor_Init(void);

/*
 * Description : Function to rotate the DC Motor according to the input state
 * and the required input speed.
 */
void DcMotor_Rotate(DcMotor_State state,uint8 speed);


#endif /* DC_MOTOR_H_ */
