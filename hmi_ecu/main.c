/******************************************************************************
 *
 * Module: MAIN
 *
 * File Name: main.c
 *
 * Description: the main file of the HMI ECU
 *
 * Author: Nada Youssef
 *
 *******************************************************************************/
#include "lcd.h"
#include "keypad.h"
#include "uart.h"
#include"timer1.h"
#include <avr/io.h>
#include "human_interface.h"
int main(void){
	uint8 Keypad_PressedKey = 0;
	uint8 Entered_Password[PASS_LENGTH];
	uint8 state = 0;
	/*Enable global interrupts*/
	SREG |= 1 << 7;
	/*Timer Initialization */
	Timer1_setCallBack(CallBack_Function);
	/*we want interrupt every 1 sec
	 * using compare mode and prescaler=256
	 * F_TIMER=F_CPU/256 = 31250 hz
	 * T_Timer=1/31250=32usec
	 * 1_sec_Ticks=1/32u=31250 ticks
	 * so, comp_value=31250
	 * */
	Timer1_ConfigType Timer_config = { 0,31250,prescaler_256,compare_mode};
	Timer1_init(&Timer_config);

	/*UART Initialization */
	UART_ConfigType confg={eight_bit,disable,one_bit,400000};
	UART_init(&confg);

	/*LCD Initialization */
	LCD_init();
	/* keypad initialization */
	KEYPAD_init();
	/* setting the password for the first time */
	Set_Password();

	while(1){
		Display_Options();

		do
		{
			Keypad_PressedKey = KEYPAD_getPressedKey();
			/* accepting only '+' and '-' as options */
		}while ((Keypad_PressedKey != Open_Door_Option) && (Keypad_PressedKey != Change_Password_Option));

		if (Keypad_PressedKey == Open_Door_Option)
		{
			LCD_clearScreen();
			LCD_displayStringRowColumn(0, 0,"plz enter pass");
			/* reading the password */
			Get_Password(Entered_Password);

			UART_sendByte(READY);
			/* sending the password to the control ECU for authorization */
			Send_Password(Entered_Password);
			/* sending the option chosen by the user */
			UART_sendByte(Open_Door_Option);

			state = UART_recieveByte();
			if (state == Opening_Door)
			{
				OpeningDoor();
			}
			else if (state == NOT_MATCHED)
			{

				Display_MisMatch();
			}
			/* entered the wrong password 3 times! */
			else if (state == Danger)
			{

				Display_Danger();
			}
		}
		else if (Keypad_PressedKey == Change_Password_Option){
			LCD_clearScreen();
			LCD_displayStringRowColumn(0, 0,"plz enter pass");
			/* reading the password */
			Get_Password(Entered_Password);
			UART_sendByte(READY);
			/* sending the password to the control ECU for authorization */
			Send_Password(Entered_Password);
			/* sending the option chosen by the user */
			UART_sendByte(Change_Password_Option);
			state = UART_recieveByte();

			if (state == Changing_Password)
			{
				/* two matching passwords */
				Set_Password();

			}
			else if (state == NOT_MATCHED)
			{
				/* mismatch */
				Display_MisMatch();

			}
			else if (state == Danger)
			{
				/* entered the wrong password 3 times! */
				Display_Danger();

			}

		}
	}
}
