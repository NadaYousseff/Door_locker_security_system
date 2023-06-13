/******************************************************************************
 *
 * Module: HUMAN_INTERFACE
 *
 * File Name: human_interface.c
 *
 * Description: Source file for HUMAN_INTERFACE
 *
 * Author: Nada Youssef
 *
 *******************************************************************************/
#include "lcd.h"
#include "keypad.h"
#include "uart.h"
#include <util/delay.h>
#include "human_interface.h"

/*******************************************************************************
 *                              Global Variables                                *
 *******************************************************************************/

uint32 g_ticks = 0;

char* pass=NULL_PTR;
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*
 * Description :
 * Function to be called in Timer1 ISR.
 */
void CallBack_Function(void) {
	g_ticks++;
}
/*
 * Description :
 * Function to get the password of the user for the first time.
 */
void Get_Password(uint8 *pass){
	LCD_moveCursor(1, 0);
	/*variable to get the pressed keypad button */
	uint8 key;

	for(uint8 i=0;i<PASS_LENGTH;){
		key = KEYPAD_getPressedKey();
		/*accepting numbers only from the user*/
		if (key >= 0 && key <= 9) {
			LCD_displayCharacter('*');
			//LCD_displayCharacter(key+48);
			pass[i]= key;
			i++;
		}
		_delay_ms(300);
	}
	/* waiting for the user to press enter */
	while(KEYPAD_getPressedKey() != 13);
}

/*
 * Description :
 * Function to get the password of the user for the second time for confirmation.
 */
void Get_Password_again(uint8 *pass){
	LCD_moveCursor(1, 10);
	/*variable to get the pressed keypad button */
	uint8 key;

	for(uint8 i=0;i<PASS_LENGTH;){
		key = KEYPAD_getPressedKey();
		/*accepting numbers only from the user*/
		if (key >= 0 && key <= 9) {
			LCD_displayCharacter('*');
			//LCD_displayCharacter(key+48);
			pass[i]= key;
			i++;
		}

		_delay_ms(300);
	}
	/* waiting for the user to press enter */
	while(KEYPAD_getPressedKey() != 13);

}
/*
 * Description :
 * Function to send the password to the control ECU via UART Driver.
 */
void Send_Password(uint8 *pass){

	uint8 temp;
	for (uint8 i=0;i<PASS_LENGTH;i++){
		/* sending one byte at a time */
		temp=pass[i];
		UART_sendByte(temp);
		_delay_ms(50);
	}
}
/*
 * Description :
 * Function to get the password from user twice for confirmation.
 * send it to the control ECU.
 * and inform the user whether the two password are matched or not.
 */
void Set_Password(void){
	/* to store the 1st password  */
	uint8 PasswordTemp1[PASS_LENGTH];
	/* to store the 2nd password  */
	uint8 Password_State = 0;
	/* exit only if the two passwords are matched */
	while(Password_State == 0){
		LCD_clearScreen();
		LCD_displayStringRowColumn(0, 0,"plz enter pass");
		/* 1st password */
		Get_Password(PasswordTemp1);

		UART_sendByte(READY);          //ready
		while (UART_recieveByte() != READY);

		/* sending the 1st password to control ECU */
		Send_Password(PasswordTemp1);

		LCD_clearScreen();
		LCD_displayStringRowColumn(0, 0, "plz re_enter the");
		LCD_displayStringRowColumn(1, 0, "same pass: ");


		/* 2nd password */
		Get_Password_again(PasswordTemp1);

		UART_sendByte(READY);

		while (UART_recieveByte() != READY);
		/* sending the 1st password to control ECU */
		Send_Password(PasswordTemp1);

		while (UART_recieveByte() != READY);
		/*getting the state of the two passwords*/
		Password_State = UART_recieveByte();
		if(Password_State == MATCHED){
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,0,"Match");
			_delay_ms(500);
		}
		else if(Password_State == NOT_MATCHED){
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,0,"Mismatch");
			_delay_ms(500);
		}
	}

	LCD_clearScreen();
}
/*
 * Description :
 * Function to display the options for the user on the LCD.
 */
void Display_Options(void){
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, "+: Open Door");
	LCD_displayStringRowColumn(1, 0, "-: Change Password");
}
/*
 * Description :
 * Function to display the opening statues to the user
 * while the control ECU is opening the door.
 */
void OpeningDoor(void) {
	/* restart the timer ticks */
	g_ticks = 0;
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, "Door is Unlocking" );
	/* waiting the door opening time */
	while (g_ticks < DOOR_OPENNING_TIME) {};

	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, "Unlocked");
	/* holding the door */
	while (g_ticks < (DOOR_LEFT_OPEN_TIME + DOOR_OPENNING_TIME)) {};

	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, "Door is Locking");
	/* waiting the door closing time */
	while (g_ticks < (DOOR_CLOSING_TIME + DOOR_LEFT_OPEN_TIME + DOOR_OPENNING_TIME)) {};

}
/*
 * Description :
 * Function to display the Danger situation to the user on LCD.
 */
void Display_Danger(void) {
	/* restart the timer ticks */
	g_ticks = 0;
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, "DANGER!!!!");
	/* waiting the alert time */
	while (g_ticks < DANGER_TIME) {};

}
/*
 * Description :
 * Function to display to the user that the password doesn't match.
 */
void Display_MisMatch(void) {
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, "Mismatch");
	_delay_ms(500);
}



