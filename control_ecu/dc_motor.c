/******************************************************************************
 *
 * Module: DC_Motor
 *
 * File Name: DC_Motor.c
 *
 * Description: Source file for the ATmega16 DC Motor driver
 *
 * Author: Nada Youssef
 *
 *******************************************************************************/
#include "dc_motor.h"

#include "gpio.h"
#include "pwm.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void DcMotor_Init(void){
	/* Setup the direction of the 2 motor pins as output */
	GPIO_setupPinDirection(MOTOR_PORT, MOTOR_PIN0, PIN_OUTPUT);
	GPIO_setupPinDirection(MOTOR_PORT, MOTOR_PIN1, PIN_OUTPUT);

	/* stop the motor at the beginning */
	GPIO_writePin(MOTOR_PORT,MOTOR_PIN0,LOGIC_LOW);
	GPIO_writePin(MOTOR_PORT,MOTOR_PIN1,LOGIC_LOW);

}

void DcMotor_Rotate(DcMotor_State state,uint8 speed){
	/* rotate the motor according to the input state */
	if(state == Clock_Wise){
		GPIO_writePin(MOTOR_PORT,MOTOR_PIN0,LOGIC_LOW);
		GPIO_writePin(MOTOR_PORT,MOTOR_PIN1,LOGIC_HIGH);
	}
	else if(state == Anti_Clock_Wise){
		GPIO_writePin(MOTOR_PORT,MOTOR_PIN0,LOGIC_HIGH);
		GPIO_writePin(MOTOR_PORT,MOTOR_PIN1,LOGIC_LOW);
	}
	else{
		GPIO_writePin(MOTOR_PORT,MOTOR_PIN0,LOGIC_LOW);
		GPIO_writePin(MOTOR_PORT,MOTOR_PIN1,LOGIC_LOW);
	}

	/* initiate the PWM and send the required input speed */
	PWM_Timer0_Start(speed);

}
