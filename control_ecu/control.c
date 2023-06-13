/******************************************************************************
 *
 * Module: CONTROL
 *
 * File Name: control.c
 *
 * Description: Source file for CONTROL
 *
 * Author: Nada Youssef
 *
 *******************************************************************************/

#include "control.h"
#include "external_eeprom.h"
#include "uart.h"
#include "twi.h"
#include "buzzer.h"
#include "timer1.h"
#include "dc_motor.h"
#include <util/delay.h>
/*******************************************************************************
 *                              Global Variables                                *
 *******************************************************************************/

uint32 g_ticks = 0;
uint8 App_Password[PASS_LENGTH];
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*
 * Description :
 * Function to be called in Timer1 ISR.
 */
void CallBack_Function(void){
	g_ticks++;
}

/*
 * Description :
 * Function to compare the two passwords sent by the HMI ECU.
 */
uint8 Compare_Passwords(uint8* password1,uint8* password2){
	/* flag to set in case two numbers are mismatched  */
	uint8 flag=0;

	for(uint8 i=0;i<PASS_LENGTH;i++){

		if(password1[i]!=password2[i]){
			flag=1;
		}
	}
	if(flag==0){
		return MATCHED;
	}
	else {
		return NOT_MATCHED;
	}
}
/*
 * Description :
 * Function to save the password sent by the HMI ECU in EEPROM.
 */
void Save_Pasword(uint8 *pass){

	for(uint8 i=0;i<PASS_LENGTH;i++){
		/* storing byte by byte */
		EEPROM_writeByte(PASSWORD_ADRESS+i, pass[i]);
		App_Password[i]=pass[i];
		_delay_ms(50);
	}

}
void Recieve_Password(uint8 *pass){

	uint8 temp;
	for(uint8 i=0;i<PASS_LENGTH;i++){
		/* receiving byte by byte */
		temp=UART_recieveByte();
		pass[i]=temp;
		_delay_ms(50);
	}
}
/*
 * Description :
 * Function to sent the new password by the user.
 * - receive the 2 passwords sent from the HMI ECU.
 * - compare the 2 passwords sent from the HMI ECU.
 * - store the 2 passwords sent from the HMI ECU.
 */
void Setting_Password(void){
	/* to store the 1st password sent by the user */
	uint8 FirstPassword[PASS_LENGTH];
	/* to store the 1st password sent by the user */
	uint8 SecondPassword[PASS_LENGTH];

	uint8 Password_State = NOT_MATCHED;

	while(Password_State == NOT_MATCHED){
		while (UART_recieveByte() != READY);
		UART_sendByte(READY);
		/*1st password*/
		Recieve_Password(FirstPassword);

		while (UART_recieveByte() != READY);
		UART_sendByte(READY);

		/* 2nd password */
		Recieve_Password(SecondPassword);

		/* compare the two password */
		Password_State = Compare_Passwords(FirstPassword, SecondPassword);

		UART_sendByte(READY);

		UART_sendByte(Password_State);

		if ( Password_State == MATCHED){
			/* matched */
			Save_Pasword(FirstPassword);

		}
	}
}

/*
 * Description :
 * Function to open the door via DC_MOTOR Driver.
 * and hold it open for 3 seconds then close it again.
 */
void OpeningDoor(void){
	/* restart the timer ticks */
	g_ticks = 0;
	/* open the door */
	DcMotor_Rotate(Clock_Wise,50);
	while (g_ticks < DOOR_OPENNING_TIME){};

	/* hold the door */
	DcMotor_Rotate(Stop,0);

	while (g_ticks < (DOOR_LEFT_OPEN_TIME+DOOR_OPENNING_TIME)){};

	/* close the door */
	DcMotor_Rotate(Anti_Clock_Wise,50);

	while (g_ticks < (DOOR_CLOSING_TIME+DOOR_LEFT_OPEN_TIME + DOOR_OPENNING_TIME)){};

	DcMotor_Rotate(Stop,0);
}
/*
 * Description :
 * Function to turn on the buzzer in case of a danger situation (entering wrong password 3 times)
 */
void Alert(void){
	/* restart timer ticks */
	g_ticks=0;
	Buzzer_on();
	/* waiting the alert time */
	while(g_ticks < DANGER_TIME);

	Buzzer_off();
}
