/******************************************************************************
 *
 * Module: MAIN
 *
 * File Name: main.c
 *
 * Description: the main file of the control ECU
 *
 * Author: Nada Youssef
 *
 *******************************************************************************/
#include "uart.h"
#include <avr/io.h>
#include "control.h"
#include "twi.h"
#include "timer1.h"
#include"dc_motor.h"


int main(void){
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
	/* UART Initialization */
	UART_ConfigType confg={eight_bit,disable,one_bit,400000};
	UART_init(&confg);
	/*TWI Initialization */
	TWI_ConfigType confg_twi={0x01,400000};
	TWI_init(&confg_twi);
	/*DC_Motor Initialization */
	DcMotor_Init();

	Setting_Password();

	uint8 recieved_password[PASS_LENGTH];

	uint8 no_of_wrong_entered_password=0;

	uint8 option=0;

	uint8 state=0;

	while (1) {

		if (UART_recieveByte() == READY) {
			/* receiving password from HMI ECU */
			Recieve_Password(recieved_password);

			/* receiving option from HMI ECU */
			option = UART_recieveByte();

			if (option == Open_Door_Option) {
				/* compare the password to the saved password */
				state = Compare_Passwords(App_Password, recieved_password);
				/* password is matched */
				if (state == MATCHED) {

					UART_sendByte(Opening_Door);

					no_of_wrong_entered_password = 0;

					OpeningDoor();
				}
				/* password is not matched */
				else if (state == NOT_MATCHED) {
					no_of_wrong_entered_password++;
					if (no_of_wrong_entered_password == Max_Pass_Tries ) {
						UART_sendByte(Danger);
						/* activate the alert */
						Alert();
						/* reset */
						no_of_wrong_entered_password = 0;
					}
					else {

						UART_sendByte(NOT_MATCHED);
					}
				}
			}

			else if (option == Change_Password_Option) {
				state=Compare_Passwords(App_Password, recieved_password);

				/* password is matched */
				if ( state== MATCHED) {

					UART_sendByte(Changing_Password);
					/* reset */
					no_of_wrong_entered_password=0;

					Setting_Password();
				}
				/* password is not matched */
				else if(state==NOT_MATCHED){
					no_of_wrong_entered_password++;
					if (no_of_wrong_entered_password == Max_Pass_Tries ){
						UART_sendByte(Danger);

						/* activate alert */
						Alert();

						/* reset */
						no_of_wrong_entered_password=0;
					}
					else{

						UART_sendByte(NOT_MATCHED);
					}

				}

			}

		}
	}
}



